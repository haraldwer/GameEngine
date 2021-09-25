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
    Map() : Entries(10, true) {}
    Map(unsigned int startSize) : Entries(startSize, true) {}

    Value& operator[](const Key& key)
	{
        return GetEntry(key).value;
	}

    void Insert(const Key& key, const Value& value)
    {
        (*this)[key] = value;
    }

    void Remove(const Key& key)
    {
        GetEntry(key).hash = 0;
    }

    void Clear()
    {
        Entries.Clear();
    }

private:
    Entry& GetEntry(const Key& key)
    {
        // Find index
        const uint32_t hash = Hash(key);
        const unsigned short index = FindIndex(Entries, hash);
        if(index == static_cast<unsigned short>(-1)) // No index found
        {
            // Expand
            if(Entries.Size() == Entries.Capacity())
            {
                // Rehash existing items
                List<Entry> newEntries = List<Entry>(Entries.Capacity() * 2, true);
                for(auto& it : Entries)
                {
                    unsigned short newIndex = FindIndex(newEntries, it.hash);
                    CHECK(newIndex >= 0 && newIndex < newEntries.Size() && "Index outside of range");
                    newEntries[newIndex] = it;
                }
                Entries = newEntries;
            }

            // Create new at expanded index
            unsigned short expandedIndex = FindIndex(Entries, hash); 
            CHECK(expandedIndex >= 0 && expandedIndex < Entries.Size() && "Index outside of range");
            Entry& e = Entries[expandedIndex];
            e.hash = hash;
            e.key = key;
            return e.value;
        }
        else if(Entries[index].hash == 0) // Index found but entry uninitialized
        {
            // Create new at index
            CHECK(index >= 0 && index < Entries.Size() && "Index outside of range");
            Entry& e = Entries[index];
            e.hash = hash;
            e.key = key;
            return e.value;
        }

        // Return existing
        CHECK(index >= 0 && index < Entries.Size() && "Index outside of range");
        return Entries[index].value;
    }

    unsigned short FindIndex(const List<Entry>& entries, uint32_t hash)
    {
        const unsigned short startIndex = hash % entries.Capacity();
        unsigned short index = startIndex;
        unsigned short size = entries.Size();
        while(true)
        {
            const Entry& e = entries[index];
            if(e.hash == 0 || e.hash == hash)
                return index;
            
            index++;
            if(index == startIndex)
                return -1;
            if(index >= size)
                index = 0;
        }
        return -1;
    }

    List<Entry> Entries;
};