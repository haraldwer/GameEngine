#include "pch.h"
#include "../Core/List.h"
#include "../Core/Sort.h"
#include "../Core/String.h"
#include <iostream>

int main()
{
	String str = String("Hejsan");
	str.Append(" svejsan");
	//Sort::Quick(str.RawData());

	while(true)
	{
		PrintPCH();
	}
	return 0;
}