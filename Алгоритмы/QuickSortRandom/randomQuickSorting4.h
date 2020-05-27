#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include "Cursor.h"

bool comp (cursor &higher, cursor &lower)
{
    return lower <= higher;
}

template<class RandomIterator, class Compare>
RandomIterator partition_index(RandomIterator low, RandomIterator high, Compare comp){
    typename iterator_traits<RandomIterator> :: value_type pivot = *high;
    RandomIterator i = prev(low);
    for (RandomIterator j = low; j != high; advance(j, 1)){
        if (comp(*j, pivot)){
            advance(i, 1);
            iter_swap(i, j);
        }
    }
    iter_swap(next(i), high);
    return next(i);
}
template<class RandomIterator, class Compare>
void randomQuickSorting4(RandomIterator low, RandomIterator high, Compare comp){
    if (distance(low, high) > 0)
    {
        RandomIterator pi = partition_index(low, high, comp);
        randomQuickSorting4(low, prev(pi), comp);
        randomQuickSorting4(next(pi), high, comp);
    }
}
