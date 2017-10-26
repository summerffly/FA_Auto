
/*--------------------  CODE_ORIGIN @ 番茄  --------------------*/

#pragma once

#include "global.h"
#include "FBric_operator.h"
#include "FA_tool.h"

using namespace std;

/**************************************************/
//   读取 conf文件
/**************************************************/
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
    
    // tip 番茄@20170817 - 直接对内存进行操作，需要注意风险，特别是更改格式以后
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

/**************************************************/
//   更新 life.M 月度收支
/**************************************************/
int FAitfX_Update_Month(const char *month_on, const char *month_under)
{
    string str_month_on("## life.M");
    str_month_on += month_on;
    string str_month_under("## life.M");
    str_month_under += month_under;

    int line_on = FA_Search_Line("./life.M.md", str_month_on.c_str());
    int line_under = FA_Search_Line("./life.M.md", str_month_under.c_str());
    int line_tvt = FA_Search_Line("./FA_TVT.md", str_month_on.c_str());
    
    int money_in_up = sm_StrMoneyFind_Month(FA_Print_Line_Index("./life.M.md", line_on + 1));
    int money_out_up = FA_Line_Calculator("./life.M.md", line_on, line_under);
    int money_rest_up = money_in_up + money_out_up;

    cout << "----------------------------------------" << endl;
    cout << "line_" << line_on + 1 << " // " << FA_Print_Line_Index("./life.M.md", line_on + 1) << endl;
    cout << "line_" << line_on + 2 << " // " << FA_Print_Line_Index("./life.M.md", line_on + 2) << endl;
    cout << "line_" << line_on + 3 << " // " << FA_Print_Line_Index("./life.M.md", line_on + 3) << endl;
    cout << "### Check_Sum ### " << money_in_up << endl;
    cout << "### Check_Sum ### " << money_out_up << endl;
    cout << "### Check_Sum ### " << money_rest_up << endl;

    FA_Sum_Modify("./life.M.md", line_on + 2, money_out_up, 3);
    FA_Sum_Modify("./life.M.md", line_on + 3, money_rest_up, 3);

    cout << "line_" << line_on + 1 << " // " << FA_Print_Line_Index("./life.M.md", line_on + 1) << endl;
    cout << "line_" << line_on + 2 << " // " << FA_Print_Line_Index("./life.M.md", line_on + 2) << endl;
    cout << "line_" << line_on + 3 << " // " << FA_Print_Line_Index("./life.M.md", line_on + 3) << endl;

    FA_Sync_Month(line_on, line_tvt);

    cout << "----------------------------------------" << endl;

    return 0;
}

/**************************************************/
//   检查 life.M 月度收支
/**************************************************/
int FAitfX_Check_Month(const char *month_on, const char *month_under)
{
    string str_month_on("## life.M");
    str_month_on += month_on;
    string str_month_under("## life.M");
    str_month_under += month_under;

    int line_on = FA_Search_Line("./life.M.md", str_month_on.c_str());
    int line_under = FA_Search_Line("./life.M.md", str_month_under.c_str());
    
    int money_in_chk = sm_StrMoneyFind_Month(FA_Print_Line_Index("./life.M.md", line_on + 1));
    int money_out_chk = FA_Line_Calculator("./life.M.md", line_on, line_under);
    int money_rest_chk = money_in_chk + money_out_chk;

    cout << "----------------------------------------" << endl;
    cout << "line_" << line_on + 1 << " // " << FA_Print_Line_Index("./life.M.md", line_on + 1) << endl;
    cout << "line_" << line_on + 2 << " // " << FA_Print_Line_Index("./life.M.md", line_on + 2) << endl;
    cout << "line_" << line_on + 3 << " // " << FA_Print_Line_Index("./life.M.md", line_on + 3) << endl;
    cout << "### Check_Sum ### " << money_in_chk << endl;
    cout << "### Check_Sum ### " << money_out_chk << endl;
    cout << "### Check_Sum ### " << money_rest_chk << endl;
    cout << "----------------------------------------" << endl;

    return 0;
}

/**************************************************/
//   更新 FA_TVT
/**************************************************/
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
            money_sum += sm_StrMoneyFind_Line(strLine[i]);
            continue;
        }
        else if( regex_match(strLine[i], RE_bank) )
        {
            cout << "line_" << i << " // " << strLine[i].c_str() << endl;
            money_sum -= sm_StrMoneyFind_Top(strLine[i]);
            continue;
        }
        else if( regex_match(strLine[i], RE_alirest) )
        {
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

/**************************************************/
//   检查 FA_TVT
/**************************************************/
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
            money_sum += sm_StrMoneyFind_Line(strLine[i]);
            continue;
        }
        else if( regex_match(strLine[i], RE_bank) )
        {
            cout << "line_" << i << " // " << strLine[i].c_str() << endl;
            money_sum -= sm_StrMoneyFind_Top(strLine[i]);
            continue;
        }
        else if( regex_match(strLine[i], RE_alirest) )
        {
            cout << "line_" << i << " // " << strLine[i].c_str() << endl;
            cout << "Sum_Check_SZ: " << money_sum << endl;
            cout << "----------------------------------------" << endl;
            continue;
        }
    }
    
    return 0;
}

/**************************************************/
//   检查 DK
/**************************************************/
int FAitfX_Check_DK()
{
    int line_begin = FA_Search_Line("./DK.md", "# Digital Kingdom");
    int line_end = FA_Search_Line("./DK.md", "## Total");

    int money_sum = FA_Line_Calculator("./DK.md", line_begin, line_end);

    cout << "----------------------------------------" << endl;
    cout << "line_" << line_end+2 << " // " << FA_Print_Line_Index("./DK.md", line_end+2) << endl;
    cout << "### Check_Sum ### " << money_sum << endl;
    cout << "----------------------------------------" << endl;

    return 0;
}

/**************************************************/
//   检查 NS
/**************************************************/
int FAitfX_Check_NS()
{
    int line_begin = FA_Search_Line("./NS.md", "# New Style");
    int line_end = FA_Search_Line("./NS.md", "## Total");

    int money_sum = FA_Line_Calculator("./NS.md", line_begin, line_end);

    cout << "----------------------------------------" << endl;
    cout << "line_" << line_end+2 << " // " << FA_Print_Line_Index("./NS.md", line_end+2) << endl;
    cout << "### Check_Sum ### " << money_sum << endl;
    cout << "----------------------------------------" << endl;

    return 0;
}

/**************************************************/
//   检查 lottery
/**************************************************/
int FAitfX_Check_lottery()
{
    int line_begin = FA_Search_Line("./lottery.md", "# lottery");
    int line_end = FA_Search_Line("./lottery.md", "## Total");

    int money_sum = FA_Line_Calculator("./lottery.md", line_begin, line_end);

    cout << "----------------------------------------" << endl;
    cout << "line_" << line_end+2 << " // " << FA_Print_Line_Index("./lottery.md", line_end+2) << endl;
    cout << "### Check_Sum ### " << money_sum << endl;
    cout << "----------------------------------------" << endl;

    return 0;
}

/**************************************************/
//   .md文件 全备份
/**************************************************/
int FAitfX_BackUp(const char *bak_file_path)
{
    cout << "----------------------------------------" << endl;
    FA_BackUp("./FA_TVT.md", bak_file_path);
    FA_BackUp("./life.M.md", bak_file_path);
    FA_BackUp("./Books.M.md", bak_file_path);
    FA_BackUp("./KEEP.M.md", bak_file_path);
    FA_BackUp("./TB.M.md", bak_file_path);
    FA_BackUp("./sa.M.md", bak_file_path);
    FA_BackUp("./DK.md", bak_file_path);
    FA_BackUp("./NS.md", bak_file_path);
    FA_BackUp("./lottery.md", bak_file_path);
    cout << "----------------------------------------" << endl;

    return 0;
}


/*--------------------  CODE_END @ 番茄  --------------------*/


