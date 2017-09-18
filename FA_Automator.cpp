
/*----------  CODE_ORIGIN @ 番茄  ----------*/

#include "global.h"
#include "FA_tools.h"

using namespace std;


int main(int argc, char **argv, char *env[])
{
    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;
    cout << "| |       FA_Automator System        | |" << endl;
    cout << "| |      >>>  番茄_summer  <<<       | |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;
    
    
    while(1)
    {
        char sm_command[MAX_COMMAND];
        cout << "CMD >>> ";
        cin >> sm_command;
        
        if( strncmp(sm_command, CMD_DOWN, sizeof(CMD_DOWN)-1) == 0 )
        {
            cout << "----------------------------------------" << endl;
            cout << "|----- Summer's FA_Automator DOWN -----|" << endl;
            cout << "----------------------------------------" << endl;
            break;
        }
        
        if( strncmp(sm_command, CMD_PT_SZ, sizeof(CMD_PT_SZ)-1) == 0 )
        {
            FA_Print_File();
        }
        if( !strncmp(sm_command, CMD_PT_LN, sizeof(CMD_PT_LN)-1) )
        {
            char sm_line[16];
            
            cout << "Line >>> ";
            cin >> sm_line;
            
            if( strncmp(sm_line, CMD_BACK, sizeof(CMD_BACK)-1) == 0 )
            {
                continue;
            }
            else
            {
                FA_Print_Line(sm_line);
            }
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
            char sm_line[16];
            char sm_money[8];
            
            cout << "Line >>> ";
            cin >> sm_line;
            
            if( strncmp(sm_line, CMD_BACK, sizeof(CMD_BACK)-1) == 0 )
            {
                cout << "----------------------------------------" << endl;
                continue;
            }
            else
            {
                if( FA_Print_Line(sm_line) == 1 )
                    continue;
            }
            
            cout << "Money >>> ";
            cin >> sm_money;
            if( strncmp(sm_money, CMD_BACK, sizeof(CMD_BACK)-1) == 0 )
            {
                cout << "----------------------------------------" << endl;
                continue;
            }
            else
            {
                FA_Line_Modify(sm_line, char2int(sm_money));
                FA_Sum_Update_Month();
                FA_Sum_Update_SZ();
            }
        }
        else if( strncmp(sm_command, CMD_TEST, sizeof(CMD_TEST)-1) == 0 )
        {
            cout << "summer_test" << endl;
        }
        else
        {
            cout << "----------------------------------------" << endl;
            cout << ">>>  Error Command  <<<" << endl;
            cout << "----------------------------------------" << endl;
        }
    }
    
    return 0;
}


/*----------  CODE_END @ 番茄  ----------*/


