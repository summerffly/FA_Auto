
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


double showtcost(struct timeval tv_begin, struct timeval tv_end)
{
    long tv_pass_us;
    double tv_pass_ms;

    tv_pass_us = (tv_end.tv_sec-tv_begin.tv_sec) * 1000000 + tv_end.tv_usec-tv_begin.tv_usec;
    tv_pass_ms = (double)tv_pass_us/1000;

    cout << "STEP TIME COST: " << tv_pass_ms << " ms" << endl;

    return tv_pass_ms;
}


/*--------------------  CODE_END @ 番茄  --------------------*/


