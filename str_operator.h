
/*----------  CODE_ORIGIN @ 番茄  ----------*/

#include <iostream>
#include <string>

#include "global.h"


using namespace std;


int sm_StrCnt(string strA, string strB);     // 声明


/* * * * * *  char to int  * * * * * */
int char2int(const char *num_char)
{
    int num_flag = 0;
    int num_int = 0;
    
    if(num_char[0] == '+')
    {
        num_flag = 1;
        
        for(int i=1; ; i++)
        {
            if(num_char[i] == '\0')
                break;
            
            num_int = (num_char[i] - 48) + num_int*10;
        }
    }
    else if(num_char[0] == '-')
    {
        num_flag = -1;
        
        for(int i=1; ; i++)
        {
            if(num_char[i] == '\0')
                break;
            
            num_int = (num_char[i] - 48) + num_int*10;
        }
    }
    else if(('0' <= num_char[0])&(num_char[0] <= '9'))
    {
        num_flag = 1;
        
        for(int i=0; ; i++)
        {
            if(num_char[i] == '\0')
                break;
            
            num_int = (num_char[i] - 48) + num_int*10;
        }
    }
    else
    {
        cout << "char2int error" << endl;
        return -1;
    }
    
    return (num_flag * num_int);
}


/* * * * * *  int to char  * * * * * */
char *int2char(const int num_int)
{
    char *num_char = new char[8];     // tip 番茄@20170813 - 支持到十万级
    sprintf(num_char, "%d", num_int);
    return num_char;
}


/* * * * * *  Write File  * * * * * */
int WirteFile(const char *file_name, const string *strLine, const int line_index)
{
    ofstream ofile(file_name);

    if(!ofile.is_open())
    {
        cout << "Write File Error" << endl;
        return -1;
    }
    
    for(int i = 1; i <= line_index; i++)
    {
        ofile << strLine[i].c_str() << endl;
        
        if(!sm_StrCnt(strLine[i], "---"))
        {
            break;
        }
    }
    
    ofile.close();
    
    return 0;
}


/* * * * * *  string包含匹配  * * * * * */
int sm_StrCnt(string strA, string strB)
{
    string::size_type index;

    index = strA.find(strB);
    
    if(index == string::npos )
    {
        return -1;
    }
    else
    {
        return 0;
    }
}


/* * * * * *  string最高层金额查找  * * * * * */
int sm_StrMoneyFind_Top(string str)
{
    char str_char[MAX_LINE_CHAR];
    
    strcpy(str_char, str.c_str());
    
    int m_flag = 0;
    int money = 0;
    
    for(int i=0; ; i++)
    {
        if(str_char[i] == '-')
        {
            m_flag = -1;
            continue;
        }
        else if(str_char[i] == '+')
        {
            m_flag = 1;
            continue;
        }
        else if(str_char[i] == '\0')
        {
            break;
        }
        
        if(m_flag != 0)
        {
            money = (str_char[i] - 48) + money*10;
        }
    }
    
    return (m_flag * money);
}


/* * * * * *  string分项金额查找  * * * * * */
int sm_StrMoneyFind_Title(string str)
{
    char str_char[MAX_LINE_CHAR];
    
    strcpy(str_char, str.c_str());
    
    int m_flag = 0;
    int money = 0;

    if(str_char[2] == '-')
    {
        m_flag = -1;
    }
    else if(str_char[2] == '+')
    {
        m_flag = 1;
    }
    else
    {
        cout << "format error" << endl;
        return -1;
    }
    
    for(int i=3; ; i++)
    {
        if(str_char[i] == '\0')
        {
            break;
        }
        
        money = (str_char[i] - 48) + money*10;
    }
    
    return (m_flag * money);
}


/* * * * * *  string月度金额查找  * * * * * */
int sm_StrMoneyFind_Month(string str)
{
    char str_char[MAX_LINE_CHAR];
    
    strcpy(str_char, str.c_str());
    
    int m_flag = 0;
    int money = 0;
    
    for(int i=0; ; i++)
    {
        if(str_char[i] == '-')
        {
            m_flag = -1;
            continue;
        }
        else if(str_char[i] == '+')
        {
            m_flag = 1;
            continue;
        }
        else if(str_char[i] == '\0')
        {
            break;
        }
        
        if(m_flag != 0)
        {
            money = (str_char[i] - 48) + money*10;
        }
    }
    
    return (m_flag * money);
}


/* * * * * *  string单行金额查找  * * * * * */
int sm_StrMoneyFind_Line(string str)
{
    char str_char[MAX_LINE_CHAR];
    
    strcpy(str_char, str.c_str());
    
    int m_flag = 0;
    int money = 0;
    
    if(str_char[1] == '-')
    {
        m_flag = -1;
    }
    else if(str_char[1] == '+')
    {
        m_flag = 1;
    }
    else
    {
        cout << "format error" << endl;
        return -1;
    }
    
    for(int i=3; ;i++)
    {
        if(str_char[i] == '`')
        {
            break;
        }

        money = (str_char[i] - 48) + money*10;
    }
    
    return (m_flag * money);
}


/* * * * * *  string最高层金额修改  * * * * * */
int sm_StrMoneyModify_Top(string &str, int money_new)
{
    char str_char[MAX_LINE_CHAR];
    
    strcpy(str_char, str.c_str());
    
    int m_tag = 0;
    
    for(int i=0; ;i++)
    {
        if(str_char[i] == '-')
        {
            m_tag = i+1;
            break;
        }
        else if(str_char[i] == '+')
        {
            m_tag = i+1;
            break;
        }
    }
    
    str = str.substr(0, (m_tag-1));
    
    if(money_new>=0)
    {
        str += "+";
        str += int2char(money_new);
    }
    else
    {
        str += int2char(money_new);
    }
    
    return 0;
}


/* * * * * *  string分项金额修改  * * * * * */
int sm_StrMoneyModify_Title(string &str, int money_new)
{
    char str_char[MAX_LINE_CHAR];
    
    strcpy(str_char, str.c_str());
    
    str = str.substr(0, 2);
    
    if(money_new>=0)
    {
        str += "+";
        str += int2char(money_new);
    }
    else
    {
        str += int2char(money_new);
    }
    
    return 0;
}


/* * * * * *  string月度金额修改  * * * * * */
int sm_StrMoneyModify_Month(string &str, int money_new)
{
    char str_char[MAX_LINE_CHAR];
    
    strcpy(str_char, str.c_str());
    
    int m_tag = 0;
    
    for(int i=0; ;i++)
    {
        if(str_char[i] == '-')
        {
            m_tag = i+1;
            break;
        }
        else if(str_char[i] == '+')
        {
            m_tag = i+1;
            break;
        }
    }
    
    str = str.substr(0, (m_tag-1));
    
    if(money_new>=0)
    {
        str += "+";
        str += int2char(money_new);
    }
    else
    {
        str += int2char(money_new);
    }
    
    return 0;
}


/* * * * * *  string单行金额修改  * * * * * */
int sm_StrMoneyModify_Line(string &str, int money_new)
{
    char str_char[MAX_LINE_CHAR];
    
    strcpy(str_char, str.c_str());
    
    int m_index = 0;
    
    for(int i=3; ; i++)
    {
        if(str_char[i] == '`')
            break;
        
        m_index++;
    }
    
    str.erase(1, (m_index+2));
    if(money_new>0)
    {
        str.insert(1, "+ ");
        str.insert(3, int2char(money_new));
    }
    else
    {
        str.insert(1, "- ");
        str.insert(3, int2char((-1)*money_new));
    }
    
    return 0;
}


/*----------  CODE_END @ 番茄  ----------*/


