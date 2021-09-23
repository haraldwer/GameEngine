#include "pch.h"

void PrintPCH()
{
    #ifdef DBUILD_PCH
    std::cout << "PCH header" << std::endl;
    #else
    std::cout << "Not PCH header" << std::endl;
    #endif
}