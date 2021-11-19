#include "pch.h"
#include "../Utility/Math/Matrix4x4.h"

int main() 
{

    Matrix4x4<float> matrix;

    matrix = Matrix4x4<float>::Transpose(matrix);
    matrix = Matrix4x4<float>::Inverse(matrix);
    matrix.Identity();

    return 0;
}