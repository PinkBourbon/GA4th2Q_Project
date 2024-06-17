#pragma once
#include <assert.h>

#define Assert(cond, str) assert(cond && str) // cond = 상태, str 문자 
 //크래시는 무조건 죽음
#define Crash()\
do   \
{   \
   ((void(*)())0)(); \
} while (false)

