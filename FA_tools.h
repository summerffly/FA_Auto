
/*----------  CODE_ORIGIN @ 番茄  ----------*/

#include <iostream>
#include <string>

#include <fstream>
#include <iomanip>

#define MAX_COMMAND     64      // 命令最大字符数
#define MAX_LINE_CHAR   128     // 每行最大字符数
#define MAX_LINE        200     // 最大支持行数


// --------------- COMMAND Library --------------- //

const char *CMD_SC_MN = "sumck-mn";     // FA_Sum_Check_Month
const char *CMD_SC_SZ = "sumck-sz";     // FA_Sum_Check_SZ

const char *CMD_SU_MN = "sumup-mn";     // FA_Sum_Update_Month
const char *CMD_SU_SZ = "sumup-sz";     // FA_Sum_Update_SZ

const char *CMD_LM = "lmod";            // FA_Line_Modify

const char *CMD_DOWN = "down";


// --------------- NAMESPACE --------------- //

using namespace std;


/*----------  TOOLS @ 番茄  ----------*/

/* * * * * *  char to int  * * * * * */
int char2int(const char *num_char)
{
    int num_int = 0;
    
    for(int i=0; ; i++)
    {
        if(num_char[i] == '\0')
            break;
        
        num_int = (num_char[i] - 48) + num_int*10;
    }
    
    return num_int;
}

/* * * * * *  int to char  * * * * * */
char *int2char(const int num_int)
{
    char *num_char = new char[7];
    sprintf(num_char, "%d", num_int);
    return num_char;
}


/*----------  TOOLS @ 番茄  ----------*/

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


/* * * * * *  string原始金额查找  * * * * * */
int sm_StrMoneyFind_Origin(string str)
{
    char str_char[MAX_LINE_CHAR];
    
    strcpy(str_char, str.c_str());
    
    int money = 0;
    int m_flag = 0;
    
    for(int i=0; ;i++)
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
    
    int money = 0;
    int m_flag = 0;

    if(str_char[2] == '-')
    {
        m_flag = -1;
    }
    else if(str_char[2] == '+')
    {
        m_flag = 1;
    }
    
    for(int i=3; ; i++)
    {
        if(str_char[i] == '\0')
            break;
        
        money = (str_char[i] - 48) + money*10;
    }
    
    return (m_flag * money);
}


/* * * * * *  string月度金额查找  * * * * * */
int sm_StrMoneyFind_Month(string str)
{
    char str_char[MAX_LINE_CHAR];
    
    strcpy(str_char, str.c_str());
    
    int money = 0;
    int m_flag = 0;
    
    for(int i=0; ;i++)
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
    
    int money = 0;
    
    for(int i=3; ;i++)
    {
        if(str_char[i] == '`')
        {
            break;
        }

        money = (str_char[i] - 48) + money*10;
    }
    
    return money;
}


/* * * * * *    * * * * * */
int sm_StrMoneyReplace_Line(string &str, int delta)
{
    char str_char[MAX_LINE_CHAR];
    
    strcpy(str_char, str.c_str());
    
    int money = 0;
    int index = 0;
    
    for(int i=3; ; i++)
    {
        if(str_char[i] == '`')
            break;
        
        money = (str_char[i] - 48) + money*10;
        index++;
    }
    
    str.erase(3, index);
    str.insert(3, int2char(money+delta));
    
    return 0;
}


/* * * * * *    * * * * * */
int sm_StrMoneyReplace_Title(string &str, int delta)
{
    char str_char[MAX_LINE_CHAR];
    
    strcpy(str_char, str.c_str());

    int money = 0;
    int index = 0;
    
    for(int i=3; ; i++)
    {
        if(str_char[i] == '\0')
            break;
        
        money = (str_char[i] - 48) + money*10;
        index++;
    }
    
    cout << money << endl;
    
    str.erase(3, index);
    str.insert(3, int2char(money+delta));
    
    return 0;
}

/* * * * * *    * * * * * */
int sm_StrMoneyReplace_Month(string &str, int money_new)
{
    char str_char[MAX_LINE_CHAR];
    
    strcpy(str_char, str.c_str());
    
    int money = 0;
    int m_flag = 0;
    int index = 0;
    int tag = 0;
    
    for(int i=0; ;i++)
    {
        if(str_char[i] == '-')
        {
            tag = i+1;
            m_flag = -1;
            continue;
        }
        else if(str_char[i] == '+')
        {
            tag = i+1;
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
            index++;
        }
    }
    
    str = str.substr(0, (tag-1));
    
    
    if(money_new>=0)
    {
        str += "+";
    }
    
    str += int2char(money_new);
    
    return 0;
}


/*----------  CODE_END @ 番茄  ----------*/


