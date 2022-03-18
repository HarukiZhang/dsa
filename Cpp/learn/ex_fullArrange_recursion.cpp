#include<iostream>
using namespace std;
 
int n = 0; 
 
void swap(int *a, int *b)
{    
    int m;    
    m = *a;    
    *a = *b;    
    *b = m;
} 
void perm(int list[], int k, int m)
{    
    int i;    
    if(k > m)    
    {         
        for(i = 0; i <= m; i++)    
			cout << list[i] << " ";
		cout << endl;       
        n++;    
    }    
    else    
    {        
        for(i = k; i <= m; i++)        
        {            
            swap(&list[k], &list[i]);            
            perm(list, k + 1, m);            
            swap(&list[k], &list[i]);        
        }    
    }
}
int main()
{    
    int list[] = {1, 2, 3, 4, 5};    
    perm(list, 0, 4);
	cout << "total: " << n;  
    return 0;
}