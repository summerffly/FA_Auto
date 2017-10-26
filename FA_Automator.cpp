
/*--------------------  CODE_ORIGIN @ 番茄  --------------------*/

#include <vector>

#include "global.h"
#include "advanced_CMD.h"
#include "FBric_operator.h"
#include "FA_tool.h"
#include "FA_itfX.h"

using namespace std;

//----- 全局变量区 -----//
struct timeval tst,ted;

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

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *    关闭系统    * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        if( CMD_argv.begin()->compare(CMD_SD) == 0 )
        {
            cout << "----------------------------------------" << endl;
            cout << "|-----    FA_Automator SHUTDOWN   -----|" << endl;
            cout << "----------------------------------------" << endl;

            break;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   显示md文件   * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        if( CMD_argv.begin()->compare(CMD_PRINT) == 0 )
        {
            if(CMD_argv.size() != 2)
            {
                cout << "CMD is incomplete !" << endl;
                cout << "----------------------------------------" << endl;

                continue;
            }

            gettimeofday(&tst, NULL);   ////////////////////////////// TimePoint_START

            cout << "----------------------------------------" << endl;
            FA_Print_File(CMD_argv.at(CMD_argc-1).c_str());
            cout << "----------------------------------------" << endl;  
            
            gettimeofday(&ted, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *    搜索单行    * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_SEARCH) == 0 )
        {
            if(CMD_argv.size() != 3)
            {
                cout << "CMD is incomplete !" << endl;
                cout << "----------------------------------------" << endl;

                continue;
            }

            gettimeofday(&tst, NULL);   ////////////////////////////// TimePoint_START

            FA_Print_Line_Key(CMD_argv.at(1).c_str(), CMD_argv.at(2).c_str());

            gettimeofday(&ted, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   更新 当月收支
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_UPDATE) == 0)\
                && (CMD_argv.at(1).compare(CMD_MONTH) == 0)\
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tst, NULL);
            
            FAitfX_Update_Month(cr_month, nx_month);
            
            gettimeofday(&ted, NULL);
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   检查 当月收支
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_MONTH) == 0)\
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tst, NULL);

            FAitfX_Check_Month(cr_month, nx_month);
            
            gettimeofday(&ted, NULL);
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   更新 上月收支
        /**************************************************/
        else if( CMD_argv.begin()->compare(CMD_SU_EXMN) == 0 )
        {
            gettimeofday(&tst, NULL);
            
            FAitfX_Update_Month(ex_month, cr_month);
            
            gettimeofday(&ted, NULL);
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   检查TVT支出  * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_SC_TVT) == 0 )        
        {
            gettimeofday(&tst, NULL);   ////////////////////////////// TimePoint_START

            FA_Sum_Check_TVT();

            gettimeofday(&ted, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   更新TVT支出  * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_SU_TVT) == 0 )        
        {
            gettimeofday(&tst, NULL);   ////////////////////////////// TimePoint_START

            FA_Sum_Update_TVT();

            gettimeofday(&ted, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *  更改LIFE支出  * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_LIFE) == 0 )        
        {
            string cr_month_str("## life.M");
            cr_month_str += cr_month;
            string nx_month_str("## life.M");
            nx_month_str += nx_month;

            int line_this = FA_Search_Line("life.M.md", cr_month_str.c_str());
            int line_next = FA_Search_Line("life.M.md", nx_month_str.c_str());

            char line_key[32];
            char mod_money[8];
            int line_tag = 0;

            cout << "Line-Key >>> ";
            cin >> line_key;

            line_tag = FA_Print_Line_Area("life.M.md", line_key, line_this, line_next);
            if(line_tag < 0)
                continue;

            cout << "Mod-Money >>> ";
            cin >> mod_money;

            if(char0check(mod_money) != 0)
            {
                continue;
            }

            gettimeofday(&tst, NULL);   ////////////////////////////// TimePoint_START

            FA_Line_Modify("life.M.md", line_tag, char2int(mod_money));

            gettimeofday(&ted, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            cin.ignore();
            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *  增加BOOK支出  * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_BOOK) == 0 ) 
        {
            char money[8];
            char content[32];

            string cr_month_str("Books.M");
            cr_month_str += cr_month;
            string nx_month_str("Books.M");
            nx_month_str += nx_month;

            cout << "Money >>> ";
            cin >> money;

            if(char0check(money) != 0)
                continue;

            cout << "Book >>> ";
            cin >> content;

            gettimeofday(&tst, NULL);   ////////////////////////////// TimePoint_START

            int line_this = FA_Search_Line("Books.M.md", cr_month_str.c_str());
            int line_next = FA_Search_Line("Books.M.md", nx_month_str.c_str());
            int line_tag = FA_Search_Line("life.M.md", cr_month_str.c_str());

            FA_Line_Add("Books.M.md", (line_next-1), false, char2int(money), content);
            int money_sum = FA_Line_Calculator("Books.M.md", line_this, line_next);
            FA_Sum_Modify("Books.M.md", (line_this+1), money_sum, 1);
            FA_Line_Modify("life.M.md", line_tag, char2int(money));

            gettimeofday(&ted, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            cin.ignore();
            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   增加TB支出   * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_TB) == 0 )
        {
            char money[8];
            char content[32];

            string cr_month_str("TB.M");
            cr_month_str += cr_month;
            string nx_month_str("TB.M");
            nx_month_str += nx_month;

            cout << "Money >>> ";
            cin >> money;

            if(char0check(money) != 0)
                continue;

            cout << "TB >>> ";
            cin >> content;

            gettimeofday(&tst, NULL);   ////////////////////////////// TimePoint_START

            int line_this = FA_Search_Line("TB.M.md", cr_month_str.c_str());
            int line_next = FA_Search_Line("TB.M.md", nx_month_str.c_str());
            int line_tag = FA_Search_Line("life.M.md", cr_month_str.c_str());

            FA_Line_Add("TB.M.md", (line_next-1), false, char2int(money), content);
            int money_sum = FA_Line_Calculator("TB.M.md", line_this, line_next);
            FA_Sum_Modify("TB.M.md", (line_this+1), money_sum, 1);
            FA_Line_Modify("life.M.md", line_tag, char2int(money));

            gettimeofday(&ted, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            cin.ignore();
            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *  增加KEEP支出  * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_KEEP) == 0 )
        {
            char money[8];
            char content[32];

            string cr_month_str("KEEP.M");
            cr_month_str += cr_month;
            string nx_month_str("KEEP.M");
            nx_month_str += nx_month;

            cout << "Money >>> ";
            cin >> money;

            if(char0check(money) != 0)
                continue;

            cout << "KEEP >>> ";
            cin >> content;

            gettimeofday(&tst, NULL);   ////////////////////////////// TimePoint_START

            int line_this = FA_Search_Line("KEEP.M.md", cr_month_str.c_str());
            int line_next = FA_Search_Line("KEEP.M.md", nx_month_str.c_str());
            int line_tag = FA_Search_Line("life.M.md", cr_month_str.c_str());

            FA_Line_Add("KEEP.M.md", (line_next-1), false, char2int(money), content);
            int money_sum = FA_Line_Calculator("KEEP.M.md", line_this, line_next);
            FA_Sum_Modify("KEEP.M.md", (line_this+1), money_sum, 1);
            FA_Line_Modify("life.M.md", line_tag, char2int(money));

            gettimeofday(&ted, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            cin.ignore();
            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   增加SA支出   * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_SA) == 0 )
        {
            char money[8];
            char content[32];

            string cr_month_str("sa.M");
            cr_month_str += cr_month;
            string nx_month_str("sa.M");
            nx_month_str += nx_month;

            cout << "Money >>> ";
            cin >> money;

            if(char0check(money) != 0)
                continue;

            cout << "sa >>> ";
            cin >> content;

            gettimeofday(&tst, NULL);   ////////////////////////////// TimePoint_START

            int line_this = FA_Search_Line("sa.M.md", cr_month_str.c_str());
            int line_next = FA_Search_Line("sa.M.md", nx_month_str.c_str());
            int line_tag = FA_Search_Line("life.M.md", cr_month_str.c_str());
            
            FA_Line_Add("sa.M.md", (line_next-1), false, char2int(money), content);
            int money_sum = FA_Line_Calculator("sa.M.md", line_this, line_next);
            FA_Sum_Modify("sa.M.md", (line_this+1), money_sum, 1);
            FA_Line_Modify("life.M.md", line_tag, char2int(money));

            gettimeofday(&ted, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;
         
            cin.ignore();
            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   增加DK支出   * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_DK) == 0 )
        {
            char money[8];
            char content[32];

            cout << "Money >>> ";
            cin >> money;

            if(char0check(money) != 0)
                continue;

            cout << "DK >>> ";
            cin >> content;

            gettimeofday(&tst, NULL);   ////////////////////////////// TimePoint_START

            int line_this = FA_Search_Line("DK.md", "# Digital Kingdom");
            int line_next = FA_Search_Line("DK.md", "## Total");
            int line_tag = FA_Search_Line("FA_TVT.md", "## DK");
            
            FA_Line_Add("DK.md", (line_next-1), false, char2int(money), content);
            int money_sum = FA_Line_Calculator("DK.md", line_this, line_next);

            // tip 番茄@20170906 - line_next需要+3，因为加了新的一行
            FA_Sum_Modify("DK.md", (line_next+3), money_sum, 2);
            FA_Sum_Modify("FA_TVT.md", (line_tag+1), money_sum, 1);

            gettimeofday(&ted, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            cin.ignore();
            continue;
        }

        /**************************************************/
        //   检查DK
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_DK) == 0)\
                && (CMD_argv.size() == 2))
        {
            FAitfX_Check_DK();

            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   增加NS支出   * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_NS) == 0 )
        {
            char money[8];
            char content[32];

            cout << "Money >>> ";
            cin >> money;

            if(char0check(money) != 0)
                continue;

            cout << "NS >>> ";
            cin >> content;

            gettimeofday(&tst, NULL);   ////////////////////////////// TimePoint_START

            int line_this = FA_Search_Line("NS.md", "# New Style");
            int line_next = FA_Search_Line("NS.md", "## Total");
            int line_tag = FA_Search_Line("FA_TVT.md", "## NS");
            
            FA_Line_Add("NS.md", (line_next-1), false, char2int(money), content);
            int money_sum = FA_Line_Calculator("NS.md", line_this, line_next);

            // tip 番茄@20170906 - line_next需要+3，因为加了新的一行
            FA_Sum_Modify("NS.md", (line_next+3), money_sum, 2);
            FA_Sum_Modify("FA_TVT.md", (line_tag+1), money_sum, 1);

            gettimeofday(&ted, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            cin.ignore();
            continue;
        }

        /**************************************************/
        //   检查NS
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_NS) == 0)\
                && (CMD_argv.size() == 2))
        {
            FAitfX_Check_NS();

            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * *   计算lottery收支  * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_LOTTERY) == 0 )
        {
            if(CMD_argv.size() != 4)
            {
                cout << "CMD is incomplete !" << endl;
                cout << "----------------------------------------" << endl;

                continue;
            }

            gettimeofday(&tst, NULL);   ////////////////////////////// TimePoint_START

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

            gettimeofday(&ted, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   检查lottery
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_LOTTERY) == 0)\
                && (CMD_argv.size() == 2))
        {
            FAitfX_Check_lottery();

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

            gettimeofday(&tst, NULL);   ////////////////////////////// TimePoint_START

            int line_bank = FA_Search_Line("FA_TVT.md", "广发银行");
            int line_alirest = FA_Search_Line("FA_TVT.md", "余额宝");

            FA_Balance("FA_TVT.md", line_bank, line_alirest, char2int(money), true);

            gettimeofday(&ted, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tst, ted);
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

            
            gettimeofday(&tst, NULL);   ////////////////////////////// TimePoint_START
            
            int line_bank = FA_Search_Line("FA_TVT.md", "广发银行");
            int line_alirest = FA_Search_Line("FA_TVT.md", "余额宝");

            FA_Balance("FA_TVT.md", line_bank, line_alirest, char2int(money), false);

            gettimeofday(&ted, NULL);   ////////////////////////////// TimePoint_END
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            cin.ignore();
            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * *     BackUp操作     * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_BACKUP) == 0 )
        {
            gettimeofday(&tst, NULL);

            FAitfX_BackUp("./FA_TVT.bak/");

            gettimeofday(&ted, NULL);
            showtcost(tst, ted);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *      TEST     * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( CMD_argv.begin()->compare(CMD_TEST) == 0 )
        {
            //FAitfX_Check_Month("09", "10");
            FAitfX_Update_Month(cr_month, nx_month);
            continue;   
        }

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

