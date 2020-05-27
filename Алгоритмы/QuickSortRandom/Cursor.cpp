#include <iostream>
#include <sstream>
#include "Cursor.h"

using namespace std;

cursor::cursor() :
    x(1), y(1), id(0) {};

cursor::cursor(int _x, int _y, int _id) :
    x(_x), y(_y), id(_id) {};

cursor::cursor(const cursor& other) :
    x(other.x), y(other.y), id(other.id) {};

ostream& operator<<(ostream& out, const cursor& c){
    out << "[" << c.x << ", " << c.y << "], " << c.id;
    return out;
}

istream& operator>>(istream& in, cursor& c){
    in >> c.x >> c.y >> c.id;
    return in;
}

void cursor :: set_x(int _x){
    x = _x;
}

void cursor :: set_y(int _y){
    y = _y;
}

void cursor :: set_id(int _id){
    id = _id;
}

bool cursor :: operator>(const cursor& c){
    return c.id > id;
}

bool cursor :: operator<(const cursor& c){
    return c.id < id;
}

bool cursor :: operator!=(const cursor& c){
    return c.id != id;
}

bool cursor :: operator>=(const cursor& c){
    return c.id >= id;
}

bool cursor :: operator<=(const cursor& c){
    return c.id <= id;
}

bool cursor :: operator==(const cursor& c){
    return c.id == id;
}

string cursor::toString() const {
    ostringstream oss;
    oss << "Cursor with coordinates x = " << x << " and y = " << y << "; Id: " << id;
    string s = oss.str();
    return s;
}
