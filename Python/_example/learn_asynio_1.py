'''
callback example
'''
# import asyncio

# def callback(future):# 唯一参数是一个Task对象
#     # print(type(future)) # <class '_asyncio.Task'>
#     # print(future) # <Task finished name='Task-2' coro=<foo() done, defined at E: ... xxx.py:11> result=123>
#     # print(future.get_name()) # foo
#     print(future.result()) # 123   
#     # 接收返回值

# async def foo(num, name):
#     print(f"{name} is running")
#     return num

# async def main():
#     task = asyncio.create_task(await asyncio.gather([foo(1,'A'), foo(2,'B'), foo(3,'C')]))
#     task.add_done_callback(callback) # 添加回调函数
#     await task

# if __name__ == '__main__':
#     asyncio.run(main())

'''
concurrent running via .create_task
'''
# import asyncio

# async def foo(char:str, count: int):
#     for i in range(count):
#         print(f"{char}-{i}")
#         await asyncio.sleep(.5)

# async def main():
#     task1 = asyncio.create_task(foo("A", 2))
#     task2 = asyncio.create_task(foo("B", 3))
#     task3 = asyncio.create_task(foo("C", 2))
#     await task1
#     await task2
#     await task3

# if __name__ == '__main__':
#     asyncio.run(main())



'''
concurrent running via .gather
'''

# import asyncio

# async def foo(char:str, count: int):
#     for i in range(count):
#         print(f"{char}-{i}")
#         await asyncio.sleep(.5)

# async def main():
#     await asyncio.gather(
#         foo("A", 2), 
#         foo("B", 3), 
#         foo("C", 2)
#         )
    
# if __name__ == '__main__':
#     asyncio.run(main())



'''
to_thread
'''
import asyncio
import time

def block_func(name: str):
    time.sleep(2)       # 模拟阻塞时间
    print(f"name = {name}")

async def foo():# 一个协程
    print("async foo")
    await asyncio.sleep(1)

async def main():
    await asyncio.gather(
        asyncio.to_thread(block_func, name="lczmx"), 
        foo()
        )

if __name__ == '__main__':
    t0 = time.perf_counter()
    asyncio.run(main())
    print(f"{time.perf_counter()-t0:.5f}s")