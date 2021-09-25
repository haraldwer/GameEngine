#pragma once
#include "List.h"

class Sort
{
public:
    template<class T, class sT = unsigned short>
    static void Quick(List<T, sT>& list)
    {
        if(list.Size() < 2)
            return;
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
    static int Partition (List<T, sT>& arr, int low, int high)
    {
        const T pivot = arr[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++)
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
    static void QuickSort_Impl(List<T, sT>& arr, int low, int high)
    {
        if (low < high)
        {
            int pi = Partition(arr, low, high);
            QuickSort_Impl<T, sT>(arr, low, pi - 1);
            QuickSort_Impl<T, sT>(arr, pi + 1, high);
        }
    }
};