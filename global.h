
/*--------------------  CODE_ORIGIN @ 番茄  --------------------*/

#pragma once

#include <string>
#include <regex>

using namespace std;

/*--------------------  DEFINE Library  --------------------*/

#define MAX_COMMAND     128     // 命令最大字符数
#define MAX_LINE_CHAR   128     // 每行最大字符数
#define MAX_LINE        256     // 最大支持行数

/*-------------------- RegEx Library --------------------*/

string pattern_cv = "^Current Version = \\d\\.\\d$";
regex RE_cv(pattern_cv);

string pattern_pm = "^Previous Month = \\d{2}$";
regex RE_pm(pattern_pm);

string pattern_cm = "^Current Month = \\d{2}$";
regex RE_cm(pattern_cm);

string pattern_nm = "^Next Month = \\d{2}$";
regex RE_nm(pattern_nm);

string pattern_month = "^## life.M\\d{2}$";
regex RE_month(pattern_month);

string pattern_ofi = "^原始财富.*$";
regex RE_ofi(pattern_ofi);

string pattern_cfi = "^当前财富.*$";
regex RE_cfi(pattern_cfi);

string pattern_lottery = "^## lottery$";
regex RE_lottery(pattern_lottery);

string pattern_dk = "^## DK$";
regex RE_dk(pattern_dk);

string pattern_ns = "^## NS$";
regex RE_ns(pattern_ns);

string pattern_de_one = "^.*押金_壹公寓$";
regex RE_de_one(pattern_de_one);

string pattern_de_mobike = "^.*押金_mobike$";
regex RE_de_mobike(pattern_de_mobike);

string pattern_de_ofo = "^.*押金_ofo$";
regex RE_de_ofo(pattern_de_ofo);

string pattern_loan = "^.*蚂蚁借呗$";
regex RE_loan(pattern_loan);

string pattern_bank = "^广发银行.*$";
regex RE_bank(pattern_bank);

string pattern_alirest = "^余额宝.*$";
regex RE_alirest(pattern_alirest);

string pattern_end = "^---$";
regex RE_end(pattern_end);


/*-------------------- COMMAND Library --------------------*/

const char *CMD_PRINT = "print";
const char *CMD_SEARCH = "search";

const char *CMD_CHECK = "check";
const char *CMD_UPDATE = "update";

const char *CMD_MONTH = "month";
const char *CMD_TVT = "tvt";

const char *CMD_EX = "ex";

const char *CMD_SC_MN = "check-month";
const char *CMD_SC_TVT = "check-tvt";

const char *CMD_SU_MN = "update-month";
const char *CMD_SU_TVT = "update-tvt";

const char *CMD_SU_EXMN = "update-ex-month";

const char *CMD_LIFE = "life";

const char *CMD_BOOK = "book";
const char *CMD_TB = "tb";
const char *CMD_KEEP = "keep";
const char *CMD_SA = "sa";

const char *CMD_DK = "dk";
const char *CMD_NS = "ns";
const char *CMD_LOTTERY = "lottery";

const char *CMD_BALANCE = "balance";          // 广发银行-- 余额宝++
const char *CMD_REBALANCE = "rebalance";      // 广发银行++ 余额宝--

const char *CMD_BACKUP = "bakup";

const char *CMD_TEST = "test";

const char *CMD_CANCEL = "cancel";
const char *CMD_SD = "sd";


/*--------------------  CODE_END @ 番茄  --------------------*/


