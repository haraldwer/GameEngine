#pragma once
#include "Vector4.h"

template<class T>
class Matrix4x4
{
public:
    union
    {
        T elements[4][4];
        T data[16];

        struct
        {
            Vector4<T> right;
            Vector4<T> up;
            Vector4<T> forward;
            Vector4<T> translation;
        };
    };

    Matrix4x4()
    {
        Identity();
    }
    
    Matrix4x4(const Matrix4x4& matrix)
    {
        memcpy(data, matrix.data, sizeof(T) * 16);
    }

    T& operator()(const int row, const int column)
    {
        return elements[row][column];
    }

    const T& operator()(const int row, const int column) const
    {
        return elements[row][column];
    }

    T& operator()(const int index)
    {
        return data[index];
    }

    const T& operator()(const int index) const
    {
        return data[index];
    }

    void Identity()
    {
        elements[0][0] = 1.f;
        elements[0][1] = 0.0f;
        elements[0][2] = 0.f;
        elements[0][3] = 0.0f;

        elements[1][0] = 0.0f;
        elements[1][1] = 1.0;
        elements[1][2] = 0.0;
        elements[1][3] = 0.0f;

        elements[2][0] = 0.f;
        elements[2][1] = 0.0;
        elements[2][2] = 1.f;
        elements[2][3] = 0.0f;

        elements[3][0] = 0.0f;
        elements[3][1] = 0.0f;
        elements[3][2] = 0.0f;
        elements[3][3] = 1.0f;
    }

    static Matrix4x4 Transpose(const Matrix4x4& matrix)
    {
        Matrix4x4 m;
        for (unsigned int row = 0; row < 4; ++row)
        {
            for (unsigned int column = 0; column < 4; ++column)
            {
                m.elements[row][column] = matrix.elements[column][row];
            }
        }
        return m;
    }

    static Matrix4x4 Inverse(const Matrix4x4& matrix)
    {
        const T* const m = matrix.data;
        Matrix4x4 invMat;
        T* inv = invMat.data;
        T det;

        inv[0] = 
            m[5] * m[10] * m[15] -
            m[5] * m[11] * m[14] -
            m[9] * m[6] * m[15] +
            m[9] * m[7] * m[14] +
            m[13] * m[6] * m[11] -
            m[13] * m[7] * m[10];

        inv[4] = 
            -m[4] * m[10] * m[15] +
            m[4] * m[11] * m[14] +
            m[8] * m[6] * m[15] -
            m[8] * m[7] * m[14] -
            m[12] * m[6] * m[11] +
            m[12] * m[7] * m[10];

        inv[8] = 
            m[4] * m[9] * m[15] -
            m[4] * m[11] * m[13] -
            m[8] * m[5] * m[15] +
            m[8] * m[7] * m[13] +
            m[12] * m[5] * m[11] -
            m[12] * m[7] * m[9];

        inv[12] = 
            -m[4] * m[9] * m[14] +
            m[4] * m[10] * m[13] +
            m[8] * m[5] * m[14] -
            m[8] * m[6] * m[13] -
            m[12] * m[5] * m[10] +
            m[12] * m[6] * m[9];

        inv[1] = 
            -m[1] * m[10] * m[15] +
            m[1] * m[11] * m[14] +
            m[9] * m[2] * m[15] -
            m[9] * m[3] * m[14] -
            m[13] * m[2] * m[11] +
            m[13] * m[3] * m[10];

        inv[5] = 
            m[0] * m[10] * m[15] -
            m[0] * m[11] * m[14] -
            m[8] * m[2] * m[15] +
            m[8] * m[3] * m[14] +
            m[12] * m[2] * m[11] -
            m[12] * m[3] * m[10];

        inv[9] = 
            -m[0] * m[9] * m[15] +
            m[0] * m[11] * m[13] +
            m[8] * m[1] * m[15] -
            m[8] * m[3] * m[13] -
            m[12] * m[1] * m[11] +
            m[12] * m[3] * m[9];

        inv[13] = 
            m[0] * m[9] * m[14] -
            m[0] * m[10] * m[13] -
            m[8] * m[1] * m[14] +
            m[8] * m[2] * m[13] +
            m[12] * m[1] * m[10] -
            m[12] * m[2] * m[9];

        inv[2] = 
            m[1] * m[6] * m[15] -
            m[1] * m[7] * m[14] -
            m[5] * m[2] * m[15] +
            m[5] * m[3] * m[14] +
            m[13] * m[2] * m[7] -
            m[13] * m[3] * m[6];

        inv[6] = 
            -m[0] * m[6] * m[15] +
            m[0] * m[7] * m[14] +
            m[4] * m[2] * m[15] -
            m[4] * m[3] * m[14] -
            m[12] * m[2] * m[7] +
            m[12] * m[3] * m[6];

        inv[10] = 
            m[0] * m[5] * m[15] -
            m[0] * m[7] * m[13] -
            m[4] * m[1] * m[15] +
            m[4] * m[3] * m[13] +
            m[12] * m[1] * m[7] -
            m[12] * m[3] * m[5];

        inv[14] = 
            -m[0] * m[5] * m[14] +
            m[0] * m[6] * m[13] +
            m[4] * m[1] * m[14] -
            m[4] * m[2] * m[13] -
            m[12] * m[1] * m[6] +
            m[12] * m[2] * m[5];

        inv[3] = 
            -m[1] * m[6] * m[11] +
            m[1] * m[7] * m[10] +
            m[5] * m[2] * m[11] -
            m[5] * m[3] * m[10] -
            m[9] * m[2] * m[7] +
            m[9] * m[3] * m[6];

        inv[7] = 
            m[0] * m[6] * m[11] -
            m[0] * m[7] * m[10] -
            m[4] * m[2] * m[11] +
            m[4] * m[3] * m[10] +
            m[8] * m[2] * m[7] -
            m[8] * m[3] * m[6];

        inv[11] = 
            -m[0] * m[5] * m[11] +
            m[0] * m[7] * m[9] +
            m[4] * m[1] * m[11] -
            m[4] * m[3] * m[9] -
            m[8] * m[1] * m[7] +
            m[8] * m[3] * m[5];

        inv[15] = 
            m[0] * m[5] * m[10] -
            m[0] * m[6] * m[9] -
            m[4] * m[1] * m[10] +
            m[4] * m[2] * m[9] +
            m[8] * m[1] * m[6] -
            m[8] * m[2] * m[5];

        det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

        if (det == 0)
        {
            return Matrix4x4();
        }

        det = 1.0 / det;

        for(int i = 0; i < 16; i++)
        {
            inv[i] *= det;
        }
        
        return invMat;
    }
};