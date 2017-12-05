
/*--------------------  CODE_ORIGIN @ 番茄  --------------------*/

#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>

#include "global.h"

using namespace std;


/**************************************************/
//   生成 下个月份值
/**************************************************/
string GenNextMonth(const char *cur_month)
{
    unsigned int int_cur_month = atoi(cur_month);
    string str_nx_month;

    switch(int_cur_month)
    {
        case 1:
            str_nx_month += "02";
            break;
        case 2:
            str_nx_month += "03";
            break;
        case 3:
            str_nx_month += "04";
            break;
        case 4:
            str_nx_month += "05";
            break;
        case 5:
            str_nx_month += "06";
            break;
        case 6:
            str_nx_month += "07";
            break;
        case 7:
            str_nx_month += "08";
            break;
        case 8:
            str_nx_month += "09";
            break;
        case 9:
            str_nx_month += "10";
            break;
        case 10:
            str_nx_month += "11";
            break;
        case 11:
            str_nx_month += "12";
            break;
        case 12:
            str_nx_month += "01";
            break;
        default:
            break;
    }

    return str_nx_month;
}


/**************************************************/
//   生成 上个月份值
/**************************************************/
string GenPreMonth(const char *cur_month)
{
    unsigned int int_cur_month = atoi(cur_month);
    string str_pre_month;

    switch(int_cur_month)
    {
        case 1:
            str_pre_month += "12";
            break;
        case 2:
            str_pre_month += "01";
            break;
        case 3:
            str_pre_month += "02";
            break;
        case 4:
            str_pre_month += "03";
            break;
        case 5:
            str_pre_month += "04";
            break;
        case 6:
            str_pre_month += "05";
            break;
        case 7:
            str_pre_month += "06";
            break;
        case 8:
            str_pre_month += "07";
            break;
        case 9:
            str_pre_month += "08";
            break;
        case 10:
            str_pre_month += "09";
            break;
        case 11:
            str_pre_month += "10";
            break;
        case 12:
            str_pre_month += "11";
            break;
        default:
            break;
    }

    return str_pre_month;
}


/**************************************************/
//   检查 char型 数字格式
/**************************************************/
int char0check(const char *num_char)
{
    string pattern_NumCheck = "^(\\+|-?)(\\d+)$";
    regex RE_NumCheck(pattern_NumCheck);

    string str_NumCheck = string(num_char);

    if( !regex_match(str_NumCheck, RE_NumCheck) )
    {
        cout << "----------------------------------------" << endl;
        cout << ">>>        Number Format Error       <<<" << endl;
        cout << "----------------------------------------" << endl;
        return -1;
    }

    return 0;
}


/**************************************************/
//   char型 转换 int型
/**************************************************/
int char2int(const char *num_char)
{
    return atoi(num_char);
}


/**************************************************/
//   int型 转换 char型
/**************************************************/
char *int2char(const int num_int)
{
    char *num_char = new char[8];     // tips 番茄@20170813 - 支持到十万级

    if(num_int > 0)
    {
        sprintf(num_char, "+%d", num_int);
    }
    else if(num_int < 0)
    {
        sprintf(num_char, "%d", num_int);
    }
    else
    {
        sprintf(num_char, "-%d", num_int);
    }
    
    delete []num_char;
    return num_char;
}


/**************************************************/
//   unsigned int型 转换 char型
/**************************************************/
char *uint2char(const unsigned int num_int)
{
    char *num_char = new char[8];     // tips 番茄@20170813 - 支持到十万级

    sprintf(num_char, "%d", num_int);
    
    delete []num_char;
    return num_char;
}


/**************************************************/
//   检查文件存在
/**************************************************/
int CheckFile(const char *file_name)
{
    ifstream ifile(file_name);
    
    if(!ifile.is_open())
    {
        cout << "----------------------------------------" << endl;
        cout << ">>>        Check File Failure        <<<" << endl;
        cout << "----------------------------------------" << endl;
        return -1;
    }
    
    ifile.close();
    
    return 0;
}


/* * * * * * * * * * * * * * * * * * 
             读文件 
* * * * * * * * * * * * * * * * * */
int ReadFile(const char *file_name, string *strLine, int &line_index)
{
    char buffer[MAX_LINE_CHAR];
    
    ifstream ifile(file_name);

    if(!ifile.is_open())
    {
        cout << "----------------------------------------" << endl;
        cout << ">>>          Read File Error         <<<" << endl;
        cout << "----------------------------------------" << endl;
        return -1;
    }

    while(!ifile.eof())
    {
        ifile.getline(buffer, MAX_LINE_CHAR);
        strLine[line_index] = buffer;

        if( regex_match(strLine[line_index], RE_end) )
        {
            break;
        }
        
        line_index++;
    }
    
    ifile.close();
    
    return 0;
}


/* * * * * * * * * * * * * * * * * * 
             写文件 
* * * * * * * * * * * * * * * * * */
int WirteFile(const char *file_name, const string *strLine, const int line_index)
{
    ofstream ofile(file_name);

    if(!ofile.is_open())
    {
        cout << "----------------------------------------" << endl;
        cout << ">>>         Write File Error         <<<" << endl;
        cout << "----------------------------------------" << endl;
        return -1;
    }
    
    for(int i = 1; i <= line_index; i++)
    {
        ofile << strLine[i].c_str() << endl;
        
        if( regex_match(strLine[i], RE_end) )
        {
            break;
        }
    }
    
    ofile.close();
    
    return 0;
}


/* * * * * * * * * * * * * * * * * * 
          写文件_插入一行 
* * * * * * * * * * * * * * * * * */
int InsertFile(const char *file_name, const string strInertLine, const int insert_index)
{
    string strLine[MAX_LINE];    
    int line_index = 1;
    
    if( ReadFile(file_name, strLine, line_index) == -1 )
    {
        return -1;
    }

    for(int i = 1; i <= line_index; i++)
    {
        if( i == insert_index )
        {
            line_index++;            
            for(int j = line_index; j > i; j--)
            {
                strLine[j] = strLine[j-1];
            }
            strLine[i] = strInertLine;
        }
    }

    if(WirteFile(file_name, strLine, line_index) == -1)
    {
        return -2;
    }
    
    return 0;

}


/*---------------------------------------------------------------*/
/*--------------------  string处理函数 @ 番茄  --------------------*/
/*---------------------------------------------------------------*/

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
    
    str += int2char(money_new);
    
    return 0;
}


/* * * * * *  string分项金额修改  * * * * * */
int sm_StrMoneyModify_Title(string &str, int money_new)
{
    char str_char[MAX_LINE_CHAR];
    
    strcpy(str_char, str.c_str());
    
    str = str.substr(0, 2);

    str += int2char(money_new);

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

    str += int2char(money_new);
    
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
    str.insert(1, int2char(money_new));
    str.insert(2, " ");

    #if 0
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
    #endif
    
    return 0;
}

/**************************************************/
//   string单行金额生成 
/**************************************************/
string sm_StrGenerator_Line(const bool pnFlag, const unsigned int value, const char *line_char)
{
    string str;
    
    if(pnFlag == false)
    {
        str += "`- ";
    }
    else
    {
        str += "`+ ";
    }
    str += uint2char(value);
    str += "` ";
    str += line_char;
    
    return str;
}


/*--------------------  CODE_END @ 番茄  --------------------*/


