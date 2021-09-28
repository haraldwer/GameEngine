#pragma once
#include <windows.h>

#define DLL_FUNC(func) 					\
extern "C" 											\
{													\
	void __declspec(dllexport) func();	\
}

typedef void (__cdecl *DLLFunc_Void)();

class DLLFunc()
{
public:

	DLLFunc(const str& dllName, const str& funcName)
	{
		HINSTANCE dllID = LoadLibrary(dllName);

		if (!dllID) 
		{
			LOG("Could not load the dynamic library");
			return;
		}

		// resolve function address here
		DLLFunc_Void func = (DLLFunc_Void)GetProcAddress(dllID, funcName);
		if (!func) 
		{
			LOG("Could not locate the function");
			return;
		}
	}

	~DLLFunc()
	{
		// Unload
	}

	void Func()
	{
		func();
	}

private:
	HINSTANCE dllID = NULL;
	DLLFunc_Void func = nullptr;

}