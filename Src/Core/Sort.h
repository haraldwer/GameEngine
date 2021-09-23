#pragma once
#include "List.h"

class Sort
{
public:
    template<class T, class sT = unsigned short>
    static void Quick(List<T, sT>& list)
    {
        QuickSort_Impl<T, sT>(list, 0, list.Size() - 1);
    }

private:
    template <class T>
    static void Swap(T* a, T* b)
    {
        T t = *a;
        *a = *b;
        *b = t;
    }
    
    template <class T, class sT = unsigned short>
    static sT Partition (List<T, sT>& arr, sT low, sT high)
    {
        const T pivot = arr[high];
        sT i = (low - 1);
        for (sT j = low; j <= high- 1; j++)
        {
            if (arr[j] <= pivot)
            {
                i++;
                Swap(&arr[i], &arr[j]);
            }
        }
        Swap(&arr[i + 1], &arr[high]);
        return (i + 1);
    }

    template<class T, class sT = unsigned short>
    static void QuickSort_Impl(List<T, sT>& arr, sT low, sT high)
    {
        if (low < high)
        {
            sT pi = Partition(arr, low, high);
            QuickSort_Impl<T, sT>(arr, low, pi - 1);
            QuickSort_Impl<T, sT>(arr, pi + 1, high);
        }
    }
};