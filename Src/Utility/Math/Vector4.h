#pragma once

#include "Sqrt.h"
#include "../Memory.h"

template<class T>
class Vector4
{
    union
    {
        T data[4];
        struct
        {
            union
            {
                T x;
                T r;
            };

            union
            {
                T y;
                T g;
            };

            union
            {
                T z;
                T b;
            };

            union
            {
                T w;
                T a;
            };
        };
         
    };

    Vector4()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }

    Vector4(const Vector4& other)
    {
        (*this) = other;
    }

    Vector4(const T value)
    {
        x = value;
        y = value;
        z = value;
        w = value;
    }

    T& operator[](int index)
    {
        return data[index];
    }

    const T& operator[](int index) const
    {
        return data[index];
    }
    
    Vector4& operator=(const Vector4& other)
    {
        Memory::Copy(data, other.data, sizeof(T) * 4);
        return (*this);
    }

    Vector4& operator+(const Vector4& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
    }

    Vector4& operator*(const T scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
    }

    T Size()
    {
        return Sqrt(SizeSqr());
    }

    T SizeSqr()
    {
        return x * x + y * y + z * z + w * w;
    }
};