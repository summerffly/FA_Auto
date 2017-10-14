
/*--------------------  CODE_ORIGIN @ 番茄  --------------------*/

#pragma once

#include "global.h"
#include "FBric_operator.h"
#include "FA_tools.h"

using namespace std;


int FAiX_BackUp(const char *bak_file_path)
{
    FA_BackUp("FA_TVT.md", bak_file_path);
    FA_BackUp("life.M.md", bak_file_path);
    FA_BackUp("Books.M.md", bak_file_path);
    FA_BackUp("KEEP.M.md", bak_file_path);
    FA_BackUp("TB.M.md", bak_file_path);
    FA_BackUp("sa.M.md", bak_file_path);
    FA_BackUp("DK.md", bak_file_path);
    FA_BackUp("NS.md", bak_file_path);
    FA_BackUp("lottery.md", bak_file_path);

    return 0;
}




/*--------------------  CODE_END @ 番茄  --------------------*/


