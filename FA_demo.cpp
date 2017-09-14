
/*----------  CODE_ORIGIN @ 番茄  ----------*/

#include "FA_tools.h"

using namespace std;

int FA_Sum_Check_Month();
int FA_Sum_Check_SZ();

int FA_Sum_Update_Month();
int FA_Sum_Update_SZ();

int FA_Line_Modify(int mod_money);


/*----------  MAIN_FUNC @ 番茄  ----------*/
int main(int argc, char **argv, char *env[])
{
    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;
    cout << "| |       FA_Automator System        | |" << endl;
    cout << "| |      >>>  番茄_summer  <<<       | |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;
    
    /*
    for(int i = 0; i < argc; i++)
    {
        printf("argc = %d, argv[%d] = %s\n", argc, i, argv[i]);
    }
    */
    
    while(1)
    {
        char sm_command[MAX_COMMAND];
        cout << "* * * * * * * * * * * * * * * * * * * *" << endl;
        cout << ">>> ";
        cin >> sm_command;
        cout << endl;
        
        
        if( strncmp(sm_command, CMD_DOWN, sizeof(CMD_DOWN)-1) == 0 )
        {
            cout << "----------------------------------------" << endl;
            cout << "|----- Summer's FA_Automator DOWN -----|" << endl;
            cout << "----------------------------------------" << endl;
            break;
        }
        
        
        
        if( strncmp(sm_command, CMD_SC_MN, sizeof(CMD_SC_MN)-1) == 0 )
        {
            FA_Sum_Check_Month();
        }
        else if( strncmp(sm_command, CMD_SC_SZ, sizeof(CMD_SC_SZ)-1) == 0 )
        {
            FA_Sum_Check_SZ();
        }
        else if( strncmp(sm_command, CMD_SU_MN, sizeof(CMD_SU_MN)-1) == 0 )
        {
            FA_Sum_Update_Month();
        }
        else if( strncmp(sm_command, CMD_SU_SZ, sizeof(CMD_SU_SZ)-1) == 0 )
        {
            FA_Sum_Update_SZ();
        }
        else if( strncmp(sm_command, CMD_LM, sizeof(CMD_LM)-1) == 0 )
        {
            char sm_money[10];
            cout << "* * * * * * * * * *" << endl;
            cout << "Enter Money:" << endl;
            cin >> sm_money;
            
            FA_Line_Modify(char2int(sm_money));
            FA_Sum_Update_Month();
            FA_Sum_Update_SZ();
        }
        else
        {
            cout << ">>> Error Command!" << endl;
        }
    }
    
    return 0;
}


/*----------  SUB_FUNC @ 番茄  ----------*/
int FA_Sum_Check_Month()
{
    char line_buffer[MAX_LINE_CHAR];
    string strLine[MAX_LINE];
    
    ifstream ifile("FA_SZ.md");
    if(!ifile.is_open())
    {
        cout << "Open File Error" << endl;
        return 1;
    }
    
    int month_sum = 0;
    bool r_flag = false;
    int line_index = 1;
    int line_tag = 0;
    
    while(!ifile.eof())
    {
        ifile.getline(line_buffer, MAX_LINE_CHAR);
        strLine[line_index] = line_buffer;
        
        if(sm_StrCnt(strLine[line_index], "8月结余") == 0)
        {
            r_flag = true;
            line_tag = line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "Summary") == 0)
        {
            r_flag = false;
            
            cout << "----------------------------------------" << endl;
            cout << "line_" << line_tag << " // " << strLine[line_tag].c_str() << endl;
            cout << "sum_month_check比对值: " << month_sum << endl;
            cout << "----------------------------------------" << endl;
            
            break;
        }
        
        if((r_flag == true) && (sm_StrCnt(strLine[line_index], "`-") == 0))
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            month_sum -= sm_StrMoneyFind_Line(strLine[line_index]);
        }
        
        line_index++;
    }
    
    ifile.close();
    
    return month_sum;
}


int FA_Sum_Check_SZ()
{
    char buffer[MAX_LINE_CHAR];
    string strLine[MAX_LINE];
    int numLine = 1;
    
    ifstream ifile("FA_SZ.md");
    if(!ifile.is_open())
    {
        cout << "Open File Error" << endl;
        return 1;
    }
    
    int sum = 0;
    
    while(!ifile.eof())
    {
        ifile.getline(buffer, MAX_LINE_CHAR);
        strLine[numLine] = buffer;
        
        if(sm_StrCnt(strLine[numLine], "原始财富") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum += sm_StrMoneyFind_Origin(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "home注资") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum += sm_StrMoneyFind_Origin(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "壹公寓搬家") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            numLine++;
            
            ifile.getline(buffer, MAX_LINE_CHAR);
            strLine[numLine] = buffer;
            
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum += sm_StrMoneyFind_Title(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "DGtler") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            numLine++;
            
            ifile.getline(buffer, MAX_LINE_CHAR);
            strLine[numLine] = buffer;
            
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum += sm_StrMoneyFind_Title(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "travel") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            numLine++;
            
            ifile.getline(buffer, MAX_LINE_CHAR);
            strLine[numLine] = buffer;
            
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum += sm_StrMoneyFind_Title(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "lottery") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            numLine++;
            
            ifile.getline(buffer, MAX_LINE_CHAR);
            strLine[numLine] = buffer;
            
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum += sm_StrMoneyFind_Title(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "月结余") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum += sm_StrMoneyFind_Month(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "当前财富") == 0)
        {
            cout << "----------------------------------------" << endl;
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            cout << "sum_check比对值: " << sum << endl;
            cout << "----------------------------------------" << endl;
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "押金") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum -= sm_StrMoneyFind_Line(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "蚂蚁借呗") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum += sm_StrMoneyFind_Origin(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "余额宝") == 0)
        {
            cout << "----------------------------------------" << endl;
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            cout << "sum_check比对值: " << sum << endl;
            cout << "----------------------------------------" << endl;
            numLine++;
            continue;
        }
        
        numLine++;
    }
    
    ifile.close();
    
    return sum;
}


int FA_Sum_Update_Month()
{
    cout << "----------------------------------------" << endl;
    
    char line_buffer[MAX_LINE_CHAR];
    string strLine[MAX_LINE];
    
    ifstream ifile("FA_SZ.md");
    if(!ifile.is_open())
    {
        cout << "Open File Error" << endl;
        return 1;
    }
    
    int month_in = 0;
    int month_out = 0;
    int month_rest = 0;
    int month_sum = 0;
    bool r_flag = false;
    int line_index = 1;
    int line_tag_in = 0;
    int line_tag_out = 0;
    int line_tag_rest = 0;
    
    while(!ifile.eof())
    {
        ifile.getline(line_buffer, MAX_LINE_CHAR);
        strLine[line_index] = line_buffer;
        
        if(sm_StrCnt(strLine[line_index], "8月薪资") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            month_in += sm_StrMoneyFind_Month(strLine[line_index]);
            
            line_tag_in = line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "8月支出") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            month_out += sm_StrMoneyFind_Month(strLine[line_index]);
            
            line_tag_out = line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "8月结余") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            month_rest += sm_StrMoneyFind_Month(strLine[line_index]);
            
            cout << "----------------------------------------" << endl;
            
            r_flag = true;
            line_tag_rest = line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "Summary") == 0)
        {
            r_flag = false;
            
            cout << "----------------------------------------" << endl;
            cout << "line_" << line_tag_out << " // " << strLine[line_tag_out].c_str() << endl;
            cout << "新的支出比对值: " << month_sum << endl;
            cout << "----------------------------------------" << endl;
        }
        
        if((r_flag == true) && (sm_StrCnt(strLine[line_index], "`-") == 0))
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            month_sum -= sm_StrMoneyFind_Line(strLine[line_index]);
        }
        
        line_index++;
    }
    
    sm_StrMoneyReplace_Month(strLine[line_tag_out], month_sum);
    sm_StrMoneyReplace_Month(strLine[line_tag_rest], (month_in+month_sum));
    
    ifile.close();
    
    ofstream ofile("FA_SZ.md");
    if(!ofile.is_open())
    {
        cout << "Write File Error" << endl;
        return 1;
    }
    
    for(int i = 1; i <= line_index; i++)
    {
        ofile << strLine[i].c_str() << endl;
    }
    
    ofile.close();
    
    return month_sum;
}


int FA_Sum_Update_SZ()
{
    char buffer[MAX_LINE_CHAR];
    string strLine[MAX_LINE];
    int numLine = 1;
    
    ifstream ifile("FA_SZ.md");
    if(!ifile.is_open())
    {
        cout << "Open File Error" << endl;
        return 1;
    }
    
    int sum = 0;
    
    while(!ifile.eof())
    {
        ifile.getline(buffer, MAX_LINE_CHAR);
        strLine[numLine] = buffer;
        
        if(sm_StrCnt(strLine[numLine], "原始财富") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum += sm_StrMoneyFind_Origin(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "home注资") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum += sm_StrMoneyFind_Origin(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "壹公寓搬家") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            numLine++;
            
            ifile.getline(buffer, MAX_LINE_CHAR);
            strLine[numLine] = buffer;
            
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum += sm_StrMoneyFind_Title(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "DGtler") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            numLine++;
            
            ifile.getline(buffer, MAX_LINE_CHAR);
            strLine[numLine] = buffer;
            
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum += sm_StrMoneyFind_Title(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "travel") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            numLine++;
            
            ifile.getline(buffer, MAX_LINE_CHAR);
            strLine[numLine] = buffer;
            
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum += sm_StrMoneyFind_Title(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "lottery") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            numLine++;
            
            ifile.getline(buffer, MAX_LINE_CHAR);
            strLine[numLine] = buffer;
            
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum += sm_StrMoneyFind_Title(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "月结余") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum += sm_StrMoneyFind_Month(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "当前财富") == 0)
        {
            cout << "----------------------------------------" << endl;
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            cout << "sum_check比对值: " << sum << endl;
            cout << "----------------------------------------" << endl;
            sm_StrMoneyReplace_Month(strLine[numLine], sum);
            
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "押金") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum -= sm_StrMoneyFind_Line(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "蚂蚁借呗") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sum += sm_StrMoneyFind_Origin(strLine[numLine]);
            numLine++;
            continue;
        }
        
        if(sm_StrCnt(strLine[numLine], "余额宝") == 0)
        {
            cout << "----------------------------------------" << endl;
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            cout << "sum_check比对值: " << sum << endl;
            cout << "----------------------------------------" << endl;
            sm_StrMoneyReplace_Month(strLine[numLine], sum);
            
            numLine++;
            continue;
        }
        
        numLine++;
    }
    
    ifile.close();
    
    ofstream ofile("FA_SZ.md");
    if(!ofile.is_open())
    {
        cout << "Write File Error" << endl;
        return 1;
    }
    
    for(int i = 1; i <= numLine; i++)
    {
        ofile << strLine[i].c_str() << endl;
    }
    
    ofile.close();
    
    return sum;
}


int FA_Line_Modify(int mod_money)
{
    char buffer[MAX_LINE_CHAR];
    string strLine[MAX_LINE];
    int numLine = 1;
    
    ifstream ifile("FA_SZ.md");
    if(!ifile.is_open())
    {
        cout << "Open File Error" << endl;
        return 1;
    }
        
    while(!ifile.eof())
    {
        ifile.getline(buffer, MAX_LINE_CHAR);
        strLine[numLine] = buffer;
            
        if(sm_StrCnt(strLine[numLine], "8月 生活费") == 0)
        {
            cout << "line: " << numLine << "// " << strLine[numLine].c_str() << endl;
            sm_StrMoneyReplace_Line(strLine[numLine], mod_money);
        }
        numLine++;
    }
        
    ifile.close();
        
    ofstream ofile("FA_SZ.md");
    if(!ofile.is_open())
    {
        cout << "Write File Error" << endl;
        return 1;
    }

    for(int i = 1; i <= numLine; i++)
    {
        ofile << strLine[i].c_str() << endl;
    }
        
    ofile.close();
        
    return 0;
}


/*----------  CODE_END @ 番茄  ----------*/

