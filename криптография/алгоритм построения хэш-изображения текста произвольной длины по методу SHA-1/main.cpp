#include <iostream>
#include "sha1.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
     int a;
     string sf;
     ifstream inf;

    inf.open ( "/Users/Mac/Desktop/XCode/5.1(kryptography)/5.1(kryptography)/input.txt" );
    getline ( inf, sf, '\0' );

    ofstream strm("/Users/Mac/Desktop/XCode/5.1(kryptography)/5.1(kryptography)/res.txt");

    strm <<sha1(sf);

    inf.close();


      return 0;
}
