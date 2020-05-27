#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <time.h>
#include "randomQuickSorting1.h"
#include "randomQuickSorting2.h"
#include "randomQuickSorting3.h"
#include "randomQuickSorting4.h"
#include "Cursor.h"

void rand (vector <int> &arr, int n) {
    generate_n (back_inserter (arr), n,
                [] {return rand() % 1000 + 1;});
}

void random (vector <cursor> &arr, int n) {
    arr.resize(n);
    for (int i = 0; i < n; i++)
    {
        int x = rand() % 2000 + 1000;
        int y = rand() % 1000 + 1000;
        int id = rand() % 1000 + 1;

        arr[i].set_x(x);
        arr[i].set_y(y);
        arr[i].set_id(id);
    }
}
using namespace std;

int main()
{
    int stime;
    stime = time(NULL);
    srand(stime);

    vector <int> arr1;
    rand(arr1,20);
    randomQuickSorting1(arr1,0,19);
    copy(arr1.begin(), arr1.end(),ostream_iterator <int>(cout, " "));
    cout << "\n\n";

    vector <cursor> arr2;
    random(arr2, 20);
    randomQuickSorting2(arr2,0,19);
    copy(arr2.begin(), arr2.end(),ostream_iterator <cursor>(cout, "\n"));
    cout << "\n\n";

    vector <cursor> arr3;
    random(arr3,20);
    randomQuickSorting3(arr3.begin(), arr3.end());
    copy(arr3.begin(), arr3.end(),ostream_iterator <cursor>(cout, "\n"));
    cout << "\n\n";

    vector <cursor> arr4;
    random(arr4,20);
    randomQuickSorting4(arr4.begin(), arr4.end(), comp);
    copy(arr4.begin(), arr4.end(),ostream_iterator <cursor>(cout, "\n"));
    cout << "\n\n";
    return 0;
}
