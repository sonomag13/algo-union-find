#pragma once

#include <iostream>

using namespace std;

void printArray(int * arrc, int n) {
    for (int i = 0; i < n; ++i) {
        cout <<  "\t" << i << ": " << *(arrc + i) << endl;
    }
}