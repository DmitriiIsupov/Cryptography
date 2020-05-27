#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
using namespace std;

//template <class RandomIterator>

//void randomQuickSorting3(RandomIterator begin, RandomIterator end)
//{
//  auto left = begin;
//  auto right = end;
//  auto pivot = begin; // разрешающий элемент
//  auto l_hold = begin; //левая граница
//  auto r_hold = end; // правая граница
//  *pivot = *left;
//  while (left < right) // пока границы не сомкнутся
//  {
//    while ((*right >= *pivot) && (left < right))
//      right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
//    if (left != right) // если границы не сомкнулись
//    {
//      *left = *right; // перемещаем элемент [right] на место разрешающего
//      left++; // сдвигаем левую границу вправо
//    }
//    while ((*left <= *pivot) && (left < right))
//      l_hold++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
//    if (left != right) // если границы не сомкнулись
//    {
//      *right = *left; // перемещаем элемент [left] на место [right]
//      right--; // сдвигаем правую границу вправо
//    }
//  }
//  *left = *pivot; // ставим разрешающий элемент на место
//  *(pivot) = *left;
//  *left = *l_hold;
//  *right = *r_hold;
//  if (*left < *(pivot)) // Рекурсивно вызываем сортировку для левой и правой части массива
//    randomQuickSorting3(left, (pivot) - 1);
//  if (*right > *(pivot))
//    randomQuickSorting3((pivot) + 1, right);
//}

//void randomQuickSorting3(RandomIterator begin, RandomIterator end)
//{
//    auto first = begin;
//    auto middle = begin;
//    auto last = prev(end);
//    if (first < last)
//    {
////        cout << *first <<  endl;
////        cout << *last <<  endl;
//        auto left = first;
//        auto right = last;
//        int dist = (distance(left,right))/2;
////        cout << dist <<  endl;
////        cout << *left <<  endl;
////        cout << *right <<  endl;
//        advance(middle,dist);
////        cout << *middle <<  endl;
//        do
//        {
//            while (*(left) < *(middle)){
//            left++;
//            }
//            while (*(right) > *(middle)){
//            right--;
//            }
//            if (left <= right)
//            {
//                iter_swap(right,left);
//                left++;
//                right--;
//            }
//        } while (left <= right);
//        randomQuickSorting3(first, right);
//        randomQuickSorting3(left, last);
//    }
//}


template<class RandomIterator>
RandomIterator partition_index(RandomIterator low, RandomIterator high){
    typename iterator_traits<RandomIterator> :: value_type pivot = *high;
    RandomIterator i = prev(low);
    for (RandomIterator j = low; j != high; advance(j, 1)){
        if (pivot <= *j){
            advance(i, 1);
            iter_swap(i, j);
        }
    }
    iter_swap(next(i), high);
    return next(i);
}
template<class RandomIterator>
void randomQuickSorting3(RandomIterator low, RandomIterator high){
    if (distance(low, high) > 0)
    {
        RandomIterator pi = partition_index(low, high);
        randomQuickSorting3(low, prev(pi));
        randomQuickSorting3(next(pi), high);
    }
}

