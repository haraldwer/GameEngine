#pragma once
#include "List.h"
#include "Hash.h"

template <class Key, class Value>
class Map
{
    struct Entry
    {
        uint32_t hash = 0;
        Key key;
        Value value;
    };

public:
    Map() {}
    Map(unsigned int startSize) : Data(startSize, true) {}

    Value& operator[](const Key& key)
	{
        return GetEntry(key).value;
	}

    const Value& At(const Key& key) const
	{
        const Entry* e = TryGetEntryConst(key);
        CHECK(e && "Invalid key");
        return e->value;
	}

    void Insert(const Key& key, const Value& value)
    {
        (*this)[key] = value;
    }

    void Remove(const Key& key)
    {
        Entry* e = TryGetEntry(key);
        CHECK(e && "Invalid key");
        e->hash = 0;
        e->value = Value();
    }

    void Clear()
    {
        Data.Clear();
    }

    class Iterator
	{
	public:
		Iterator(Entry* ptr) : dataItr(ptr) {  }
        Iterator(const typename List<Entry, unsigned short, true>::Iterator& itr) : dataItr(itr) 
        { 
            while(dataItr->hash == 0)
                dataItr++;
        }

		Iterator& operator++() 
		{
            do
                dataItr++;
            while(dataItr->hash == 0);
			return *this;
		}

		Iterator operator++(int) 
		{
			Iterator itr = *this;
			++(*this);
			return itr;
		}

		Iterator& operator--() 
		{
            do
                dataItr--;
            while(dataItr->hash == 0);
			return *this;
		}

		Iterator operator--(int) 
		{
			Iterator itr = *this;
			--(*this);
			return itr;
		}

		Entry& operator[](unsigned short index) 
        { 
            Iterator itr = *this;
            for(unsigned short i = 0; i < index; i++)
                itr++;
            return itr.dataItr.operator*();
        }
		Entry* operator->() { return dataItr.operator->(); }
		Entry& operator*() { return dataItr.operator*(); }
		bool operator==(const Iterator& other) { return dataItr == other.dataItr; }
		bool operator!=(const Iterator& other) { return !(dataItr == other.dataItr); }

	private:
		typename List<Entry, unsigned short, true>::Iterator dataItr;
	};

	Iterator begin()
    {
        return Iterator(Data.begin());
    }

    Iterator end()
    {
        return Iterator(Data.end());
    }

private:
    const Entry* TryGetEntryConst(const Key& key) const
    {
        const uint32_t hash = Hash(key);
        const unsigned short index = FindIndex(Data, hash);
        if(index == static_cast<unsigned short>(-1))
            return nullptr;
        const Entry& e = Data[index];
        if(e.hash == 0)
            return nullptr;
        return &e;
    }

    Entry* TryGetEntry(const Key& key)
    {
        const uint32_t hash = Hash(key);
        const unsigned short index = FindIndex(Data, hash);
        if(index == static_cast<unsigned short>(-1))
            return nullptr;
        Entry& e = Data[index];
        if(e.hash == 0)
            return nullptr;
        return &e;
    }

    Entry& GetEntry(const Key& key)
    {
        // Find index
        const uint32_t hash = Hash(key);
        const unsigned short index = FindIndex(Data, hash);
        if(index == static_cast<unsigned short>(-1)) // No index found
        {
            // Expand
            List<Entry, unsigned short, true> newData = List<Entry, unsigned short, true>(NewSize(), true);
            for(auto& it : Data)
            {
                const unsigned short newIndex = FindIndex(newData, it.hash);
                CHECK(newIndex >= 0 && newIndex < newData.Size() && "Index outside of range");
                newData[newIndex] = it;
            }
            Data = newData;

            // Create new at expanded index
            const unsigned short expandedIndex = FindIndex(Data, hash); 
            CHECK(expandedIndex >= 0 && expandedIndex < Data.Size() && "Index outside of range");
            Entry& e = Data[expandedIndex];
            e.hash = hash;
            e.key = key;
            return e;
        }

        CHECK(index >= 0 && index < Data.Size() && "Index outside of range");
        if(Data[index].hash == 0) // Index found but entry uninitialized
        {
            // Create new at index
            Entry& e = Data[index];
            e.hash = hash;
            e.key = key;
            return e;
        }

        // Return existing
        return Data[index];
    }

    unsigned short FindIndex(const List<Entry, unsigned short, true>& entries, uint32_t hash) const
    {
        const unsigned short size = entries.Size();
        if(size < 1)
            return -1;
        const unsigned short startIndex = hash % size;
        unsigned short index = startIndex;
        
        do
        {
            const Entry& e = entries[index];
            if(e.hash == 0 || e.hash == hash)
                return index;
            index++;
            if(index >= size)
                index = 0;
        }
        while(index != startIndex);

        return -1;
    }

    unsigned short NewSize() const
	{
        const unsigned short capacity = Data.Capacity();
		return MAX(capacity * 2, capacity + 1);
	}

    List<Entry, unsigned short, true> Data;
};