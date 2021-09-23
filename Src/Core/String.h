#include "List.h"

template <class ch = char>
class String
{
public:
    String();
    String(const ch* cstr)
    {
        Data.Clear();
        Append(cstr); 
    }

    String(const String& string)
    {
        (*this) = string;
    }
    
    String& Append(const ch* cstr)
    {
        Data.Insert(Data.Size(), cstr, GetCSize(cstr));
    }

    String& Append(const String& string)
    {
        const ch* cstr = string.CStr();
        Data.Insert(Data.Size(), cstr, cstr);
    }

    String SubStr(unsigned short index, unsigned short count) const
    {
        CHECK((index + count) < Length());
        List<ch> list(count);
        list.Insert(list.Size(), Data.RawData[index], count);
        return list;
    }

    String Replace(const String& old, const String& replacement) const
    {
        return String();
    }

    unsigned short Find(const String& string) const
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

    const ch* CStr()
    {
        return Data.RawData();
    }

    ch operator[](const unsigned short index)
	{
		return Data[index];
	}

	const ch& operator[](const unsigned short index) const
	{
		return Data[index];
	}

    String& operator=(const String& string)
	{
		Data = string.Data;
		return *this;
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

private:
    unsigned short GetCSize(const ch* cstr)
    {
        int i = 0;
        while(cstr[i] != '\0')
        {
             CHECK(i < 1000);
             i++;
        }
        return i;
    }

    List<ch> Data;
};