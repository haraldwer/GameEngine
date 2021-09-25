#pragma once
#include "Memory.h"
#include "Math.h"

template <class T, class sT = unsigned short>
class List
{
public:

	// Constructors

	List() 
	{ 

	}

	List(sT startSize, bool fill = false) 
	{ 
		Data = Memory::NewArr<T>(startSize); 
		ContainerSize = startSize; 
		if(fill)
			Fill();
	}

	List(const List& list) 
	{ 
		Copy(list); 
	}

	~List() 
	{ 
		Clear(); 
	}

	// Operators 

	List& operator=(const List& list)
	{
		Copy(list);
		return *this;
	}

	T& operator[](const sT index)
	{
		CHECK(index >= 0 && index < Count && "Index outside of range");
		return Data[index];
	}

	const T& operator[](const sT index) const
	{
		CHECK(index >= 0 && index < Count && "Index outside of range");
		return Data[index];
	}

	// Functions

	void Add(const T& object)
	{
		Insert(Count, object);
	}

	void Insert(const sT index, const T& object)
	{
		Insert(index, &object, 1);
	}

	// Insert multiple elements 
	void Insert(const sT index, const T* object, const sT count)
	{
		CHECK(index >= 0 && index <= Count && "Index outside of range");
		
		T* target = Data;
		if(Count + count > ContainerSize)
		{
			// Resize
			const sT newSize = MAX((Count + count), NewSize());
			target = Memory::NewArr<T>(newSize); 
			ContainerSize = newSize;

			// Copy data below index
			if(Data)
				Memory::Copy(target, Data, sizeof(T) * index);
		}

		if(index < Count)
		{
			// Copy data above index
			const size_t n = ((Count - count + 1) - index);
			Memory::Copy(&target[index + count], &Data[index], sizeof(T) * n);
		}

		Memory::Copy(&target[index], object, sizeof(T) * count);
		Count += count;

		if(target != Data)
			Data = target;
	}

	void Remove(const sT index)
	{
		CHECK(index >= 0 && index < Count && "Index outside of range");
		Count--;
		// copy from index + 1 to last,
		const size_t n = Count - index;
		if(n <= 0)
			return;
		Memory::Copy(&Data[index], &Data[index + 1], sizeof(T) * n);
	}

	void Clear()
	{
		if(Data)
		{
			Memory::DeleteArr(Data);
			Data = nullptr;
		}
		Count = 0;
		ContainerSize = 0;
	}

	void Resize(sT newSize)
	{
		CHECK(newSize > Count)
		if(Data)
		{
			Memory::DeleteArr(Data);
			Data = nullptr;
		}
		T* newArr = Memory::NewArr<T>(newSize);
		Memory::Copy(newArr, Data, sizeof(T) * Count);
		ContainerSize = newSize;
	}

	sT Size() const 
	{
		return Count;
	}

	sT Capacity() const 
	{
		return ContainerSize;
	}

	void Fill()
	{
		for(sT i = Count; i < ContainerSize;i++)
			Data[i] = T();
		Count = ContainerSize;
	}

	T* RawData()
	{
		return Data;
	}

	const T* RawData() const
	{
		return Data;
	}

	sT FindFirst(const T& object) const
	{
		for(sT i = 0; i < Count; i++)
			if(Data[i] == object)
				return i;
		return -1; 
	}

	sT FindLast(const T& object) const
	{
		for(sT i = Count - 1; i >= 0; i--)
			if(Data[i] == object)
				return i;
		return -1; 
	}

	List<sT> FindAll(const T& object) const
	{
		List<sT> list;
		for(sT i = 0; i < Count; i++)
			if(Data[i] == object)
				list.Add(i);
		return list;
	}

	// Iterator

	class Iterator
	{
	public:
		Iterator(T* ptr) : Ptr(ptr) {  }
		Iterator& operator++() 
		{
			Ptr++;
			return *this;
		}

		Iterator& operator++(int) 
		{
			Iterator itr = *this;
			++(*this);
			return itr;
		}

		Iterator& operator--() 
		{
			Ptr--;
			return *this;
		}

		Iterator& operator--(int) 
		{
			Iterator itr = *this;
			--(*this);
			return itr;
		}

		T& operator[](sT index) { return *(Ptr + index); }
		T* operator->() { return Ptr; }
		T& operator*() { return *Ptr; }
		bool operator==(const Iterator& other) { return Ptr == other.Ptr; }
		bool operator!=(const Iterator& other) { return !((*this) == other); }

	private:
		T* Ptr = nullptr;
	};

	Iterator begin()
	{
		return Iterator(Data);
	}

	Iterator end()
	{
		return Iterator(Data + Count);
	}

private:
	void Copy(const List& list)
	{
		Clear();
		if(!list.Data)
			return;
		(*this) = List(list.ContainerSize);
		Memory::Copy(Data, list.Data, sizeof(T) * list.Count);
	}

	sT NewSize() const
	{
		return (Count + (Count / 2));
	}

	T* Data = nullptr;
	sT Count = 0;
	sT ContainerSize = 0;
};