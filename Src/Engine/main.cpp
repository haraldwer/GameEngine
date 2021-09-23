#include "pch.h"
#include "../Core/List.h"
#include "../Core/Sort.h"
#include "../Core/String.h"
#include <iostream>

int main()
{
	List<int> list;
	list.Add(1);
	list.Add(2);
	list.Add(3);
	list.Add(4);
	list.Add(1);
	list.Add(2);
	list.Add(3);
	list.Add(4);
	list.Remove(3);
	
	Sort::Quick(list);

	String str = String("Hejsan");
	str.Append(" svejsan");
	//Sort::Quick(str.RawData());

	while(true)
	{
		for(auto& it : list)
		{
			std::cout << it << std::endl;	
		}	
		std::cout << str.CStr() << std::endl;
		for(auto& it : str)
		{
			std::cout << it << std::endl;
		}
	}
	return 0;
}