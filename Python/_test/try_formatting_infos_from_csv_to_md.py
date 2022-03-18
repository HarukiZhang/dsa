def formating_from_csv_to_md(csv_path: str, use_cols: list, templ:str):
    '''
    Usage: extract inforamtion from csv and write to markdown according with the given template;

    :param use_cols: 
        should include all information that you intend to show in the markdown;
        should always include 'J9', 'CR' and put them in the end of list;
    
    Notes: Output path is assigned to: './Project/'
    '''

    import re
    import pandas as pd

    dtfm = pd.read_csv(
        csv_path,
        header=0, index_col=False, usecols=use_cols, keep_default_na=False, encoding='UTF_8'
    )

    lst_output = []
    for row in range(dtfm.shape[0]): # single for_loop for all process
        au = dtfm.loc[row]['AU'].split('; ')[0].replace(',', '')        

        filename = au +', '+ str(dtfm.loc[row]['PY']) +', '+ dtfm.loc[row]['J9'] +'.md'

        templst_1 = []
        for each_CR in dtfm.loc[row]['CR'].split('; '):
            temp_CR = re.sub(r'[\[\]]+', repl='', string=each_CR)
            templst_2 = []
            for part in temp_CR.split(', '):
                if not re.match(r'^[PV][\d]*$|^DOI ', part): # ths ver trying to remove DOI in filename & content link
                    templst_2.append(part)
            templst_1.append('[[' + ', '.join(templst_2) + ']]')
        output_CR = '\n'.join(templst_1)
        
        output_UT = dtfm.loc[row]['UT'].replace('WOS:','')

        output_AU = set_tag_to_Bi(dtfm.loc[row,'AU'])

        filecontent = templ.format(
            dtfm.loc[row][use_cols[0]],       #0
            output_AU,                        #1
            dtfm.loc[row][use_cols[2]],       #2
            dtfm.loc[row][use_cols[3]],       #3
            dtfm.loc[row][use_cols[4]],       #4
            dtfm.loc[row][use_cols[5]],       #5
            dtfm.loc[row][use_cols[6]],       #6
            dtfm.loc[row][use_cols[7]],       #7
            dtfm.loc[row][use_cols[8]],       #8
            output_UT,                        #9
            output_CR,                        #10
            str(dtfm.loc[row][use_cols[10]]), #11
            str(dtfm.loc[row][use_cols[11]]), #12
            str(dtfm.loc[row][use_cols[12]]), #13
            str(dtfm.loc[row][use_cols[13]])  #14
        )

        lst_output.append((filename, filecontent))
    
    # save files:
    for i in range(len(lst_output)):
        with open(f'./Projects/{lst_output[i][0]}', 'xt', encoding='UTF_8') as f:
            f.write(lst_output[i][1])
            f.close()

    # return lst_output, dtfm

def set_tag_to_Bi(authors:str):
    import re

    lst_au = []
    for author in authors.split('; '):
        if re.match(r'B[iI], YC?|B[iI], Yanchao', author):
            lst_au.append('#BiYC')
        else:
            lst_au.append(author)
    return '; '.join(lst_au)



'''
Initiation
'''

path = 'Data/CiteAnalysisData/'
#       0     1    2   3    4    5    6    7    8    9    10    11   12    13     
use = ['TI','AU','PY','DT','SO','AB','DE','ID','DI','UT','NCR','TC','LCS','LCR','J9','CR']
template = '''---
Alias: NeuroBasis
TC: {12}
LCS: {13}
LCR: {14}
---
#show_on
**Title**: {0}
**Authors**: {1}
**PubYear**: #PY{2}
**DocType**: #{3}
**Journal**: {4}
> **Abstract**:
> {5}

**AuthKW**: {6}
**Keywords+**: {7}
**DOI**: {8}
**WoS**: {9}

#### CitedRefs: ({11})
{10}'''

formating_from_csv_to_md(csv_path=path, use_cols=use, templ=template)