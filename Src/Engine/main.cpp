#include "pch.h"
#include "Core/Map.h"
#include "Core/String.h"

int main()
{
	Map<String<char>, int> map; 
	map["String"] = 10;
	return 0;
}