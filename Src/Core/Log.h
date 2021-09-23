#pragma once
#include <iostream>

#define LOG(...) LOG_INTERNAL(__VA_ARGS__, " File:", __FILE__, " Line:", __LINE__, " Function:", __FUNCTION__, "\n");
#define LOG_INTERNAL(...) Log(__VA_ARGS__);

template<typename ...Args>
void Log(Args && ...args)
{
    (std::cout << ... << args);
}
