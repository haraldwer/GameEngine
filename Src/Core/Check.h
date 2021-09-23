#pragma once
#include "Log.h"

#ifdef DEBUG
#define CHECK(condition) 						\
if(!(condition))								\
{												\
	LOG("CHECK: ", (#condition));		\
	abort();										\
}
#else
#define CHECK(condition) do { (void)sizeof(condition); } while(0);
#endif
