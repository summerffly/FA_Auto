
/*--------------------  CODE_ORIGIN @ 番茄  --------------------*/

#include <vector>

#include "global.h"
#include "advanced_CMD.h"
#include "FBric_operator.h"
#include "FA_tool.h"
#include "FA_itfX.h"

using namespace std;


//***** 全局变量区 *****//
struct timeval tv_begin,tv_end;

char *version = new char[10];
char *or_month = new char[3];
char *cr_month = new char[3];

//********** Main入口 **********//
int main(int argc, char **argv, char *env[])
{
    if( FA_Read_Cfg(version, or_month, cr_month) == -1 )
    {
        return -1;
    }

    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;
    cout << "| |       FA_Automator System        | |" << endl;
    cout << "| |      >>>  番茄_summer  <<<       | |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;
    cout << "| |        Version: " << version << "_LTU" << "          | |" << endl;
    cout << "| |        Origin Month: " << or_month << "          | |" << endl;
    cout << "| |        Current Month: " << cr_month << "         | |" << endl;
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
            cout << ">>> CMD is blank line!" << endl;
            cout << "----------------------------------------" << endl;
            
            continue;
        }
        
        // 判断是否输入撤销CMD
        if( CMD_argv.back().compare(CMD_CANCEL) == 0 )
        {
            cout << ">>> CMD canceled!" << endl;
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

            FAitfX_Modify_Month(cr_month, char2int(CMD_argv.at(1).c_str()), CMD_argv.at(2).c_str());

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   更新 当月/上月 收支
        //   CMD-> update month/exmonth
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_UPDATE) == 0)\
                && ((CMD_argv.at(1).compare(CMD_MONTH) == 0)||(CMD_argv.at(1).compare(CMD_EXMONTH) == 0)) \
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);
            
            if( CMD_argv.at(1).compare(CMD_MONTH) == 0 )
            {
                FAitfX_Update_Month(cr_month);
            }
            else if( CMD_argv.at(1).compare(CMD_EXMONTH) == 0 )
            {
                FAitfX_Update_Month(GenPreMonth(cr_month).c_str());
            }
            else
            {
                cout << ">>> CMD Param Error!" << endl;
            }
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   检查 当月/上月 收支
        //   CMD-> check month/exmonth
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && ((CMD_argv.at(1).compare(CMD_MONTH) == 0)||(CMD_argv.at(1).compare(CMD_EXMONTH) == 0)) \
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);

            if( CMD_argv.at(1).compare(CMD_MONTH) == 0 )
            {
                FAitfX_Check_Month(cr_month);
            }
            else if( CMD_argv.at(1).compare(CMD_EXMONTH) == 0 )
            {
                FAitfX_Check_Month(GenPreMonth(cr_month).c_str());
            }
            else
            {
                cout << ">>> CMD Param Error!" << endl;
            }
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   增加 life_子项.md 支出
        //   CMD-> submonth book 100 《史记》
        //   CMD-> submonth keep 100 云南白药
        //   CMD-> submonth tb 100 居家小物
        //   CMD-> submonth sa 100 红包
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_SUNMONTH) == 0)\
                && (CMD_argv.size() == 4))
        {
            gettimeofday(&tv_begin, NULL);
    
            if( CMD_argv.at(1).compare(CMD_BOOK) == 0 )
            {
                FAitfX_Modify_SubMonth("./Books.M.md", "Books.M", cr_month,\
                                        char2int(CMD_argv.at(2).c_str()), CMD_argv.at(3).c_str());
            }
            else if( CMD_argv.at(1).compare(CMD_KEEP) == 0 )
            {
                FAitfX_Modify_SubMonth("./KEEP.M.md", "KEEP.M", cr_month,\
                                        char2int(CMD_argv.at(2).c_str()), CMD_argv.at(3).c_str());
            }
            else if( CMD_argv.at(1).compare(CMD_TB) == 0 )
            {
                FAitfX_Modify_SubMonth("./TB.M.md", "TB.M", cr_month,\
                                        char2int(CMD_argv.at(2).c_str()), CMD_argv.at(3).c_str());
            }
            else if( CMD_argv.at(1).compare(CMD_SA) == 0 )
            {
                FAitfX_Modify_SubMonth("./sa.M.md", "sa.M", cr_month,\
                                        char2int(CMD_argv.at(2).c_str()), CMD_argv.at(3).c_str());
            }
            else
            {
                cout << ">>> CMD Param Error!" << endl;
            }

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;
            
            continue;
        }

        /**************************************************/
        //   更新 life_子项.md 支出
        //   CMD-> update submonth book/keep/tb/sa
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_UPDATE) == 0)\
                && (CMD_argv.at(1).compare(CMD_SUNMONTH) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);
    
            if( CMD_argv.at(2).compare(CMD_BOOK) == 0 )
            {
                FAitfX_Update_SubMonth("./Books.M.md", "Books.M", cr_month);
            }
            else if( CMD_argv.at(2).compare(CMD_KEEP) == 0 )
            {
                FAitfX_Update_SubMonth("./KEEP.M.md", "KEEP.M", cr_month);
            }
            else if( CMD_argv.at(2).compare(CMD_TB) == 0 )
            {
                FAitfX_Update_SubMonth("./TB.M.md", "TB.M", cr_month);
            }
            else if( CMD_argv.at(2).compare(CMD_SA) == 0 )
            {
                FAitfX_Update_SubMonth("./sa.M.md", "sa.M", cr_month);
            }
            else
            {
                cout << ">>> CMD Param Error!" << endl;
            }

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;
             
            continue;
        }

        /**************************************************/
        //   检查 life_子项.md 支出
        //   CMD-> check submonth book/keep/tb/sa
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_SUNMONTH) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);
    
            if( CMD_argv.at(2).compare(CMD_BOOK) == 0 )
            {
                FAitfX_Check_SubMonth("./Books.M.md", "Books.M", cr_month);
            }
            else if( CMD_argv.at(2).compare(CMD_KEEP) == 0 )
            {
                FAitfX_Check_SubMonth("./KEEP.M.md", "KEEP.M", cr_month);
            }
            else if( CMD_argv.at(2).compare(CMD_TB) == 0 )
            {
                FAitfX_Check_SubMonth("./TB.M.md", "TB.M", cr_month);
            }
            else if( CMD_argv.at(2).compare(CMD_SA) == 0 )
            {
                FAitfX_Check_SubMonth("./sa.M.md", "sa.M", cr_month);
            }
            else
            {
                cout << ">>> CMD Param Error!" << endl;
            }

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;
             
            continue;
        }

        /**************************************************/
        //   更新 FA_TVT
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_UPDATE) == 0)\
                && (CMD_argv.at(1).compare(CMD_TVT) == 0)\
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_Update_TVT();

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   检查 FA_TVT
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_TVT) == 0)\
                && (CMD_argv.size() == 2))     
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_Check_TVT();

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   增加 & 更新 DK 支出
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
        //   增加 & 更新 NS 支出
        //   CMD-> ns 200 优衣库
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
        //   增加 & 更新 lottery 收支
        //   CMD-> lottery -- 128 201711102
        //   CMD-> lottery ++ 3000 201711102
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_LOTTERY) == 0)\
                && (CMD_argv.size() == 4))
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_lottery(CMD_argv.at(1), char2int(CMD_argv.at(2).c_str()), CMD_argv.at(3).c_str());

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   更新 TVT_分项 收支
        //   CMD-> update title dk/ns/lottery
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_UPDATE) == 0)\
                && (CMD_argv.at(1).compare(CMD_TITLE) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);
            
            if( CMD_argv.at(2).compare(CMD_DK) == 0 )
            {
                FAitfX_Update_Title("./DK.md", "# Digital Kingdom", "## DK");
            }
            else if( CMD_argv.at(2).compare(CMD_NS) == 0 )
            {
                FAitfX_Update_Title("./NS.md", "# New Style", "## NS");
            }
            else if( CMD_argv.at(2).compare(CMD_LOTTERY) == 0 )
            {
                FAitfX_Update_Title("./lottery.md", "# lottery", "## lottery");
            }
            else
            {
                cout << ">>> CMD Param Error!" << endl;
            }
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   检查 TVT_分项 收支
        //   CMD-> check title dk/ns/lottery
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_TITLE) == 0)\
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);
            
            if( CMD_argv.at(2).compare(CMD_DK) == 0 )
            {
                FAitfX_Check_Title("./DK.md", "# Digital Kingdom", "## DK");
            }
            else if( CMD_argv.at(2).compare(CMD_NS) == 0 )
            {
                FAitfX_Check_Title("./NS.md", "# New Style", "## NS");
            }
            else if( CMD_argv.at(2).compare(CMD_LOTTERY) == 0 )
            {
                FAitfX_Check_Title("./lottery.md", "# lottery", "## lottery");
            }
            else
            {
                cout << ">>> CMD Param Error!" << endl;
            }
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   balance 操作
        //   CMD-> balance ++ 100   // 广发银行 +100
        //   CMD-> balance -- 200   // 广发银行 -200
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_BALANCE) == 0)
                && (CMD_argv.size() == 3))
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_Balance(char2int(CMD_argv.at(2).c_str()), CMD_argv.at(1).c_str());

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   BackUp 全备份
        //   CMD-> bakup
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_BACKUP) == 0)\
                && (CMD_argv.size() == 1))
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_BackUp("./FA_TVT.bak/");

            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   检查 .md文件 收支
        //   CMD-> check temp
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_CHECK) == 0)\
                && (CMD_argv.at(1).compare(CMD_TEMP) == 0)\
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_CheckFile("./temp.Nov.md", "# temp.Nov", "---");
            
            gettimeofday(&tv_end, NULL);
            showtcost(tv_begin, tv_end);
            cout << "----------------------------------------" << endl;

            continue;
        }

        /**************************************************/
        //   对比分析 月度支出
        //   CMD-> analysis 支出
        /**************************************************/
        else if((CMD_argv.begin()->compare(CMD_ANALYSIS) == 0)\
                && (CMD_argv.size() == 2))
        {
            gettimeofday(&tv_begin, NULL);

            FAitfX_Analysis_Month(CMD_argv.at(1).c_str(), or_month, cr_month);
            
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
            cout << or_month << endl;

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

