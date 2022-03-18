import pandas as pd
from lxml import etree
import re
import asyncio
import pickle
from time import perf_counter as pfc


def extract_table(html: str):
    table = pd.read_html(io=html)
    for dtfm in table:
        if re.search(r'标的名称', dtfm.to_string(columns=[0])):
            return dtfm

def extract_accname_via_etree(html: str, extr_len=100):
    '''
    actually accn could only be contained in ct4 or ct5, not any ohter place
    '''
    h_etree = etree.HTML(html)
    for i in range(4,6):
        elem:list = h_etree.xpath(f'//*[@id="bd_detail_tab_ct{i}"]')
        e2str = etree.tostring(elem[0], method='text', encoding='utf-8').decode('utf-8')
        try:
            idx = e2str.index('户名')
        except ValueError:
            if not i == 5:
                continue
            return 'Not Found "Account Name" Signal'
        else:
            return e2str[idx + 3 : idx + extr_len].split('，')[0]

async def async_extract_table(lst_html: list):
    lst_result = []
    for html in lst_html:
        t1 = pfc()
        await asyncio.sleep(0)
        lst_result.append(extract_table(html))
        print(f'\r{t1-t0:.4f}s',end='')
    return lst_result

async def async_extract_accname_via_etree(lst_html: list, extr_len=100):
    lst_result = []
    for html in lst_html:
        t2 = pfc()
        await asyncio.sleep(0)
        lst_result.append(extract_accname_via_etree(html, extr_len))
        print(f'\r{t2-t0:.4f}s',end='')
    return lst_result

def callback(future):
    print(future.result()[56])

async def extract_infos_from_html(lst_html: list):   
    task1 = asyncio.create_task(async_extract_table(lst_html))
    task2 = asyncio.create_task(async_extract_accname_via_etree(lst_html))
    task1.add_done_callback(callback)
    task2.add_done_callback(callback)
    await task1
    await task2



'''
TEST

Final result: 10.9427s 
this time is even longer than not using asynchronization
'''
with open('Data\pickle_lst_html_carinfor.pkl','rb') as f:
    lst_html = pickle.load(f)
    f.close()

def cre_lst(lst):
    newlst = []
    for i in lst:
        newlst.append(i[1])
    return newlst

lst_text = cre_lst(lst_html)

t0 = pfc()
asyncio.run(extract_infos_from_html(lst_text))

# loop = asyncio.get_event_loop()
# lst_infoTable, lst_accname = loop.run_until_complete(extract_infos_from_html(lst_html=lst_text))