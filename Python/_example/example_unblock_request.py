from contextlib import asynccontextmanager
from concurrent.futures import ThreadPoolExecutor
from functools import partial
import requests
import asyncio
import time

class ASyncRequests:
    """非阻塞的requests"""
    
    def __init__(self, count):
        """ 
        :param count: 线程池大小
        """
        assert isinstance(count, int)
        self.pool = ThreadPoolExecutor(count) # 创建线程池
        self.loop = asyncio.get_running_loop() # 获得事件循环
        if not self.loop:
            raise RuntimeError("event loop为None")
        
        # self.all_future 用于装run_in_executor返回的future对象
        # python3.9版本用to_threadself.all_future = []
    
    def get(self, url, callback, **kwargs):
        self.requests(url, "get", callback, **kwargs)
    
    def post(self, url, callback, **kwargs):
        self.requests(url, "post", callback, **kwargs)
    
    def requests(self, url, method, callback, **kwargs):
        """
        写了两种方法，第一种适合版本python，另一种适合最新版的python
        """
        # python3.5及以上版本可用
            # run_in_executor:
                #   把阻塞的函数放入线程池中执行
                #   返回一个asyncio.Future对象
                #   传值时，利用 偏函数 传关键字参数
            # result = self.loop.run_in_executor(self.pool, partial(requests.request, url=url, method=method, **kwargs))
            # result.add_done_callback(callback) # 回调
            # self.all_future.append(result)        
        # python3.9及以上版本可用
            # to_thread:
                #   使用其它的线程，执行阻塞函数
                #   返回一个协程
                #   除第一个参数外的所有参数都会给func
        coro = asyncio.to_thread(requests.request, url=url, method=method, **kwargs)
        task = asyncio.create_task(coro)
        task.add_done_callback(callback) # 回调
        self.all_future.append(task)


def process_get(future):
    """回调函数，处理返回值"""
    print(type(future))  # <class '_asyncio.Future'>
    # future.result()的返回值就是Response对象
    print(future.result().status_code)  # 200

@asynccontextmanager
async def request_session(count=5):
    try:
        async_req = ASyncRequests(count)
        yield async_req
    finally:
        await asyncio.gather(*async_req.all_future)

async def main():
    async with request_session(10) as session:
        session.get("https://www.baidu.com/", callback=process_get)
        session.get("https://www.sogo.com/", callback=process_get)
        session.get("https://cn.bing.com/", callback=process_get)
        session.get("https://www.cnblogs.com/", callback=process_get)

if __name__ == '__main__':
    start = time.time()
    asyncio.run(main())
    end = time.time()
    print("使用协程加线程：总用时: %f sec" % (end - start))

    # block_req()
    # print("直接访问：总用时: %f sec" % (time.time() - end))
    # 访问数越多，协程的优势就越大
    # 访问同一个网站过多可能会报错 Connection aborted.', ConnectionResetError(10054, '远程主机强迫关闭了一个现有的连接。