#pragma once
#include <assert.h>

#define Assert(cond, str) assert(cond && str) // cond = ����, str ���� 
 //ũ���ô� ������ ����
#define Crash()\
do   \
{   \
   ((void(*)())0)(); \
} while (false)

