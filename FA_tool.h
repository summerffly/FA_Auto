
/*--------------------  CODE_ORIGIN @ 番茄  --------------------*/

#pragma once

#include "global.h"
#include "FBric_operator.h"

using namespace std;


/**************************************************/
//   打印.md文件全部内容
/**************************************************/
int FA_Print_File(const char *file_name)
{    
    string strLine[MAX_LINE];
    int line_index = 1;
    
    if( ReadFile(file_name, strLine, line_index) == -1 )
    {
        return -1;
    }
    
    for(int i = 1; i <= line_index; i++)
    {
        cout << "line_" << i << " // " << strLine[i].c_str() << endl;
    }
    
    return 0;
}

/**************************************************/
//   搜索.md文件某一行
/**************************************************/
int FA_Search_Line(const char *file_name, const char *line_key)
{
    string strLine[MAX_LINE];    
    int line_index = 1;       // 每一行的标志 从1开始计数 返回0可能有别的用途
    int line_counter = 0;     // 匹配行的计数器
    int line_tag = 0;         // 匹配行的标志

    string str_key = line_key;
    string pattern_key = "^.*" + str_key + ".*$";
    regex RE_key(pattern_key);
    
    if( ReadFile(file_name, strLine, line_index) == -1 )
    {
        return -1;
    }

    for(int i = 1; i <= line_index; i++)
    {
        if( regex_match(strLine[i], RE_key) )
        {
            if( line_counter == 0 )
            {
                line_tag = i;
            }
            line_counter++;
        }
    }
    
    if(line_counter > 0)
    {
        if(line_counter == 1)
        {
            return line_tag;
        }
        else
        {
            cout << "----------------------------------------" << endl;
            cout << ">>>        MULTI-LINES MATCHED       <<<" << endl;
            cout << "----------------------------------------" << endl;
            return -1;
        }
    }
    else
    {
        cout << "----------------------------------------" << endl;
        cout << ">>>          NO-LINE MATCHED         <<<" << endl;
        cout << "----------------------------------------" << endl;
        return -2;
    }
}

/**************************************************/
//   打印.md文件某一行 (按照关键字)
/**************************************************/
int FA_Print_Line_Key(const char *file_name, const char *line_key)
{
    string strLine[MAX_LINE];
    int line_index = 1;               // 每一行的标志 从1开始计数 返回0可能有别的用途
    int line_counter = 0;             // 匹配行的计数器
    int line_tag[MAX_LINE] = {0};     // 匹配行的标志

    string str_key = line_key;
    string pattern_key = "^.*" + str_key + ".*$";
    regex RE_key(pattern_key);
   
    if( ReadFile(file_name, strLine, line_index) == -1 )
    {
        return -1;
    }

    for(int i = 1; i <= line_index; i++)
    {
        if( regex_match(strLine[i], RE_key) )
        {
            line_counter++;
            line_tag[line_counter] = i;
        }
    }
    
    if(line_counter > 0)
    {
        if(line_counter == 1)
        {
            cout << "----------------------------------------" << endl;
            cout << "line_" << line_tag[1] << " // " << strLine[line_tag[1]].c_str() << endl;
            cout << "----------------------------------------" << endl;
            cout << ">>>       SINGLE-LINE MATCHED        <<<" << endl;
            cout << "----------------------------------------" << endl;
            return line_tag[1];
        }
        else
        {
            cout << "----------------------------------------" << endl;
            for(int i=1; i<=line_counter; i++)
            {
                cout << "line_" << line_tag[i] << " // " << strLine[line_tag[i]].c_str() << endl;
            }
            cout << "----------------------------------------" << endl;
            cout << ">>>        MULTI-LINES MATCHED       <<<" << endl;
            cout << "----------------------------------------" << endl;
            return -1;
        }
    }
    else
    {
        cout << "----------------------------------------" << endl;
        cout << ">>>          NO-LINE MATCHED         <<<" << endl;
        cout << "----------------------------------------" << endl;
        return -2;
    }
}


/**************************************************/
//   打印.md文件某一行 (按照行号)
/**************************************************/
string FA_Print_Line_Index(const char *file_name, const int line_id)
{
    string strLine[MAX_LINE];
    int line_index = 1;               // 每一行的标志 从1开始计数 返回0可能有别的用途

    if( ReadFile(file_name, strLine, line_index) == -1 )
    {
        string strError("Error");
        return strError;
    }

    if( (line_id <= 0) || (line_id > line_index) )
    {
        string strError("Line ID Error");
        return strError;
    }

    return strLine[line_id];
}


/**************************************************/
//   两行区间内 搜索.md文件某一行
/**************************************************/
int FA_Search_Line_Area(const char *file_name, const char *line_key, const int line_start, const int line_end)
{
    string strLine[MAX_LINE];    
    int line_index = 1;       // 每一行的标志 从1开始计数 返回0可能有别的用途
    int line_counter = 0;     // 匹配行的计数器
    int line_tag = 0;         // 匹配行的标志

    string str_key = line_key;
    string pattern_key = "^.*" + str_key + ".*$";
    regex RE_key(pattern_key);
    
    if( ReadFile(file_name, strLine, line_index) == -1 )
    {
        return -1;
    }

    for(int i = line_start; i <= line_end; i++)
    {
        if( regex_match(strLine[i], RE_key) )
        {
            if( line_counter == 0 )
            {
                line_tag = i;
            }
            line_counter++;
        }
    }
    
    if(line_counter > 0)
    {
        if(line_counter == 1)
        {
            return line_tag;
        }
        else
        {
            cout << "----------------------------------------" << endl;
            cout << ">>>        MULTI-LINES MATCHED       <<<" << endl;
            cout << "----------------------------------------" << endl;
            return -1;
        }
    }
    else
    {
        cout << "----------------------------------------" << endl;
        cout << ">>>          NO-LINE MATCHED         <<<" << endl;
        cout << "----------------------------------------" << endl;
        return -2;
    }
}


/**************************************************/
//   两行区间内 打印.md文件某一行
/**************************************************/
int FA_Print_Line_Area(const char *file_name, const char *line_key, const int line_start, const int line_end)
{
    string strLine[MAX_LINE];
    int line_index = 1;               // 每一行的标志 从1开始计数 返回0可能有别的用途
    int line_counter = 0;             // 匹配行的计数器
    int line_tag[MAX_LINE] = {0};     // 匹配行的标志

    string str_key = line_key;
    string pattern_key = "^.*" + str_key + ".*$";
    regex RE_key(pattern_key);
   
    if( ReadFile(file_name, strLine, line_index) == -1 )
    {
        return -1;
    }

    for(int i = line_start; i <= line_end; i++)
    {
        if( regex_match(strLine[i], RE_key) )
        {
            line_counter++;
            line_tag[line_counter] = i;
        }
    }   
    
    if(line_counter > 0)
    {
        if(line_counter == 1)
        {
            cout << "----------------------------------------" << endl;
            cout << "line_" << line_tag[1] << " // " << strLine[line_tag[1]].c_str() << endl;
            cout << "----------------------------------------" << endl;
            cout << ">>>       SINGLE-LINE MATCHED        <<<" << endl;
            cout << "----------------------------------------" << endl;
            return line_tag[1];
        }
        else
        {
            cout << "----------------------------------------" << endl;
            for(int i=1; i<=line_counter; i++)
            {
                cout << "line_" << line_tag[i] << " // " << strLine[line_tag[i]].c_str() << endl;
            }
            cout << "----------------------------------------" << endl;
            cout << ">>>        MULTI-LINES MATCHED       <<<" << endl;
            cout << "----------------------------------------" << endl;
            return -1;
        }
    }
    else
    {
        cout << "----------------------------------------" << endl;
        cout << ">>>          NO-LINE MATCHED         <<<" << endl;
        cout << "----------------------------------------" << endl;
        return -2;
    }
}

/**************************************************/
//   同步 <<< FA_TVT <-> life.M >>> 月度支出
/**************************************************/
int FA_Sync_Month(const int line_tag_life, const int line_tag_sz)
{
    string strLine_life[MAX_LINE];
    string strLine_sz[MAX_LINE];
    int line_index_life = 1;
    int line_index_sz = 1;
    
    if( ReadFile("./life.M.md", strLine_life, line_index_life) == -1 )
    {
        return -1;
    }

    if( ReadFile("./FA_TVT.md", strLine_sz, line_index_sz) == -1 )
    {
        return -1;
    }

    strLine_sz[line_tag_sz+1] = strLine_life[line_tag_life+1];
    strLine_sz[line_tag_sz+2] = strLine_life[line_tag_life+2];
    strLine_sz[line_tag_sz+3] = strLine_life[line_tag_life+3];

    WirteFile("./FA_TVT.md", strLine_sz, line_index_sz);
    
    return 0;
}


/*----------------------------------------------------------------*/
/*--------------------  FA_Line处理函数 @ 番茄  --------------------*/
/*----------------------------------------------------------------*/

// tip 番茄@20170818 - money_mod默认为消费，默认为减法操作
int FA_Line_Modify(const char *file_name, const int line_id, const int money_mod)
{
    string strLine[MAX_LINE];    
    int line_index = 1;
    
    if( ReadFile(file_name, strLine, line_index) == -1 )
    {
        return -1;
    }

    for(int i = 1; i <= line_index; i++)
    {
        if( i == line_id )
        {
            int money_new = sm_StrMoneyFind_Line(strLine[i]) - money_mod;
            sm_StrMoneyModify_Line(strLine[i], money_new);
        }
    }
        
    if(WirteFile(file_name, strLine, line_index) == -1)
    {
        return -2;
    }
    
    //cout << "----------------------------------------" << endl;
    //cout << ">>>           LINE MODIFIED          <<<" << endl;
    //cout << "----------------------------------------" << endl;
    
    return 0;
}


// tip 番茄@20170818 - money默认为消费，默认为减法操作
int FA_Line_Add(const char *file_name, const int line_id, const bool pnFlag, const unsigned int value, const char *line_char)
{
    string strInsertLine = sm_StrGenerator_Line(pnFlag, value, line_char);

    InsertFile(file_name, strInsertLine, line_id);
    
    cout << "----------------------------------------" << endl;
    cout << ">>>            LINE ADDED            <<<" << endl;
    cout << "----------------------------------------" << endl;
    
    return 0;
}


int FA_Line_Calculator(const char *file_name, const int line_start, const int line_end)
{
    string pattern = "^`.*$";
    regex RE(pattern);

    if( line_start >= line_end )
    {
        cout << "----------------------------------------" << endl;
        cout << ">>>         Line Number Error        <<<" << endl;
        cout << "----------------------------------------" << endl;
        return -2;
    }

    string strLine[MAX_LINE];    
    int line_index = 1;
    int month_sum = 0;
    
    if( ReadFile(file_name, strLine, line_index) == -1 )
    {
        return -1;
    }

    for(int i = line_start; i <= line_end; i++)
    {
        if( regex_match(strLine[i], RE) )
        {
            month_sum += sm_StrMoneyFind_Line(strLine[i]);            
        }
    }
    
    return month_sum;
}


// tip 番茄@20170906 - 用mod_tag来区分需要修改的项目
int FA_Sum_Modify(const char *file_name, const int line_id, const int money, int mod_tag)
{
    string strLine[MAX_LINE];    
    int line_index = 1;
    
    if( ReadFile(file_name, strLine, line_index) == -1 )
    {
        return -1;
    }

    if( 1 == mod_tag )
    {
        sm_StrMoneyModify_Title(strLine[line_id], money);
    }
    else if( 2 == mod_tag )
    {
        sm_StrMoneyModify_Top(strLine[line_id], money);
    }
    else if( 3 == mod_tag )
    {
        sm_StrMoneyModify_Month(strLine[line_id], money);
    }
    else if( 4 == mod_tag )
    {
        sm_StrMoneyModify_Line(strLine[line_id], money);
    }
    
    if(WirteFile(file_name, strLine, line_index) == -1)
    {
        return -2;
    }
    
    //cout << "----------------------------------------" << endl;
    //cout << ">>>            SUM MODIFIED          <<<" << endl;
    //cout << "----------------------------------------" << endl;
    
    return 0;
}

int FA_Balance(const char *file_name, const int line_a, const int line_b, const int money_mod, const bool bFlag)
{
    string strLine[MAX_LINE];
    int line_index = 1;
    
    if( ReadFile(file_name, strLine, line_index) == -1 )
    {
        return -1;
    }

    for(int i = 1; i <= line_index; i++)
    {
        if( i == line_a )
        {
            if( bFlag == true )
            {
                int money_new = sm_StrMoneyFind_Top(strLine[i]) - money_mod;
                sm_StrMoneyModify_Top(strLine[i], money_new);
            }
            else
            {
                int money_new = sm_StrMoneyFind_Top(strLine[i]) + money_mod;
                sm_StrMoneyModify_Top(strLine[i], money_new);
            }
        }
        if( i == line_b )
        {
            if( bFlag == true )
            {
                int money_new = sm_StrMoneyFind_Top(strLine[i]) + money_mod;
                sm_StrMoneyModify_Top(strLine[i], money_new);
            }
            else
            {
                int money_new = sm_StrMoneyFind_Top(strLine[i]) - money_mod;
                sm_StrMoneyModify_Top(strLine[i], money_new);
            }
        }
    }
        
    if(WirteFile(file_name, strLine, line_index) == -1)
    {
        return -2;
    }
    
    cout << "----------------------------------------" << endl;
    cout << ">>>             BALANCED             <<<" << endl;
    cout << "----------------------------------------" << endl;
    
    return 0;
}


int FA_BackUp(const char *file_name, const char *bak_file_path)
{
    string strLine[MAX_LINE];    
    int line_index = 1;
    
    if( ReadFile(file_name, strLine, line_index) == -1 )
    {
        return -1;
    }
    
    string str;
    str += bak_file_path;
    str += file_name;

    if(WirteFile(str.c_str(), strLine, line_index) == -1)
    {
        return -2;
    }
    
    cout << ">>> " << "BACK UP:  " << file_name << endl;
    
    return 0;
}


/*--------------------  CODE_END @ 番茄  --------------------*/


