# Try to look up 'deposit values' when requesting HTML with pyppeteer
import asyncio
from pyppeteer import launch
import pandas as pd
import time

def create_lst_task_url(dataframe, lst_tsk_len:int):
    '''
    : param lst_tsk_len: notify that it determines concurrently running numbers of tasks
    '''
    homepage = 'https://jpxkc.cbex.com'
    srs_url = dataframe['deep_url']
    srs_tit = dataframe['title']
    lst_task_url = []
    lst_title = []
    for i in range(len(srs_url)//lst_tsk_len):
        imlst_1 = []
        imlst_2 = []
        for k in range(lst_tsk_len):
            imlst_1.append(homepage + srs_url[i * lst_tsk_len + k])
            imlst_2.append(srs_tit[i * lst_tsk_len + k])
        lst_task_url.append(imlst_1)
        lst_title.append(imlst_2)
    imlst_1 = []
    imlst_2 = []
    for i in range(len(srs_url) - len(srs_url)%lst_tsk_len, len(srs_url)):
        imlst_1.append(homepage + srs_url[i])
        imlst_2.append(srs_tit[i])
    lst_task_url.append(imlst_1)
    lst_title.append(imlst_2)
    return lst_task_url, lst_title

async def page_control(url, browser):
    page = await browser.newPage()
    # await page.setViewport(viewport={"width": width, "height": height})
    await page.setJavaScriptEnabled(enabled=True)
    await page.setUserAgent(
        'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 '
        '(KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36 Edge/16.16299')
    xpathPromise = asyncio.ensure_future(page.waitForXPath('/html/body/div[6]/div[2]/div[1]/div[2]/div[6]/ul/li[1]/span[3]'))
    print(f'\r{time.perf_counter()-t0:.3f}s',end='')
    try: # Notify waitForXPath timeout default 30 sec => raise Exception
        await page.goto(url)  # indirectly cause a navigation(?)
        await xpathPromise  # Wait until element which matches xpath appears on page
    except TimeoutError:
        result = 'TimeoutError'
    else:
        result = await (await xpathPromise.result().getProperty('textContent')).jsonValue()
        # target = await page.xpath('/html/body/div[6]/div[2]/div[1]/div[2]/div[6]/ul/li[1]/span[3]')
        # result = await (await target[0].getProperty('textContent')).jsonValue()
        # task = await asyncio.create_task(target[0].getProperty('textContent'))
        # done, _ = await asyncio.wait({task})
        # jshandle = done.result()
        # result = await jshandle.jsonValue()
    # await asyncio.sleep(3)
    # await page_close(browser) # page_close() should surrender to main()
    await page.close()
    print(f'\r{time.perf_counter()-t0:.3f}s',end='')
    return result

async def browser_control(lst_task_url):
    # lst_task_url should be a 2D url list; len of second dimens defines concurrently running no.
    browser = await launch(
        {
            'headless': False, 
            'userDataDir': r'D:/haruk/Documents/PythonCodes/Temp', 
            'args': ['--no-sandbox'], 
            'dumpio': True
            }
            )
    # encapsule coroutine (lst_task)
    lst_task = []
    for item in lst_task_url:
        imlst = []
        for subitem in item:
            imlst.append(page_control(url=subitem, browser=browser))
        lst_task.append(imlst)
    # execute tasks
    lst_result = []
    for i in range(len(lst_task)):
        print(f'\r{time.perf_counter()-t0:.3f}s',end='')
        result = await asyncio.gather(*lst_task[i])
        lst_result.append(result)
        print(f'\r{time.perf_counter()-t0:.3f}s',end='')
        # await page_close(browser) # seems browser.pages() cannot connect to the page that has already been assigned a handle name
    # await browser.close() # Please manually close the chrome
    return lst_result

def main():
    dtfm_car = pd.read_pickle('Data/car_info_download_comparLst.pkl')
    lst_task_url, lst_title = create_lst_task_url(dataframe=dtfm_car, lst_tsk_len=8)
    global t0
    t0 = time.perf_counter()
    print('Task Starts')

    loop = asyncio.get_event_loop()

    lst_depoVal = loop.run_until_complete(browser_control(lst_task_url))

    print(f'Download complete: {time.perf_counter()-t0:.4f}s')

    lst_sv = []
    for i in range(len(lst_depoVal)):
        for k in range(len(lst_depoVal[i])):
            lst_sv.append([lst_title[i][k], lst_depoVal[i][k]])

    dtfm_sv = pd.DataFrame(lst_sv, columns=['title', 'deposit_values'])
    dtfm_sv.to_excel('Data/deposit_values.xlsx')

'''
TEST
'''
if __name__=='__main__':
    main()

# width, height = screen_size()
# p_url = 'https://jpxkc.cbex.com/jpxkc/prj/detail/157387.html'

# await asyncio.wait([
    #     page.click('a.my-link'),
    #     page.waitForNavigation(),
    # ])