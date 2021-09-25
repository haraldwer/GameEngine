#include "String.h"
#include <cstdint>

template<class T>
uint32_t Hash(const String<T>& aKey)
{
    const uint8_t* aBuffer = reinterpret_cast<const uint8_t*>(aKey.CStr());
    const int count = aKey.Length();

    const uint32_t FNVOffsetBasis = 2166136261U;
    const uint32_t FNVPrime = 16777619U;
    uint32_t val = FNVOffsetBasis;
    for (int i = 0; i < count; i++)
    {
        val ^= aBuffer[i];
        val *= FNVPrime;
    }
    return val;
}

template <class T>
uint32_t Hash(const T& aKey)
{
    const uint8_t* aBuffer = reinterpret_cast<const uint8_t*>(&aKey);
    const int count = sizeof(T); 
    
    const uint32_t FNVOffsetBasis = 2166136261U;
    const uint32_t FNVPrime = 16777619U;
    uint32_t val = FNVOffsetBasis;
    for(int i = 0; i < count; i++)
    {
        val ^= aBuffer[i];
        val *= FNVPrime;
    }
    return val;
}