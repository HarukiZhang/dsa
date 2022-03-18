import asyncio
import time

'''
Final test result shows that:
    if using 'asyncio.create_task' and concurrently run following two of three async function,
        the process takes 32.6620827 sec but I can get two separate result lists,
        not only do I have to compile two more 'for loop' funcion,
        but also the main process get very slow.
    but if firsly creating a coroutine object list, and then using 'await asyncio.gather()',
        the process takes only 7.1880618 sec but the results are mixed in a single result list;
'''


async def facto(name, num):
    fc = 1
    for i in range(2, num + 1):
        print(f'T1_{name}:PRE{i-1}=={fc}  ', end='')
        await asyncio.sleep(0.3)
        fc *= i
    print(f'T1_{name}:{num}! == {fc} COMPLETE!')
    return f'{name}:{fc}'

async def cumsum(name, num):
    bs = 0
    for i in range(1, num + 1):
        print(f'T2_{name}:PRE{i-1}=={bs}  ', end='')
        await asyncio.sleep(0.1)
        bs += i
    print(f'T2_{name}:Result == {bs} COMPLETE!')
    return f'{name}:{bs}'

async def fabo(name, num):
    if num == 2 or num == 1:
        print(f'T3_{name}:Result == 1 COMPLETE!')
    else:
        nm1 = nm2 = 1
        for i in range(3, num + 1):
            pres = nm1 + nm2
            nm1, nm2 = pres, nm1
            print(f'T3_{name}:PRE {i}=={pres}  ', end='')
            await asyncio.sleep(0.2)
    print(f'T3_{name}:Result == {pres} COMPLETE!')
    return f'{name}:{pres}'

async def fun1():
    lst_T1 = []
    lst_name = ['A','B','C','D','E']
    for i in range(20,25):
        yield lst_T1.append(await facto(lst_name[i-20],i))

async def fun2():
    lst_T2 = []
    lst_name = ['A','B','C','D','E']
    for i in range(20,25):
        yield lst_T2.append(await cumsum(lst_name[i-20],i))

async def main():
    task1 = asyncio.create_task(fun1())
    task2 = asyncio.create_task(fun2())
    st0 = time.perf_counter()
    await task1
    await task2
    print(f'\n\nT Res: {task1.result()}\n{task2.result()}')
    print(time.perf_counter()-st0)
    # print(f'T1 Res:\n   {lst_resT1}\nT2 Res:\n   {lst_resT2}\nT3 Res:\n   {lst_resT3}')

async def main2():
    st0 = time.perf_counter()
    lst_T = []
    lst_name = ['A','B','C','D','E']
    for i in range(20,25):
        lst_T.append(facto(lst_name[i-20],i))
        lst_T.append(cumsum(lst_name[i-20],i))
    lst_res = await asyncio.gather(*lst_T)
    print(f'\n\nT Res: {lst_res}')
    print(time.perf_counter()-st0)
    return lst_res

# asyncio.run(main())
# asyncio.run(main2())