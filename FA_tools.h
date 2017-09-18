
/*----------  CODE_ORIGIN @ 番茄  ----------*/

#include <fstream>
#include <iomanip>

#include "global.h"
#include "str_operator.h"


using namespace std;


/*----------  TOOLS @ 番茄  ----------*/

int FA_Print_File()
{
    cout << "----------------------------------------" << endl;
    
    char buffer[MAX_LINE_CHAR];
    string strLine[MAX_LINE];
    
    int line_index = 1;
    
    ifstream ifile("FA_SZ.md");
    if(!ifile.is_open())
    {
        cout << "Open File Error" << endl;
        return -1;
    }
    
    while(!ifile.eof())
    {
        ifile.getline(buffer, MAX_LINE_CHAR);
        strLine[line_index] = buffer;
        
        cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
        
        line_index++;
        
        if(!sm_StrCnt(strLine[line_index], "---"))
        {
            break;
        }
    }
    
    ifile.close();
    
    cout << "----------------------------------------" << endl;
    
    return 0;
}

int FA_Print_Line(const char *line_key)
{
    cout << "----------------------------------------" << endl;
    
    char buffer[MAX_LINE_CHAR];
    string strLine[MAX_LINE];
    
    int line_index = 1;
    int line_tag = 0;
    
    ifstream ifile("FA_SZ.md");
    if(!ifile.is_open())
    {
        cout << "Open File Error" << endl;
        return -1;
    }
    
    while(!ifile.eof())
    {
        ifile.getline(buffer, MAX_LINE_CHAR);
        strLine[line_index] = buffer;
        
        if(sm_StrCnt(strLine[line_index], line_key) == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            line_tag++;
        }
        
        line_index++;
    }
    
    ifile.close();
    
    if(line_tag != 0)
    {
        cout << "----------------------------------------" << endl;
        return 0;
    }
    else
    {
        cout << ">>>  NO LINE MATCH  <<<" << endl;
        cout << "----------------------------------------" << endl;
        
        return 1;
    }
    
}


int FA_Sum_Check_Month()
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
            cout << "Sum_Check_Month: " << month_sum << endl;
            cout << "----------------------------------------" << endl;
            
            break;
        }
        
        if((r_flag == true) && (sm_StrCnt(strLine[line_index], "`") == 0))
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            month_sum += sm_StrMoneyFind_Line(strLine[line_index]);
        }
        
        line_index++;
    }
    
    ifile.close();
    
    return month_sum;
}


int FA_Sum_Check_SZ()
{
    cout << "----------------------------------------" << endl;

    char buffer[MAX_LINE_CHAR];
    string strLine[MAX_LINE];
    
    ifstream ifile("FA_SZ.md");
    if(!ifile.is_open())
    {
        cout << "Open File Error" << endl;
        return 1;
    }
    
    int money_sum = 0;
    int line_index = 1;
  
    while(!ifile.eof())
    {
        ifile.getline(buffer, MAX_LINE_CHAR);
        strLine[line_index] = buffer;
        
        if(sm_StrCnt(strLine[line_index], "原始财富") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Top(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "home注资") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Top(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "壹公寓搬家") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            line_index++;
            
            ifile.getline(buffer, MAX_LINE_CHAR);
            strLine[line_index] = buffer;
            
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Title(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "DGtler") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            line_index++;
            
            ifile.getline(buffer, MAX_LINE_CHAR);
            strLine[line_index] = buffer;
            
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Title(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "travel") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            line_index++;
            
            ifile.getline(buffer, MAX_LINE_CHAR);
            strLine[line_index] = buffer;
            
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Title(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "lottery") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            line_index++;
            
            ifile.getline(buffer, MAX_LINE_CHAR);
            strLine[line_index] = buffer;
            
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Title(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "月结余") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Month(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "当前财富") == 0)
        {
            cout << "----------------------------------------" << endl;
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            cout << "Sum_Check_SZ: " << money_sum << endl;
            cout << "----------------------------------------" << endl;
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "押金") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Line(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "蚂蚁借呗") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Top(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "余额宝") == 0)
        {
            cout << "----------------------------------------" << endl;
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            cout << "Sum_Check_SZ: " << money_sum << endl;
            cout << "----------------------------------------" << endl;
            line_index++;
            continue;
        }
        
        line_index++;
    }
    
    ifile.close();
    
    return money_sum;
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
            month_in = sm_StrMoneyFind_Month(strLine[line_index]);
            
            line_tag_in = line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "8月支出") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            month_out = sm_StrMoneyFind_Month(strLine[line_index]);
            
            line_tag_out = line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "8月结余") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            month_rest = sm_StrMoneyFind_Month(strLine[line_index]);
            
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
            cout << "Sum_Update_Month: " << month_sum << endl;
            cout << "----------------------------------------" << endl;
        }
        
        if((r_flag == true) && (sm_StrCnt(strLine[line_index], "`") == 0))
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            month_sum += sm_StrMoneyFind_Line(strLine[line_index]);
        }
        
        line_index++;
    }
    
    sm_StrMoneyModify_Month(strLine[line_tag_out], month_sum);
    sm_StrMoneyModify_Month(strLine[line_tag_rest], (month_in + month_sum));
    
    ifile.close();
    
    WirteFile("FA_SZ.md", strLine, line_index);
    
    return month_sum;
}


int FA_Sum_Update_SZ()
{
    cout << "----------------------------------------" << endl;

    char buffer[MAX_LINE_CHAR];
    string strLine[MAX_LINE];
    
    ifstream ifile("FA_SZ.md");
    if(!ifile.is_open())
    {
        cout << "Open File Error" << endl;
        return 1;
    }
    
    int money_sum = 0;
    int line_index = 1;
   
    while(!ifile.eof())
    {
        ifile.getline(buffer, MAX_LINE_CHAR);
        strLine[line_index] = buffer;
        
        if(sm_StrCnt(strLine[line_index], "原始财富") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Top(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "home注资") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Top(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "壹公寓搬家") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            line_index++;
            
            ifile.getline(buffer, MAX_LINE_CHAR);
            strLine[line_index] = buffer;
            
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Title(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "DGtler") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            line_index++;
            
            ifile.getline(buffer, MAX_LINE_CHAR);
            strLine[line_index] = buffer;
            
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Title(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "travel") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            line_index++;
            
            ifile.getline(buffer, MAX_LINE_CHAR);
            strLine[line_index] = buffer;
            
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Title(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "lottery") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            line_index++;
            
            ifile.getline(buffer, MAX_LINE_CHAR);
            strLine[line_index] = buffer;
            
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Title(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "月结余") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Month(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "当前财富") == 0)
        {
            cout << "----------------------------------------" << endl;
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            cout << "Sum_Update_SZ: " << money_sum << endl;
            cout << "----------------------------------------" << endl;
            sm_StrMoneyModify_Top(strLine[line_index], money_sum);
            
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "押金") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Line(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "蚂蚁借呗") == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            money_sum += sm_StrMoneyFind_Top(strLine[line_index]);
            line_index++;
            continue;
        }
        
        if(sm_StrCnt(strLine[line_index], "余额宝") == 0)
        {
            cout << "----------------------------------------" << endl;
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            cout << "Sum_Update_SZ: " << money_sum << endl;
            cout << "----------------------------------------" << endl;
            sm_StrMoneyModify_Top(strLine[line_index], money_sum);
            
            line_index++;
            continue;
        }
        
        line_index++;
    }
    
    ifile.close();
    
    WirteFile("FA_SZ.md", strLine, line_index);
    
    return money_sum;
}


int FA_Line_Modify(const char *line_id, int money_mod)
{
    cout << "----------------------------------------" << endl;

    char buffer[MAX_LINE_CHAR];
    string strLine[MAX_LINE];
    
    int line_index = 1;
    
    ifstream ifile("FA_SZ.md");
    if(!ifile.is_open())
    {
        cout << "Open File Error" << endl;
        return -1;
    }
        
    while(!ifile.eof())
    {
        ifile.getline(buffer, MAX_LINE_CHAR);
        strLine[line_index] = buffer;
            
        if(sm_StrCnt(strLine[line_index], line_id) == 0)
        {
            cout << "line_" << line_index << " // " << strLine[line_index].c_str() << endl;
            int money_new = sm_StrMoneyFind_Line(strLine[line_index]) - money_mod;
            sm_StrMoneyModify_Line(strLine[line_index], money_new);
        }
        line_index++;
    }
        
    ifile.close();
    
    WirteFile("FA_SZ.md", strLine, line_index);
        
    return 0;
}


/*----------  CODE_END @ 番茄  ----------*/

