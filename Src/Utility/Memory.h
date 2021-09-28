#pragma once
#include "Check.h"

namespace Memory
{
	template <class T>
	T* New() 
	{
		return new T();
	}

	template <class T>
	T* NewArr(size_t size) 
	{
		CHECK(size > 0 && "Invalid size");
		return new T[size];
	}

	template <class T>
	void Delete(T* object)
	{
		CHECK(object && "Invalid ptr");
		delete object;
	}

	template <class T>
	void DeleteArr(T* object)
	{
		CHECK(object && "Invalid ptr");
		delete[] object;
	}

	inline void Copy(void* dest, const void* src, size_t size)
	{
		CHECK(dest && "Invalid dest");
		CHECK(src && "Invalid src");
		CHECK(size > 0  && "Invalid size");
		memcpy(dest, src, size);
	}
}
