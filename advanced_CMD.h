
/*--------------------  CODE_ORIGIN @ 番茄  --------------------*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>

#include "global.h"

using namespace std;

/*-------------------------------------------------------------------*/
/*--------------------     CMD处理函数 @ 番茄      --------------------*/
/*-------------------------------------------------------------------*/

int CMD_Line_Parser(char *CMD_ad_buffer, int &CMD_argc, vector<string> &CMD_argv)
{
    const char *delimiters = " ";

    CMD_argc = 0;
    CMD_argv.clear();

    char *CMD_temp = strtok(CMD_ad_buffer, delimiters);
    while( CMD_temp )
    {
        CMD_argc++;
        CMD_argv.push_back(CMD_temp);
        CMD_temp = strtok(NULL, delimiters);
    }

    if( CMD_argc == 0 )
    {
        return -1;
    }

    return 0;
}


double showtcost(struct timeval tst, struct timeval ted)
{
    long tcost_us;
    double tcost_ms;

    tcost_us = (ted.tv_sec-tst.tv_sec) * 1000000 + ted.tv_usec-tst.tv_usec;
    tcost_ms = (double)tcost_us/1000;

    cout << "STEP TIME COST: " << tcost_ms << " ms" << endl;

    return tcost_ms;
}


/*--------------------  CODE_END @ 番茄  --------------------*/


