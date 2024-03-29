#pragma once
#include "List.h"
#include <ostream>

template <class ch>
class Str
{
public:
    Str() {}

    Str(const ch* cstr)
    {
        Append(cstr); 
    }

    Str(const Str& string)
    {
        (*this) = string;
    }
    
    ~Str()
    {
        Clear();
    }

    Str& Append(const ch* cstr)
    {
        Data.Insert(Data.Size(), cstr, GetCSize(cstr));
        return *this;
    }

    Str& Append(const Str& string)
    {
        const ch* cstr = string.CStr();
        Data.Insert(Data.Size(), cstr, GetCSize(cstr));
        return *this;
    }

    Str SubStr(unsigned short index, unsigned short count) const
    {
        CHECK((index + count) < Length());
        List<ch> list(count);
        list.Insert(list.Size(), Data.RawData[index], count);
        return list;
    }

    Str Replace(const Str& old, const Str& replacement) const
    {
        return Str();
    }

    unsigned short Find(const Str& string) const
    {
        auto hlen = Length();
        const auto nlen = string.Length();
        unsigned short scan;
        unsigned short bad_char_skip[UCHAR_MAX + 1];
		
        if (nlen <= 0 || Empty() || string.Empty())
            return -1;
		
        for (scan = 0; scan <= UCHAR_MAX; scan = scan + 1) 
            bad_char_skip[scan] = nlen;

		unsigned short last = nlen - 1;
        for (scan = 0; scan < last; scan = scan + 1) 
            bad_char_skip[string.Data[scan]] = last - scan;

		unsigned short hOff = 0;
        while (hlen >= nlen)
        {
            for (scan = last; Data[scan + hOff] == string.Data[scan]; scan = scan - 1)
            {
                if (scan == 0)
                {
                    return hOff;
                }
            }
            hlen -= bad_char_skip[Data[last + hOff]];
            hOff += bad_char_skip[Data[last + hOff]];
        }
        return -1;
    }

    unsigned short Length() const
    {
        return Data.Size();
    }

    bool Empty() const
    {
        return Length() == 0;
    }

    void Clear()
    {
        Data.Clear();
    }

    const ch* CStr() const
    {
        return Data.RawData();
    }

    ch& operator[](const unsigned short index)
	{
		return Data[index];
	}

	const ch& operator[](const unsigned short index) const
	{
		return Data[index];
	}

    Str& operator=(const Str& string)
	{
		Data = string.Data;
		return *this;
	}

    bool operator==(const Str& string)
	{
		return Data == string.Data;
	}

    typename List<ch>::Iterator begin()
    {
        return Data.begin();
    }

    typename List<ch>::Iterator end()
    {
        return Data.end();
    }

    List<ch>& RawData()
    {
        return Data;
    }

    friend std::ostream& operator<<(std::ostream& os, const Str& str)
    {
        os << str.CStr();
        return os;
    }

private:
    unsigned short GetCSize(const ch* cstr)
    {
        unsigned short i = 0;
        while(cstr[i] != '\0')
        {
             CHECK(i < 1000);
             i++;
        }
        return i + 1;
    }

    List<ch, unsigned short> Data;
};

typedef Str<char> String;
typedef Str<wchar_t> WString;