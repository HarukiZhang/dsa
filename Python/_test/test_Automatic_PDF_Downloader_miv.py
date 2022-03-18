# -*- coding: utf-8 -*-

def getHTMLtext(page_url):
    import requests as rq
    try:
        html=rq.get(page_url,headers={"user-agent":"chrome/10"},timeout=30)
        html.raise_for_status() # If status != 200, cause HTTPError
        html.encoding = html.apparent_encoding
        return html.text
    except:
        return "get page html Error"

def customizedCDN_4_soupFindAll(tag):
    if tag.name=="p" and tag.has_attr('class') and not tag.contents[0].name=="strong" and not tag.has_attr('align'): 
        return True

def createComparasionList(soupResultSet):
    reslst=[]
    imlst=[]
    for i in soupResultSet:
        if not i.a == None:
            hpath = i.a.attrs['href']
        else:
            hpath = None
                
        if len(i) == None or len(i) == 1:
            fname=i.string
        else:
            for k in i.strings:
                imlst.append(k)
            fname=".".join(imlst)
            imlst=[]
        reslst.append([fname,hpath])
    return reslst

def formalizeFilename(invalid_string: str):
    ''' After createComparasionList function, there are only String or NoneType in the list,
    we can assert that: if an element is a NoneType, it can not be what we desire or require;
    Therefore, we can simply change "undesired items" into NoneType as a remark for checkListAvailability function to operate '''
    import re
    
    frmd_str=re.sub(repl='', pattern=r'\xa0+|\u3000+|\r+|\n+|\.', string=invalid_string) # pop out these unvalid characters
    frmd_str=re.sub(repl='_', pattern=r'[\\\/:*?"<>|\s]+', string=frmd_str) # substitute these syms [\/:*?"<>|.] and space chr into underline '_'
    # frmd_str=re.sub(repl='_', pattern=r'_[\W]+', string=frmd_str)      # probably mistakely truncate '_('
    frmd_str=re.sub(repl='_', pattern=r'__+', string=frmd_str) # trim any redundent underline "_"
    
    if len(frmd_str) > 200: # check for string length
        frmd_str= frmd_str[:190]+'[Trmd]'
    frmd_str=frmd_str.strip('_.pdf') + '.pdf'
    
    matchchk=re.match('^\.pdf$',frmd_str) # If a filename only contain ".pdf", this row of list can not contain target url;
    if matchchk:
        frmd_str=None
    return frmd_str

def checkListAvailability(compar_lst: list, prt_opt: bool):
    ''' Attention: The logic of this function is as follow:
        CDN 1: check both filename column and url column, if both NoneType, then remove whole row;
        CDN 2: if url col is a valid url(how to decide?), but filename col is None, then complete filename from url;
        CDN 3: if filename not None, url None, then preserve this row; '''
    itera=cdn1=cdn2=cdn3 = 0
    chklst=[]
    "Loop for check"
    for ls in compar_lst:
        try:
            idx=ls.index(None)
        except ValueError: # Generally, ValueError raising implys: present row of list is available;
            continue
        else:
            if idx == 0:
                count=ls.count(None)
                if count == 1:
                    ls[0] = ls[1].split("/")[-1] + '.pdf'
                    cdn2 += 1
                elif count == 2:
                    chklst.append(itera)
            elif idx == 1:
                cdn3 += 1
        finally:
            itera+=1
    "Starting list pop"
    if not chklst == None:
        for i in chklst:
            k = i - cdn1
            compar_lst.pop(k)
            cdn1 += 1
    "Give No. to all filename"
    gno = 0
    for ls in compar_lst:
        ls[0] = '{:0>3d}_'.format(gno) + ls[0]
        gno += 1
    "Optional printing"    
    if prt_opt:
        print('After availability check, Comparasion List length: {0},\n\
        {1} row(s) have been entirely removed;\n\
        {2} row(s) whose filename column(s) has been completed form url;\n\
        {3} row(s) who only have filename but no url matched.'.format(len(compar_lst),cdn1,cdn2,cdn3))

def getPDFdown(d_url,d_path):
    import requests as rq

    try:
        html=rq.get(d_url,headers={"user-agent":"chrome/10"},timeout=30)
        html.raise_for_status() # If status != 200, raise Error
    except:
        stts = (-1, 'get_PDF_down Error @ request')
    else:
        try:
            with open(d_path,"wb") as f:
                f.write(html.content)
                f.close()
        except:
            stts = (0, 'get_PDF_down Error @ filesaving')
        else:
            stts = (1, 'get_PDF_down Success!')
    return stts

def writeLst_2_xlsx(lst4save: list, lst_title: list, savename: str):
    'For each row of lst4save, the length should be same and do not has any lack of value'
    'lst4save should be 2 dimensional'
    import pandas
    import numpy as np
    
    lst4save_np = np.array(lst4save)
    stts = ''
    if not lst4save_np.shape[1] == len(lst_title):
        stts = 'Title Dimensions do not match.'
        return stts
    else:
        dct4save = {}
        for i in range(len(lst_title)):
            dct4save[lst_title[i]] = lst4save_np[:,i]
    
        datfra = pandas.DataFrame(dct4save)
    
        try:
            datfra.to_excel(savename + '.xlsx') # default path = D://.../pathoncodes
        except:
            stts = 'Saving Lists to xlsx Error'
        else:
            stts = 'Saving Lists to xlsx Success'
    return stts

def mainPro(comparLst: list, homepage: str, root: str, svlst_title: list, svlst_fname: str):
        
    ttlen = len(comparLst)
    print(' Downloading Initiate '.center(110,'='))
    itrial=0
    imstr=''
    for ls in comparLst:
        if ls[1] == None:
            imstr = "File No.{} [No url found]".format(itrial)
        elif not ls[0] == None:
            d_url = homepage + ls[1]
            d_path = root + ls[0]
            'initiate download'
            stts = getPDFdown(d_url,d_path)
            if stts[0] == 0: # that is, content-getting successed but file-writting failed => probably due to invalid filename
                d_path = root + '{:0>3d}_[RETRY]_'.format(itrial) + ls[1].split('/')[-1] # try grep a filename from d_url
                stts = getPDFdown(d_url,d_path)
                imstr = "File No.{0} [{1}]".format(itrial,stts[1])
            else:
                imstr = "File No.{0} [{1}]".format(itrial,stts[1])                
        ls.append(imstr)
        'print a processing text bar'
        per = int(itrial/ttlen*100*100/99)
        lfbr = '*' * per
        rtbr = '-' * (100 - per)
        print('\r{0:^3d}%[{1}->{2}]'.format(per, lfbr, rtbr),end='')
        'Tteration Counter +1'
        itrial+=1
    print('\n' + ' Downloading Complete '.center(110,'='))

    stts_wL2x = writeLst_2_xlsx(comparLst, svlst_title, svlst_fname)
    print(stts_wL2x)





'Main process - Part I: Comparasion List'
from bs4 import BeautifulSoup

p_url = 'http://bilab.bnu.edu.cn/publication.html'
p_html = getHTMLtext(p_url)

soup= BeautifulSoup(p_html,'html.parser')
  
sfa_lst=soup(customizedCDN_4_soupFindAll)
print("Please check for the length of Soup_find_all lists is now: ",len(sfa_lst))

comparLst=createComparasionList(sfa_lst)

'Formalizing filename column'
for ls in comparLst:
    ls[0]=formalizeFilename(ls[0]) # user dicides which column is filename column;

'Check for availability of the Comparasion List'
checkListAvailability(comparLst, prt_opt=1)




'Main process - Part II: Initiating download'

homepage='http://bilab.bnu.edu.cn/'
root='D:/haruk/Documents/PythonCodes/Downloads/'

svlst_title = ['filename','url','download_status']
svlst_fname = 'ComparList_Test5'

mainPro(comparLst, homepage, root, svlst_title, svlst_fname)