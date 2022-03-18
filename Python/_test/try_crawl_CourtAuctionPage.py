import asyncio
from pyppeteer import launch

def screen_size():
    import tkinter
    tk = tkinter.Tk()
    width = tk.winfo_screenwidth()
    height = tk.winfo_screenheight()
    tk.quit()
    return width, height

async def get_html(url):
    browser = await launch(headless=False)
    page = await browser.newPage()    
    width, height = screen_size()
    await page.setViewport(viewport={"width": width, "height": height})
    await page.setJavaScriptEnabled(enabled=True)
    await page.setUserAgent(
        'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 '
        '(KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36 Edge/16.16299'
    )
    await page.goto(url)
	# await page.evaluate()
	# await page.evaluateOnNewDocument('()=>{Obeject.defineProperties(navigator, {webdriver:{get:() => false}})}')
    text = await page.content()
    return text

async def page_close(browser):
    await browser.close()



p_url = 'https://jpxkc.cbex.com/jpxkc/zc_prjs/1064.html'

m = asyncio.ensure_future(get_html(p_url))
asyncio.get_event_loop().run_until_complete(m)

# m = asyncio.ensure_future(asGetHtml(p_url))
# asyncio.get_event_loop().run_until_complete(m)
# m.result()