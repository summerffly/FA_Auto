
/*--------------------  CODE_ORIGIN @ 番茄  --------------------*/

#include <vector>

#include "global.h"
#include "advanced_CMD.h"
#include "FBric_operator.h"
#include "FA_tool.h"
#include "FA_itfX.h"

using namespace std;

//----- 全局变量区 -----//
struct timeval tv_begin,tv_end;

char *version = new char[10];
char *ex_month = new char[3];
char *cr_month = new char[3];
char *nx_month = new char[3];


//----- Main入口-----//
int main(int argc, char **argv, char *env[])
{
    if( FA_Read_Conf(version, ex_month, cr_month, nx_month) == -1 )
    {
        return -1;
    }

    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;
    cout << "| |       FA_Automator System        | |" << endl;
    cout << "| |      >>>  番茄_summer  <<<       | |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;
    cout << "| |         Version: " << version << "_LTU" << "         | |" << endl;
    cout << "| |       Previous Month: " << ex_month << "         | |" << endl;
    cout << "| |        Current Month: " << cr_month << "         | |" << endl;
    cout << "| |          Next Month: " << nx_month << "          | |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;

    // advanced_CMD循环模式
    char advanced_CMD[MAX_COMMAND];
    int CMD_argc = 0;
    vector<string> CMD_argv;
    
    while(1)
    {
        cout << "CMD >>> ";
        cin.getline(advanced_CMD, MAX_COMMAND);

        // 判断是否输入空行
        if( CMD_Line_Parser(advanced_CMD, CMD_argc, CMD_argv) == -1 )
        {
            cout << "CMD is blank line !" << endl;
            cout << "----------------------------------------" << endl;
            
            continue;
        }
        
        // 判断是否输入撤销CMD
        if( CMD_argv.back().compare(CMD_CANCEL) == 0 )
        {
            cout << "CMD canceled !" << endl;
            cout << "----------------------------------------" << endl;
            
            continue;
        }

        /**************************************************/
        //   退出 FA_Auto系统
        //   CMD-> sd
        /**************************************************/
        if((CMD_argv.begin()->compare(CMD_SD) == 0)\
            && (CMD_argv.size() == 1))
        {
            cout << "----------------------------------------" << endl;
            cout << "|-----    FA_Automator SHUTDOWN   -----|" << endl;
            cout << "----------------------------------------" << endl;

            break;
        }

        /**************************************************/
        //   显示 .md文件
        //   CMD-> print ./NS.md
        /**************************************************/
        if((CMD_argv.begin()->compare(CMD_PRINT) == 0)\
            && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);

            cout << "----------------------------------------" << endl;
            FA_Print_File(CMD_argv.at(1).c_str());
            cout << "----------------------------------------" << endl;  
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   搜索 .md文件 单行
        //   CMD-> search ./NS.md temp
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_SEARCH) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);

            FA_Print_Line_Key(CMD_argv.at(1).c_str(), CMD_argv.at(2).c_str());

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   修改 当月 支出
        //   CMD-> life 100 生活
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_LIFE) == 0)\
                && (CMD_argv.size() == 3))    
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_Modify_Month(cr_month, nx_month, char2int(CMD_argv.at(1).c_str()), CMD_argv.at(2).c_str());

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   更新 当月 收支
        //   CMD-> update month
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_UPDATE) == 0)\
                && (CMD_argv.at(1).compare(CMD_MONTH) == 0)\
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);
            
            FAitfX_Update_Month(cr_month, nx_month);
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   检查 当月 收支
        //   CMD-> check month
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_MONTH) == 0)\
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_Check_Month(cr_month, nx_month);
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   更新 上月 收支
        //   CMD-> update month ex
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_UPDATE) == 0)\
                && (CMD_argv.at(1).compare(CMD_MONTH) == 0)\
                && (CMD_argv.at(2).compare(CMD_EX) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);
    
            FAitfX_Update_Month(ex_month, cr_month);
    
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   检查 上月 收支
        //   CMD-> check month ex
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_MONTH) == 0)\
                && (CMD_argv.at(2).compare(CMD_EX) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);
            
            FAitfX_Check_Month(ex_month, cr_month);
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   增加 Books.M 支出
        //   CMD-> book 100 《史记》
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_BOOK) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);
    
            FAitfX_Modify_SubMonth("./Books.M.md", "Books.M", cr_month, nx_month,\
                                   char2int(CMD_argv.at(1).c_str()), CMD_argv.at(2).c_str());
    
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;
             
            continue;
        }

        /**************************************************/
        //   增加 KEEP.M 支出
        //   CMD-> keep 100 云南白药
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_KEEP) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);
    
            FAitfX_Modify_SubMonth("./KEEP.M.md", "KEEP.M", cr_month, nx_month,\
                                   char2int(CMD_argv.at(1).c_str()), CMD_argv.at(2).c_str());
    
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;
             
            continue;
        }

        /**************************************************/
        //   增加 TB.M 支出
        //   CMD-> tb 100 sth
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_TB) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);
    
            FAitfX_Modify_SubMonth("./TB.M.md", "TB.M", cr_month, nx_month,\
                                   char2int(CMD_argv.at(1).c_str()), CMD_argv.at(2).c_str());
    
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;
             
            continue;
        }

        /**************************************************/
        //   增加 sa.M 支出
        //   CMD-> sa 100 红包
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_SA) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_Modify_SubMonth("./sa.M.md", "sa.M", cr_month, nx_month,\
                                   char2int(CMD_argv.at(1).c_str()), CMD_argv.at(2).c_str());

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;
         
            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   检查TVT支出  * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_SC_TVT) == 0 )        
        {
            gettimeofday(&tv_begin, NULL);   ////////////////////////////// TimePoint_START

            FA_Sum_Check_TVT();

            gettimeofday(&tv_end, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   更新TVT支出  * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_SU_TVT) == 0 )        
        {
            gettimeofday(&tv_begin, NULL);   ////////////////////////////// TimePoint_START

            FA_Sum_Update_TVT();

            gettimeofday(&tv_end, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   增加 DK 支出
        //   CMD-> dk 5000 iPhone
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_DK) == 0)\
                && (CMD_argv.size() == 3))
        {
            if(char0check(CMD_argv.at(1).c_str()) != 0)
                continue;

            gettimeofday(&tv_begin, NULL);

            FAitfX_Modify_Title("./DK.md", "# Digital Kingdom", "## DK",\
                                char2int(CMD_argv.at(1).c_str()), CMD_argv.at(2).c_str());

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   检查 DK 支出
        //   CMD-> check dk
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_DK) == 0)\
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);
            
            FAitfX_Check_Title("./DK.md", "# Digital Kingdom", "## DK");
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   增加 NS 支出
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_NS) == 0)\
                && (CMD_argv.size() == 3))
        {
            if(char0check(CMD_argv.at(1).c_str()) != 0)
                continue;

            gettimeofday(&tv_begin, NULL);

            FAitfX_Modify_Title("./NS.md", "# New Style", "## NS",\
                                char2int(CMD_argv.at(1).c_str()), CMD_argv.at(2).c_str());

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   检查 NS 支出
        //   CMD-> check ns
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_NS) == 0)\
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);
            
            FAitfX_Check_Title("./NS.md", "# New Style", "## NS");
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * *   计算lottery收支  * * * * * * */
        //   e.g.-> lottery -- 128 201711102
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_LOTTERY) == 0 )
        {
            if(CMD_argv.size() != 4)
            {
                cout << "CMD is incomplete !" << endl;
                cout << "----------------------------------------" << endl;

                continue;
            }

            gettimeofday(&tv_begin, NULL);   ////////////////////////////// TimePoint_START

            bool pnFlag = false;
            string money;
            unsigned int value = 0;
            string strInsetLine;

            money = CMD_argv.at(2);

            if( (CMD_argv.at(1).compare("++")) && (CMD_argv.at(1).compare("--")) )
                continue;

            if( char0check(money.c_str()) != 0 )
                continue;

            if( strlen(CMD_argv.at(3).c_str()) != 8 )
                continue;
            
            if( CMD_argv.at(1).compare("++") == 0 )
            {
                pnFlag = true;
                strInsetLine += "足彩收入_";
                strInsetLine += CMD_argv.at(3);
            }
            else
            {
                pnFlag = false;
                strInsetLine += "足彩支出_";
                strInsetLine += CMD_argv.at(3);
            }

            int line_this = FA_Search_Line("lottery.md", "# lottery");
            int line_next = FA_Search_Line("lottery.md", "## Total");
            int line_tag = FA_Search_Line("FA_TVT.md", "## lottery");
            
            FA_Line_Add("lottery.md", (line_next-1), pnFlag, char2int(money.c_str()), strInsetLine.c_str());
            int money_sum = FA_Line_Calculator("lottery.md", line_this, line_next);

            FA_Sum_Modify("lottery.md", (line_next+3), money_sum, 2);
            FA_Sum_Modify("FA_TVT.md", (line_tag+1), money_sum, 1);

            FA_Sum_Update_TVT();

            int line_bank = FA_Search_Line("FA_TVT.md", "广发银行");
            int line_alirest = FA_Search_Line("FA_TVT.md", "余额宝");

            if( CMD_argv.at(1).compare("++") == 0 )
            {
                FA_Balance("FA_TVT.md", line_bank, line_alirest, char2int(money.c_str()), false);
            }
            else
            {
                FA_Balance("FA_TVT.md", line_bank, line_alirest, char2int(money.c_str()), true);
            }

            gettimeofday(&tv_end, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   检查 lottery 收支
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_LOTTERY) == 0)\
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);
            
            FAitfX_Check_Title("./lottery.md", "# lottery", "## lottery");
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   balance操作  * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_BALANCE) == 0 )
        {
            char money[8];

            cout << "Money >>> ";
            cin >> money;

            if(char0check(money) != 0)
                continue;

            gettimeofday(&tv_begin, NULL);

            int line_bank = FA_Search_Line("FA_TVT.md", "广发银行");
            int line_alirest = FA_Search_Line("FA_TVT.md", "余额宝");

            FA_Balance("FA_TVT.md", line_bank, line_alirest, char2int(money), true);

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            cin.ignore();
            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * *    rebalance操作   * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_REBALANCE) == 0 )
        {
            char money[8];

            cout << "Money >>> ";
            cin >> money;

            if(char0check(money) != 0)
                continue;

            
            gettimeofday(&tv_begin, NULL);   ////////////////////////////// TimePoint_START
            
            int line_bank = FA_Search_Line("FA_TVT.md", "广发银行");
            int line_alirest = FA_Search_Line("FA_TVT.md", "余额宝");

            FA_Balance("FA_TVT.md", line_bank, line_alirest, char2int(money), false);

            gettimeofday(&tv_end, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            cin.ignore();
            continue;
        }

        /**************************************************/
        //   BackUp 全备份
        /**************************************************/
        else if( CMD_argv.begin()->compare(CMD_BACKUP) == 0 )
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_BackUp("./FA_TVT.bak/");

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   TEST
        /**************************************************/
        else if( CMD_argv.begin()->compare(CMD_TEST) == 0 )
        {
            FAitfX_Modify_SubMonth("./sa.M.md", "sa.M", cr_month, nx_month,\
                                char2int(CMD_argv.at(1).c_str()), CMD_argv.at(2).c_str());

            continue;
        }

        /**************************************************/
        //   CMD输入错误
        /**************************************************/
        else
        {
            cout << "----------------------------------------" << endl;
            cout << ">>>           Error Command          <<<" << endl;
            cout << "----------------------------------------" << endl;

            continue;
        }
    }

    return 0;
}


/*--------------------  CODE_END @ 番茄  --------------------*/

