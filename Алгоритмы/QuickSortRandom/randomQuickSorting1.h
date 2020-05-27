#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

//void randomQuickSorting1(vector <int> &arr, int left, int right)
//{
//  int pivot; // разрешающий элемент
//  int l_hold = left; //левая граница
//  int r_hold = right; // правая граница
//  pivot = arr[left];
//  while (left < right) // пока границы не сомкнутся
//  {
//    while ((arr[right] >= pivot) && (left < right))
//      right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
//    if (left != right) // если границы не сомкнулись
//    {
//      arr[left] = arr[right]; // перемещаем элемент [right] на место разрешающего
//      left++; // сдвигаем левую границу вправо
//    }
//    while ((arr[left] <= pivot) && (left < right))
//      left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
//    if (left != right) // если границы не сомкнулись
//    {
//      arr[right] = arr[left]; // перемещаем элемент [left] на место [right]
//      right--; // сдвигаем правую границу вправо
//    }
//  }
//  arr[left] = pivot; // ставим разрешающий элемент на место
//  pivot = left;
//  left = l_hold;
//  right = r_hold;
//  if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
//    randomQuickSorting1(arr, left, pivot - 1);
//  if (right > pivot)
//    randomQuickSorting1(arr, pivot + 1, right);
//}

void randomQuickSorting1(vector <int> &arr, int first, int last)
{
    if (first < last)
    {
        int left = first, right = last, middle = arr[(left + right) / 2];
        do
        {
            while (arr[left] < middle) left++;
            while (arr[right] > middle) right--;
            if (left <= right)
            {
                int tmp = arr[left];
                arr[left] = arr[right];
                arr[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        randomQuickSorting1(arr, first, right);
        randomQuickSorting1(arr, left, last);
    }
}
