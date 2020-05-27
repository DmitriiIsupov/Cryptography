#ifndef CURSOR
#define CURSOR
#include <string>
#include <iostream>

using namespace std;

class cursor {
public:
    int x, y, id;
    cursor();
    cursor(int, int, int);
    cursor(const cursor&);

    friend ostream& operator<<(ostream&, const cursor&);
    friend istream& operator>>(istream&, cursor&);

    void set_x(int);
    void set_y(int);
    void set_id(int);
    bool operator>(const cursor&);
    bool operator<(const cursor&);
    bool operator!=(const cursor&);
    bool operator>=(const cursor&);
    bool operator<=(const cursor&);
    bool operator==(const cursor&);
    string toString() const;
};

#endif

