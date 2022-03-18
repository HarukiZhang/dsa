#include <iostream>
#include <stack>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;
//后序遍历：
string chang(char *str)
{
    stack<char> s;
    int len=strlen(str);
    int i;
    string st="";
    for(i=0; i<len; i++)
    {
        if(str[i]>='a'&&str[i]<='z')
            st=st+str[i];
        else if(str[i]>='A'&&str[i]<='Z')
            st=st+str[i];
        else if(str[i]>='0'&&str[i]<='9')
            st=st+str[i];
        else if(str[i]=='(')
            s.push(str[i]);
        else if(str[i]==')')
        {
            while(s.top()!='(')
            {
                st=st+s.top();
                s.pop();
            }
            s.pop();
        }
        else if(str[i]=='+'||str[i]=='-')
        {
            while(!s.empty()&&s.top()!='(')
            {
                st=st+s.top();
                s.pop();
            }
            s.push(str[i]);
        }
        else if(str[i]=='*')
        {
            while(!s.empty()&&s.top()!='('&&s.top()=='*')
            {
                st=st+s.top();
                s.pop();
            }
            s.push(str[i]);
        }
        else if(str[i]==' '||str[i]=='\t')
            continue;
    }
    
    while(!s.empty())
    {
        st=st+s.top();
        s.pop();
    }
    return st;
}
//用字符的编码来求值，字符ab...直接转换成int数据类型。
int get(string str)
{
    int len=str.size();
    int i,d,t;
    stack<int> s;
    for(i=0; i<len; i++)
    {
        if(str[i]>='a'&&str[i]<='z')
        {
            d=str[i];
            s.push(d);
        }
        else if(str[i]>='A'&&str[i]<='Z')
        {
            d=str[i];
            s.push(d);
        }
        else if(str[i]>='0'&&str[i]<='9')
        {
            d=str[i]-'0';      //注意这里不能再用字符的编码来计算了，要转换成相应的整数
            s.push(d);
        }
        else if(str[i]=='+')
        {
            d=s.top();
            s.pop();
            t=s.top();
            s.pop();
            s.push(d+t);
        }
        else if(str[i]=='-')
        {
            d=s.top();
            s.pop();
            t=s.top();
            s.pop();
            s.push(t-d);
        }
        else if(str[i]=='*')
        {
            d=s.top();
            s.pop();
            t=s.top();
            s.pop();
            s.push(d*t);
        }
    }
    t=s.top();
    s.pop();
    return t;
}

int main()
{
    int n,i;
    cin>>n;
    getchar();
    for(i=0;i<n;i++)
    {
        char stra[100],strb[100];
        cin.getline(stra, 100);
        string str1=chang(stra);
        int x1=get(str1);
        
        cin.getline(strb, 100);
        string str2=chang(strb);
        int x2=get(str2);
        
        if(x1==x2)
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }
    return 0;
}

