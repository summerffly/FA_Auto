
/*--------------------  CODE_ORIGIN @ 番茄  --------------------*/

#include "global.h"
#include "FA_tools.h"

using namespace std;


/*--------------------  MAIN  --------------------*/

int main(int argc, char **argv, char *env[])
{
    char *version = new char[10];
    char *ex_month = new char[3];
    char *cr_month = new char[3];
    char *nx_month = new char[3];

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
    cout << "| |           Version: " << version << "           | |" << endl;
    cout << "| |       Previous Month: " << ex_month << "         | |" << endl;    
    cout << "| |        Current Month: " << cr_month << "         | |" << endl;
    cout << "| |          Next Month: " << nx_month << "          | |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;


    // CMD循环模式
    while(1)
    {
        char sm_command[MAX_COMMAND];            
        cout << "CMD >>> ";
        cin >> sm_command;

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *    关闭系统    * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        if( strncmp(sm_command, CMD_SD, strlen(CMD_SD)) == 0 )
        {
            cout << "----------------------------------------" << endl;
            cout << "|-----    FA_Automator SHUTDOWN   -----|" << endl;
            cout << "----------------------------------------" << endl;
            break;
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   显示md文件   * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_PRINT_FILE, strlen(CMD_PRINT_FILE)) == 0 )
        {
            char file_name[32];

            cout << "File >>> ";
            cin >> file_name;
            
            cout << "----------------------------------------" << endl;
            FA_Print_File(file_name);
            cout << "----------------------------------------" << endl;            
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *    搜索单行    * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( !strncmp(sm_command, CMD_PRINT_LINE, strlen(CMD_PRINT_LINE)) )
        {
            char file_name[32];
            char line_key[32];
            
            cout << "File >>> ";
            cin >> file_name;

            cout << "Line-Key >>> ";
            cin >> line_key;

            FA_Print_Line(file_name, line_key);
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *  检查月度支出   * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_SC_MN, strlen(CMD_SC_MN)) == 0 )
        {
            string cr_month_str("## life.M");
            cr_month_str += cr_month;
            string nx_month_str("## life.M");
            nx_month_str += nx_month;

            int line_this = FA_Search_Line("life.M.md", cr_month_str.c_str());
            int line_next = FA_Search_Line("life.M.md", nx_month_str.c_str());

            FA_Sum_Check_Month(line_this);
            
            cout << "CHECK " << char2int(cr_month) << "月支出: " << FA_Line_Calculator("life.M.md", line_this, line_next) << endl;       
            cout << "----------------------------------------" << endl;            
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *  更新月度支出   * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_SU_MN, strlen(CMD_SU_MN)) == 0 )
        {
            string cr_month_str("## life.M");
            cr_month_str += cr_month;
            string nx_month_str("## life.M");
            nx_month_str += nx_month;

            int line_this = FA_Search_Line("life.M.md", cr_month_str.c_str());
            int line_next = FA_Search_Line("life.M.md", nx_month_str.c_str());
            int line_sz = FA_Search_Line("FA_TVT.md", cr_month_str.c_str());
            
            int money_sum = FA_Line_Calculator("life.M.md", line_this, line_next);

            FA_Sum_Update_Month(line_this, line_sz, money_sum);
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * *  更新上个月度收支  * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_SU_EXMN, strlen(CMD_SU_EXMN)) == 0 )
        {
            string ex_month_str("## life.M");
            ex_month_str += ex_month;

            int line_this = FA_Search_Line("life.M.md", ex_month_str.c_str());
            int line_sz = FA_Search_Line("FA_TVT.md", ex_month_str.c_str());
            
            FA_Sum_Update_ExMonth(line_this, line_sz);
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   检查TVT支出  * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_SC_TVT, strlen(CMD_SC_TVT)) == 0 )
        {
            FA_Sum_Check_TVT();
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   更新TVT支出  * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_SU_TVT, strlen(CMD_SU_TVT)) == 0 )
        {
            FA_Sum_Update_TVT();
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *  更改LIFE支出  * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_LIFE, strlen(CMD_LIFE)) == 0 )
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

            FA_Line_Modify("life.M.md", line_tag, char2int(mod_money));
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *  增加BOOK支出  * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_BOOK, strlen(CMD_BOOK)) == 0 )
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

            int line_this = FA_Search_Line("Books.M.md", cr_month_str.c_str());
            int line_next = FA_Search_Line("Books.M.md", nx_month_str.c_str());
            int line_tag = FA_Search_Line("life.M.md", cr_month_str.c_str());

            FA_Line_Add("Books.M.md", (line_next-1), false, char2int(money), content);
            int money_sum = FA_Line_Calculator("Books.M.md", line_this, line_next);
            FA_Sum_Modify("Books.M.md", (line_this+1), money_sum, 1);
            FA_Line_Modify("life.M.md", line_tag, char2int(money));
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   增加TB支出   * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_TB, strlen(CMD_TB)) == 0 )
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

            int line_this = FA_Search_Line("TB.M.md", cr_month_str.c_str());
            int line_next = FA_Search_Line("TB.M.md", nx_month_str.c_str());
            int line_tag = FA_Search_Line("life.M.md", cr_month_str.c_str());

            FA_Line_Add("TB.M.md", (line_next-1), false, char2int(money), content);
            int money_sum = FA_Line_Calculator("TB.M.md", line_this, line_next);
            FA_Sum_Modify("TB.M.md", (line_this+1), money_sum, 1);
            FA_Line_Modify("life.M.md", line_tag, char2int(money));
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *  增加KEEP支出  * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_KEEP, strlen(CMD_KEEP)) == 0 )
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

            int line_this = FA_Search_Line("KEEP.M.md", cr_month_str.c_str());
            int line_next = FA_Search_Line("KEEP.M.md", nx_month_str.c_str());
            int line_tag = FA_Search_Line("life.M.md", cr_month_str.c_str());

            FA_Line_Add("KEEP.M.md", (line_next-1), false, char2int(money), content);
            int money_sum = FA_Line_Calculator("KEEP.M.md", line_this, line_next);
            FA_Sum_Modify("KEEP.M.md", (line_this+1), money_sum, 1);
            FA_Line_Modify("life.M.md", line_tag, char2int(money));
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   增加SA支出   * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_SA, strlen(CMD_SA)) == 0 )
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

            int line_this = FA_Search_Line("sa.M.md", cr_month_str.c_str());
            int line_next = FA_Search_Line("sa.M.md", nx_month_str.c_str());
            int line_tag = FA_Search_Line("life.M.md", cr_month_str.c_str());
            
            FA_Line_Add("sa.M.md", (line_next-1), false, char2int(money), content);
            int money_sum = FA_Line_Calculator("sa.M.md", line_this, line_next);
            FA_Sum_Modify("sa.M.md", (line_this+1), money_sum, 1);
            FA_Line_Modify("life.M.md", line_tag, char2int(money));            
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   增加DK支出   * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_DK, strlen(CMD_DK)) == 0 )
        {
            char money[8];
            char content[32];

            cout << "Money >>> ";
            cin >> money;

            if(char0check(money) != 0)
                continue;

            cout << "DK >>> ";
            cin >> content;

            int line_this = FA_Search_Line("DK.md", "# Digital Kingdom");
            int line_next = FA_Search_Line("DK.md", "## Total");
            int line_tag = FA_Search_Line("FA_TVT.md", "## DK");
            
            FA_Line_Add("DK.md", (line_next-1), false, char2int(money), content);
            int money_sum = FA_Line_Calculator("DK.md", line_this, line_next);

            // tip 番茄@20170906 - line_next需要+3，因为加了新的一行
            FA_Sum_Modify("DK.md", (line_next+3), money_sum, 2);
            FA_Sum_Modify("FA_TVT.md", (line_tag+1), money_sum, 1);
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   增加NS支出   * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_NS, strlen(CMD_NS)) == 0 )
        {
            char money[8];
            char content[32];

            cout << "Money >>> ";
            cin >> money;

            if(char0check(money) != 0)
                continue;

            cout << "NS >>> ";
            cin >> content;

            int line_this = FA_Search_Line("NS.md", "# New Style");
            int line_next = FA_Search_Line("NS.md", "## Total");
            int line_tag = FA_Search_Line("FA_TVT.md", "## NS");
            
            FA_Line_Add("NS.md", (line_next-1), false, char2int(money), content);
            int money_sum = FA_Line_Calculator("NS.md", line_this, line_next);

            // tip 番茄@20170906 - line_next需要+3，因为加了新的一行
            FA_Sum_Modify("NS.md", (line_next+3), money_sum, 2);
            FA_Sum_Modify("FA_TVT.md", (line_tag+1), money_sum, 1);
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * *   计算lottery收支  * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_LOTTERY, strlen(CMD_LOTTERY)) == 0 )
        {
            char flag;
            char money[8];
            char date[10];

            bool pnFlag = false;
            unsigned int value = 0;
            string strInsetLine;

            cout << "++ or -- >>> ";
            cin >> flag;

            if((flag != '+') && (flag != '-'))
                continue;

            cout << "Money >>> ";
            cin >> money;

            if(char0check(money) != 0)
                continue;

            cout << "date >>> ";
            cin >> date;

            if(strlen(date) != 8)
                continue;
            
            if( flag == '+' )
            {
                pnFlag = true;
                strInsetLine += "足彩收入_";
                strInsetLine += date;
            }
            else
            {
                pnFlag = false;
                strInsetLine += "足彩支出_";
                strInsetLine += date;
            }

            int line_this = FA_Search_Line("lottery.md", "# lottery");
            int line_next = FA_Search_Line("lottery.md", "## Total");
            int line_tag = FA_Search_Line("FA_TVT.md", "## lottery");
            
            FA_Line_Add("lottery.md", (line_next-1), pnFlag, char2int(money), strInsetLine.c_str());
            int money_sum = FA_Line_Calculator("lottery.md", line_this, line_next);

            FA_Sum_Modify("lottery.md", (line_next+3), money_sum, 2);
            FA_Sum_Modify("FA_TVT.md", (line_tag+1), money_sum, 1);

            FA_Sum_Update_TVT();

            int line_bank = FA_Search_Line("FA_TVT.md", "广发银行");
            int line_alirest = FA_Search_Line("FA_TVT.md", "余额宝");

            if( flag == '+' )
            {
                FA_Balance("FA_TVT.md", line_bank, line_alirest, char2int(money), false);
            }
            else
            {
                FA_Balance("FA_TVT.md", line_bank, line_alirest, char2int(money), true);
            }
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *   balance操作  * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_BALANCE, strlen(CMD_BALANCE)) == 0 )
        {
            char money[8];

            cout << "Money >>> ";
            cin >> money;

            if(char0check(money) != 0)
                continue;

            int line_bank = FA_Search_Line("FA_TVT.md", "广发银行");
            int line_alirest = FA_Search_Line("FA_TVT.md", "余额宝");

            FA_Balance("FA_TVT.md", line_bank, line_alirest, char2int(money), true);
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * *    rebalance操作   * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_REBALANCE, strlen(CMD_REBALANCE)) == 0 )
        {
            char money[8];

            cout << "Money >>> ";
            cin >> money;

            if(char0check(money) != 0)
                continue;

            int line_bank = FA_Search_Line("FA_TVT.md", "广发银行");
            int line_alirest = FA_Search_Line("FA_TVT.md", "余额宝");

            FA_Balance("FA_TVT.md", line_bank, line_alirest, char2int(money), false);
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * *     BackUp操作     * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_BACKUP, strlen(CMD_BACKUP)) == 0 )
        {
            FA_BackUp("FA_TVT.md");
            FA_BackUp("life.M.md");
            FA_BackUp("Books.M.md");
            FA_BackUp("KEEP.M.md");
            FA_BackUp("TB.M.md");
            FA_BackUp("sa.M.md");
            FA_BackUp("DK.md");
            FA_BackUp("NS.md");
            FA_BackUp("lottery.md");
        }

        /* * * * * * * * * * * * * * * * * * * * * * */
        /* * * * * * * *      TEST     * * * * * * * */
        /* * * * * * * * * * * * * * * * * * * * * * */
        else if( strncmp(sm_command, CMD_TEST, strlen(CMD_TEST)) == 0 )
        {
            continue;   
        }

        else
        {
            cout << "----------------------------------------" << endl;
            cout << ">>>           Error Command          <<<" << endl;
            cout << "----------------------------------------" << endl;
        }
    }

    return 0;
}


/*--------------------  CODE_END @ 番茄  --------------------*/


