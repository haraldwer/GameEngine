#include "pch.h"

void Func()
{
    #ifdef BUILD_PCH
    std::cout << "pch" << std::endl;
    #else
    std::cout << "not pch" << std::endl;
    #endif
}