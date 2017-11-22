
/*--------------------  CODE_ORIGIN @ 番茄  --------------------*/

#pragma once

#include "global.h"
#include "FBric_operator.h"
#include "FA_tool.h"
#include <map>

using namespace std;


/**************************************************/
//   检查 .md文件 收支
/**************************************************/
int FAitfX_CheckFile(const char *file_name, const char *file_title_begin, const char *file_title_end)
{
    int line_tag_begin = FA_Search_Line(file_name, file_title_begin);
    int line_tag_end = FA_Search_Line(file_name, file_title_end);

    int value_sum = FA_Line_Calculator(file_name, line_tag_begin, line_tag_end);

    cout << "----------------------------------------" << endl;
    cout << "### Check_Sum ### " << value_sum << endl;
    cout << "----------------------------------------" << endl;

    return 0;
}


/**************************************************/
//   更新 FA_TVT
/**************************************************/
void FAitfX_Update_TVT()
{
    FA_Sum_Update_TVT();
}


/**************************************************/
//   检查 FA_TVT
/**************************************************/
void FAitfX_Check_TVT()
{
    FA_Sum_Check_TVT();
}


/**************************************************/
//   修改 life.M 月度支出
/**************************************************/
int FAitfX_Modify_Month(const char *month_on, const unsigned int value, const char *line_key)
{
    string str_month_on("## life.M");
    str_month_on += month_on;
    string str_month_under("## life.M");
    str_month_under += GenNextMonth(month_on);

    int line_on = FA_Search_Line("./life.M.md", str_month_on.c_str());
    int line_under = FA_Search_Line("./life.M.md", str_month_under.c_str());

    int line_tag = FA_Print_Line_Area("./life.M.md", line_key, line_on, line_under);
    if(line_tag < 0)
    {
        return -1;
    }

    FA_Line_Modify("./life.M.md", line_tag, value);

    cout << "line_" << line_tag << " // " << FA_Print_Line_Index("./life.M.md", line_tag) << endl;
    cout << "----------------------------------------" << endl;

    return 0;
}


/**************************************************/
//   更新 life.M 月度收支
/**************************************************/
int FAitfX_Update_Month(const char *month_on)
{
    string str_month_on("## life.M");
    str_month_on += month_on;
    string str_month_under("## life.M");
    str_month_under += GenNextMonth(month_on);

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
int FAitfX_Check_Month(const char *month_on)
{
    string str_month_on("## life.M");
    str_month_on += month_on;
    string str_month_under("## life.M");
    str_month_under += GenNextMonth(month_on);

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
//   对比分析 月度支出
/**************************************************/
// tips 20171115 - 目前最大只支持12个月
int FAitfX_Analysis_Month(const char *sub_key, const char *month_origin, const char *month_on)
{
    char *temp_month = new char[3];
    memcpy(temp_month, month_origin, 3);

    string str_temp_month_on;
    string str_temp_month_under;
    int line_temp_begin = 0;
    int line_temp_end = 0;
    int line_temp_tag = 0;
    unsigned int line_temp_value = 0;
    string str_line_temp;

    map<int, unsigned int> submap;
    
    while(1)
    {
        str_temp_month_on.clear();
        str_temp_month_under.clear();
        str_temp_month_on += "## life.M";
        str_temp_month_on += temp_month;
        str_temp_month_under += "## life.M";
        str_temp_month_under += GenNextMonth(temp_month);

        int line_temp_begin = FA_Search_Line("./life.M.md", str_temp_month_on.c_str());
        int line_temp_end = FA_Search_Line("./life.M.md", str_temp_month_under.c_str());
        int line_temp_tag = FA_Search_Line_Area_Pure("./life.M.md", sub_key, line_temp_begin, line_temp_end);

        if(line_temp_tag > 0)
        {
            str_line_temp.clear();
            str_line_temp += FA_Print_Line_Index("./life.M.md", line_temp_tag);

            line_temp_value = 0;
            if(str_line_temp.at(0) == '>')
            {
                if( sm_StrMoneyFind_Month(str_line_temp) < 0)
                {
                    line_temp_value = (-1) * sm_StrMoneyFind_Month(str_line_temp);
                }
                else
                {
                    line_temp_value = sm_StrMoneyFind_Month(str_line_temp);
                }
            }
            else if(str_line_temp.at(0) == '`')
            {
                if( sm_StrMoneyFind_Line(str_line_temp) < 0 )
                {
                    line_temp_value = (-1) * sm_StrMoneyFind_Line(str_line_temp);
                }
                else
                {
                    line_temp_value = sm_StrMoneyFind_Line(str_line_temp);
                }
            }

            submap.insert(pair<int, unsigned int>(atoi(temp_month), line_temp_value));
        }

        memcpy(temp_month, GenNextMonth(temp_month).c_str(), 3);
        if(temp_month == GenNextMonth(month_on))
        {
            break;
        }
    }

    if(submap.size() == 0)
    {
        cout << ">>> KeyWord Not Found!" << endl;
        return -1;
    }

    unsigned int max_value = 0;
    map<int, unsigned int>::iterator mapIter = submap.begin();
    while(mapIter != submap.end())
    {
        if(mapIter->second > max_value)
        {
            max_value = mapIter->second;
        }
        mapIter++;
    }
    double scale_rate = (double)50 / max_value;

    mapIter = submap.begin();
    while(mapIter != submap.end())
    {
        if(mapIter->first < 10)
        {
            cout << "0";
        }
        cout << mapIter->first << "月/" << sub_key << ": ";

        int scale_i = 0;
        int scale_max = scale_rate * mapIter->second;
        while(scale_i <= scale_max)
        {
            cout << "|";
            scale_i++;
        }
        cout << " " << mapIter->second;

        if(mapIter == submap.begin())
        {
            cout << " (-%)" << endl;
        }
        else
        {
            double growth_rate = 0;
            mapIter--;
            double pm_value = mapIter->second;
            mapIter++;
            double cm_value = mapIter->second;
            growth_rate = (cm_value - pm_value)/pm_value;
            
            if( growth_rate > 0)
            {
                cout << " (+" << (int)(growth_rate*100) << "%)" << endl;
            }
            else if( growth_rate == 0)
            {
                cout << " (==)" << endl;
            }
            else
            {
                cout << " (" << (int)(growth_rate*100) << "%)" << endl;
            }
        }

        mapIter++;
    }

    delete []temp_month;

    return 0;
}


/**************************************************/
//   增加 life_子项.md 支出
/**************************************************/
int FAitfX_Modify_SubMonth(const char *file_name, const char *title_key, const char *month_on,\
                           const unsigned int value, const char *content)
{
    string str_month_on(title_key);
    str_month_on += month_on;
    string str_month_under(title_key);
    str_month_under += GenNextMonth(month_on);

    int line_on = FA_Search_Line(file_name, str_month_on.c_str());
    int line_under = FA_Search_Line(file_name, str_month_under.c_str());
    int line_life = FA_Search_Line("./life.M.md", str_month_on.c_str());

    FA_Line_Add(file_name, (line_under-1), false, value, content);
    int value_sum = FA_Line_Calculator(file_name, line_on, line_under+1);
    FA_Sum_Modify(file_name, (line_on+1), value_sum, 1);

    FA_Sum_Modify("./life.M.md", line_life, value_sum, 4);

    return 0;
}


/**************************************************/
//   更新 life_子项.md 支出
/**************************************************/
int FAitfX_Update_SubMonth(const char *file_name, const char *title_key, const char *month_on)
{
    string str_month_on(title_key);
    str_month_on += month_on;
    string str_month_under(title_key);
    str_month_under += GenNextMonth(month_on);

    int line_on = FA_Search_Line(file_name, str_month_on.c_str());
    int line_under = FA_Search_Line(file_name, str_month_under.c_str());
    int line_life = FA_Search_Line("./life.M.md", str_month_on.c_str());

    int value_sum = FA_Line_Calculator(file_name, line_on, line_under);
    FA_Sum_Modify(file_name, (line_on+1), value_sum, 1);
    FA_Sum_Modify("./life.M.md", line_life, value_sum, 4);

    return 0;
}


/**************************************************/
//   检查 life_子项.md 支出
/**************************************************/
int FAitfX_Check_SubMonth(const char *file_name, const char *title_key, const char *month_on)
{
    string str_month_on(title_key);
    str_month_on += month_on;
    string str_month_under(title_key);
    str_month_under += GenNextMonth(month_on);

    int line_on = FA_Search_Line(file_name, str_month_on.c_str());
    int line_under = FA_Search_Line(file_name, str_month_under.c_str());

    int value_sum = FA_Line_Calculator(file_name, line_on, line_under);
    cout << "line_" << line_on + 1 << " // " << FA_Print_Line_Index(file_name, line_on + 1) << endl;
    cout << "### Check_Sum ### " << value_sum << endl;

    return 0;
}


/**************************************************/
//   增加 TVT_分项.md 支出
/**************************************************/
int FAitfX_Modify_Title(const char *file_name, const char *file_title, const char *tvt_title,\
                        const int value, const char *content)
{
    int line_begin = FA_Search_Line(file_name, file_title);
    int line_end = FA_Search_Line(file_name, "## Total");
    int line_tag = FA_Search_Line("./FA_TVT.md", tvt_title);

    FA_Line_Add(file_name, line_end-1, false, value, content);
    int value_sum = FA_Line_Calculator(file_name, line_begin, line_end+1);

    FA_Sum_Modify(file_name, (line_end+3), value_sum, 2);   // line_next需要+3，因为加了新的一行
    FA_Sum_Modify("./FA_TVT.md", (line_tag+1), value_sum, 1);

    cout << "----------------------------------------" << endl;
    cout << "line_" << line_end+3 << " // " << FA_Print_Line_Index(file_name, line_end+3) << endl;
    cout << "----------------------------------------" << endl;

    return 0;
}


/**************************************************/
//   更新 TVT_分项.md 支出
/**************************************************/
int FAitfX_Update_Title(const char *file_name, const char *file_title, const char *tvt_title)
{
    int line_begin = FA_Search_Line(file_name, file_title);
    int line_end = FA_Search_Line(file_name, "## Total");
    int line_tag = FA_Search_Line("./FA_TVT.md", tvt_title);

    int value_sum = FA_Line_Calculator(file_name, line_begin, line_end);

    cout << "----------------------------------------" << endl;
    cout << "line_" << line_end+2 << " // " << FA_Print_Line_Index(file_name, line_end+2) << endl;
    cout << "### Check_Sum ### " << value_sum << endl;

    FA_Sum_Modify(file_name, (line_end+2), value_sum, 2);
    FA_Sum_Modify("./FA_TVT.md", (line_tag+1), value_sum, 1);

    cout << "line_" << line_end+2 << " // " << FA_Print_Line_Index(file_name, line_end+2) << endl;

    cout << "----------------------------------------" << endl;

    return 0;
}


/**************************************************/
//   检查 TVT_分项.md 支出
/**************************************************/
int FAitfX_Check_Title(const char *file_name, const char *file_title, const char *tvt_title)
{
    int line_begin = FA_Search_Line(file_name, file_title);
    int line_end = FA_Search_Line(file_name, "## Total");

    int money_sum = FA_Line_Calculator(file_name, line_begin, line_end);

    cout << "----------------------------------------" << endl;
    cout << "line_" << line_end+2 << " // " << FA_Print_Line_Index(file_name, line_end+2) << endl;
    cout << "### Check_Sum ### " << money_sum << endl;
    cout << "----------------------------------------" << endl;

    return 0;
}


/**************************************************/
//   增加 & 更新 lottery 收支
/**************************************************/
int FAitfX_lottery(const string lo_flag, const unsigned int value, const char *lo_date)
{
    bool pnFlag = false;
    string strInsetLine;

    if( (lo_flag.compare("++")) && (lo_flag.compare("--")) )
        return -1;

    if( strlen(lo_date) != 8 )
        return -1;
    
    if( lo_flag.compare("++") == 0 )
    {
        pnFlag = true;
        strInsetLine += "足彩收入_";
        strInsetLine += lo_date;
    }
    else
    {
        pnFlag = false;
        strInsetLine += "足彩支出_";
        strInsetLine += lo_date;
    }

    int line_on = FA_Search_Line("./lottery.md", "# lottery");
    int line_under = FA_Search_Line("./lottery.md", "## Total");
    int lottery_tag = FA_Search_Line("./FA_TVT.md", "## lottery");
    
    FA_Line_Add("./lottery.md", (line_under-1), pnFlag, value, strInsetLine.c_str());
    int value_sum = FA_Line_Calculator("./lottery.md", line_on, line_under+1);

    FA_Sum_Modify("./lottery.md", (line_under+3), value_sum, 2);
    FA_Sum_Modify("./FA_TVT.md", (lottery_tag+1), value_sum, 1);

    FA_Sum_Update_TVT();

    int line_bank = FA_Search_Line("./FA_TVT.md", "广发银行");
    int line_alirest = FA_Search_Line("./FA_TVT.md", "余额宝");

    if( pnFlag )
    {
        FA_Balance("./FA_TVT.md", line_bank, line_alirest, value, false);
    }
    else
    {
        FA_Balance("./FA_TVT.md", line_bank, line_alirest, value, true);
    }

    return 0;
}


/**************************************************/
//   balance 操作
/**************************************************/
int FAitfX_Balance(const unsigned int mod_value, const string bFlag)
{
    bool pnFlag = false;

    if( bFlag.compare("++") == 0 )
    {
        pnFlag = false;
    }
    else
    {
        pnFlag = true;
    }
    
    int line_bank = FA_Search_Line("./FA_TVT.md", "广发银行");
    int line_alirest = FA_Search_Line("./FA_TVT.md", "余额宝");

    FA_Balance("./FA_TVT.md", line_bank, line_alirest, mod_value, pnFlag);

    return 0;
}


/**************************************************/
//   全备份 .md文件
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
    FA_BackUp("./travel.md", bak_file_path);
    FA_BackUp("./lottery.md", bak_file_path);
    cout << "----------------------------------------" << endl;

    return 0;
}


/*--------------------  CODE_END @ 番茄  --------------------*/


