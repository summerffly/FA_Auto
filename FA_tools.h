
/*--------------------  CODE_ORIGIN @ 番茄  --------------------*/

#include <fstream>
#include <iomanip>

#include "global.h"
#include "str_operator.h"

using namespace std;


/*--------------------  函数声明 @ 番茄  --------------------*/

int FA_Search_Line(const char *file_name, const char *line_key);
int FA_Line_Calculator(const char *file_name, const int line_start, const int line_end);


/*--------------------  TOOLS @ 番茄  --------------------*/

// tip 番茄@20170817 - 直接对内存进行操作，需要注意风险，特别是更改格式以后
int FA_Read_Conf(char *version, char *ex_month, char *cr_month, char *nx_month)
{
    char buffer[64];
    string strLine[16];
    int line_index = 1;
    
    ifstream ifile("./FA.conf");

    if(!ifile.is_open())
    {
        cout << "----------------------------------------" << endl;
        cout << ">>>          Read Conf Error         <<<" << endl;
        cout << "----------------------------------------" << endl;
        return -1;
    }
    
    while(!ifile.eof())
    {
        ifile.getline(buffer, MAX_LINE_CHAR);
        strLine[line_index] = buffer;
        
        if( regex_match(strLine[line_index], RE_cv) )
        {
            memmove(version, buffer+18, 4);
            continue;
        }
        else if( regex_match(strLine[line_index], RE_pm) )
        {
            memmove(ex_month, buffer+17, 3);            
            continue;
        }
        else if( regex_match(strLine[line_index], RE_cm) )
        {
            memmove(cr_month, buffer+16, 3);            
            continue;
        }
        else if( regex_match(strLine[line_index], RE_nm) )
        {
            memmove(nx_month, buffer+13, 3);              
            continue;
        }
        
        line_index++;
    }
    
    ifile.close();
        
    return 0;
}


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


int FA_Print_Line(const char *file_name, const char *line_key)
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


/*----------------------------------------------------------------*/
/*--------------------  处理函数 @ 番茄  --------------------*/
/*----------------------------------------------------------------*/

int FA_Sum_Check_Month(const int line_tag)
{
    string strLine[MAX_LINE];    
    int line_index = 1;

    int money_in = 0;
    int money_out = 0;
    int money_rest = 0;    
    
    if( ReadFile("life.M.md", strLine, line_index) == -1 )
    {
        return -1;
    }

    for(int i = 1; i <= line_index; i++)
    {
        if(i == (line_tag+1))
        {
            cout << "----------------------------------------" << endl;              
            cout << "line_" << i << " // " << strLine[i].c_str() << endl;            
            money_in = sm_StrMoneyFind_Month(strLine[i]);
            continue;
        }
        if(i == (line_tag+2))
        {
            cout << "line_" << i << " // " << strLine[i].c_str() << endl;            
            money_out = sm_StrMoneyFind_Month(strLine[i]);
            continue;
        }
        if(i == (line_tag+3))
        {
            cout << "line_" << i << " // " << strLine[i].c_str() << endl;            
            money_in = sm_StrMoneyFind_Month(strLine[i]);
            cout << "----------------------------------------" << endl;              
            continue;
        }
    }
    
    return 0;
}


int FA_Sum_Update_Month(const int line_tag_life, const int line_tag_sz, const int money_sum)
{
    string strLine_life[MAX_LINE];    
    string strLine_sz[MAX_LINE];    
    int line_index_life = 1;
    int line_index_sz = 1;
    
    int money_in = 0;
    int money_out = 0;
    int money_rest = 0;    
    
    if( ReadFile("life.M.md", strLine_life, line_index_life) == -1 )
    {
        return -1;
    }

    if( ReadFile("FA_TVT.md", strLine_sz, line_index_sz) == -1 )
    {
        return -1;
    }

    for(int i = 1; i <= line_index_life; i++)
    {
        if(i == (line_tag_life+1))
        {
            cout << "----------------------------------------" << endl;              
            cout << "line_" << i << " // " << strLine_life[i].c_str() << endl;            
            money_in = sm_StrMoneyFind_Month(strLine_life[i]);
            strLine_sz[line_tag_sz+1] = strLine_life[i];
            continue;
        }
        if(i == (line_tag_life+2))
        {
            cout << "line_" << i << " // " << strLine_life[i].c_str() << endl;            
            sm_StrMoneyModify_Month(strLine_life[i], money_sum);
            strLine_sz[line_tag_sz+2] = strLine_life[i];            
            continue;
        }
        if(i == (line_tag_life+3))
        {
            cout << "line_" << i << " // " << strLine_life[i].c_str() << endl;            
            sm_StrMoneyModify_Month(strLine_life[i], (money_in+money_sum));  
            strLine_sz[line_tag_sz+3] = strLine_life[i];            
            cout << "----------------------------------------" << endl;  
            cout << ">>>            SUM UPDATED           <<<" << endl;
            cout << "----------------------------------------" << endl;  
            cout << "line_" << (i-2) << " // " << strLine_life[i-2].c_str() << endl;            
            cout << "line_" << (i-1) << " // " << strLine_life[i-1].c_str() << endl;            
            cout << "line_" << i << " // " << strLine_life[i].c_str() << endl;            
            cout << "----------------------------------------" << endl;              
            continue;
        }
    }

    WirteFile("life.M.md", strLine_life, line_index_life);       
    WirteFile("FA_TVT.md", strLine_sz, line_index_sz);       
    
    return 0;
}


int FA_Sum_Update_ExMonth(const int line_tag_life, const int line_tag_sz)
{
    string strLine_life[MAX_LINE];    
    string strLine_sz[MAX_LINE];    
    int line_index_life = 1;
    int line_index_sz = 1;
    
    int money_in = 0;
    int money_out = 0;
    int money_rest = 0;    
    
    if( ReadFile("life.M.md", strLine_life, line_index_life) == -1 )
    {
        return -1;
    }

    if( ReadFile("FA_TVT.md", strLine_sz, line_index_sz) == -1 )
    {
        return -1;
    }

    for(int i = 1; i <= line_index_life; i++)
    {
        if(i == (line_tag_life+1))
        {
            cout << "----------------------------------------" << endl;              
            cout << "line_" << i << " // " << strLine_life[i].c_str() << endl;            
            money_in = sm_StrMoneyFind_Month(strLine_life[i]);
            strLine_sz[line_tag_sz+1] = strLine_life[i];
            continue;
        }
        if(i == (line_tag_life+2))
        {
            cout << "line_" << i << " // " << strLine_life[i].c_str() << endl;            
            money_out = sm_StrMoneyFind_Month(strLine_life[i]);
            strLine_sz[line_tag_sz+2] = strLine_life[i];
            continue;
        }
        if(i == (line_tag_life+3))
        {
            cout << "line_" << i << " // " << strLine_life[i].c_str() << endl;            
            sm_StrMoneyModify_Month(strLine_life[i], (money_in + money_out));  
            strLine_sz[line_tag_sz+3] = strLine_life[i];            
            cout << "----------------------------------------" << endl;  
            cout << ">>>            SUM UPDATED           <<<" << endl;
            cout << "----------------------------------------" << endl;  
            cout << "line_" << (i-2) << " // " << strLine_life[i-2].c_str() << endl;            
            cout << "line_" << (i-1) << " // " << strLine_life[i-1].c_str() << endl;            
            cout << "line_" << i << " // " << strLine_life[i].c_str() << endl;            
            cout << "----------------------------------------" << endl;              
            continue;
        }
    }

    WirteFile("life.M.md", strLine_life, line_index_life);       
    WirteFile("FA_TVT.md", strLine_sz, line_index_sz);       
    
    return 0;
}


int FA_Sum_Check_TVT()
{
    string strLine[MAX_LINE];    
    int line_index = 1;
    int money_sum = 0;
    
    if( ReadFile("FA_TVT.md", strLine, line_index) == -1 )
    {
        return -1;
    }

    for(int i = 1; i <= line_index; i++)
    {
        if( regex_match(strLine[i], RE_ofi) )
        {
            money_sum += sm_StrMoneyFind_Top(strLine[i]);
            continue;
        }
        else if( regex_match(strLine[i], RE_lottery) )
        {
            money_sum += sm_StrMoneyFind_Title(strLine[i+1]);
            continue;
        }
        else if( regex_match(strLine[i], RE_dk) )
        {
            money_sum += sm_StrMoneyFind_Title(strLine[i+1]);
            continue;
        }
        else if( regex_match(strLine[i], RE_ns) )
        {
            money_sum += sm_StrMoneyFind_Title(strLine[i+1]);
            continue;
        }
        else if( regex_match(strLine[i], RE_month) )
        {
            money_sum += sm_StrMoneyFind_Month(strLine[i+3]);
            continue;
        }
        else if( regex_match(strLine[i], RE_cfi) )
        {
            cout << "----------------------------------------" << endl;  
            cout << "line_" << i << " // " << strLine[i].c_str() << endl;
            cout << "Sum_Check_SZ: " << money_sum << endl;
            cout << "----------------------------------------" << endl;
            continue;
        }
        else if( regex_match(strLine[i], RE_de_one) )
        {
            money_sum += sm_StrMoneyFind_Line(strLine[i]);
            continue;
        }
        else if( regex_match(strLine[i], RE_de_mobike) )
        {
            money_sum += sm_StrMoneyFind_Line(strLine[i]);
            continue;
        }
        else if( regex_match(strLine[i], RE_de_ofo) )
        {
            money_sum += sm_StrMoneyFind_Line(strLine[i]);
            continue;
        }
        else if( regex_match(strLine[i], RE_loan) )
        {
            money_sum += sm_StrMoneyFind_Top(strLine[i]);
            continue;
        }
        else if( regex_match(strLine[i], RE_alirest) )
        {
            cout << "----------------------------------------" << endl;  
            cout << "line_" << i << " // " << strLine[i].c_str() << endl;
            cout << "Sum_Check_SZ: " << money_sum << endl;
            cout << "----------------------------------------" << endl;
            continue;
        }
    }
    
    return 0;
}


int FA_Sum_Update_TVT()
{
    string strLine[MAX_LINE];    
    int line_index = 1;
    int money_sum = 0;
    
    if( ReadFile("FA_TVT.md", strLine, line_index) == -1 )
    {
        return -1;
    }

    for(int i = 1; i <= line_index; i++)
    {
        if( regex_match(strLine[i], RE_ofi) )
        {
            money_sum += sm_StrMoneyFind_Top(strLine[i]);
            continue;
        }
        else if( regex_match(strLine[i], RE_lottery) )
        {
            money_sum += sm_StrMoneyFind_Title(strLine[i+1]);
            continue;
        }
        else if( regex_match(strLine[i], RE_dk) )
        {
            money_sum += sm_StrMoneyFind_Title(strLine[i+1]);
            continue;
        }
        else if( regex_match(strLine[i], RE_ns) )
        {
            money_sum += sm_StrMoneyFind_Title(strLine[i+1]);
            continue;
        }
        else if( regex_match(strLine[i], RE_month) )
        {
            money_sum += sm_StrMoneyFind_Month(strLine[i+3]);
            continue;
        }
        else if( regex_match(strLine[i], RE_cfi) )
        {
            cout << "----------------------------------------" << endl;  
            cout << "line_" << i << " // " << strLine[i].c_str() << endl;
            cout << "Sum_Check_SZ: " << money_sum << endl;
            cout << "----------------------------------------" << endl;
            sm_StrMoneyModify_Top(strLine[i], money_sum);            
            continue;
        }
        else if( regex_match(strLine[i], RE_de_one) )
        {
            money_sum += sm_StrMoneyFind_Line(strLine[i]);
            continue;
        }
        else if( regex_match(strLine[i], RE_de_mobike) )
        {
            money_sum += sm_StrMoneyFind_Line(strLine[i]);
            continue;
        }
        else if( regex_match(strLine[i], RE_de_ofo) )
        {
            money_sum += sm_StrMoneyFind_Line(strLine[i]);
            continue;
        }
        else if( regex_match(strLine[i], RE_loan) )
        {
            money_sum += sm_StrMoneyFind_Top(strLine[i]);
            continue;
        }
        else if( regex_match(strLine[i], RE_alirest) )
        {
            cout << "----------------------------------------" << endl;  
            cout << "line_" << i << " // " << strLine[i].c_str() << endl;
            cout << "Sum_Check_SZ: " << money_sum << endl;
            cout << "----------------------------------------" << endl;
            sm_StrMoneyModify_Top(strLine[i], money_sum);                        
            continue;
        }
    }

    WirteFile("FA_TVT.md", strLine, line_index);   
    
    cout << "----------------------------------------" << endl;
    cout << ">>>           SZ-SUM UPDATED         <<<" << endl;
    cout << "----------------------------------------" << endl;
    
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
    
    cout << "----------------------------------------" << endl;
    cout << ">>>           LINE MODIFIED          <<<" << endl;
    cout << "----------------------------------------" << endl;
    
    return 0;
}


// tip 番茄@20170818 - money默认为消费，默认为减法操作
int FA_Line_Add(const char *file_name, const int line_id, const int money, const char *line_char)
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
            line_index++;            
            for(int j = line_index; j > i; j--)
            {
                strLine[j] = strLine[j-1];
            }
            strLine[i] = sm_StrGenerator_Line(money, line_char);
        }
    }
        
    if(WirteFile(file_name, strLine, line_index) == -1)
    {
        return -2;
    }
    
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

    for(int i = 1; i <= line_index; i++)
    {
        if( i == line_id )
        {
            if( 1 == mod_tag )
            {
                sm_StrMoneyModify_Title(strLine[i], money);
            }
            else if( 2 == mod_tag )
            {
                sm_StrMoneyModify_Top(strLine[i], money);
            }
        }
    }
    
    if(WirteFile(file_name, strLine, line_index) == -1)
    {
        return -2;
    }
    
    cout << "----------------------------------------" << endl;
    cout << ">>>            SUM MODIFIED          <<<" << endl;
    cout << "----------------------------------------" << endl;
    
    return 0;
}


/*--------------------  CODE_END @ 番茄  --------------------*/


