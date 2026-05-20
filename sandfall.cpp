// sandfall.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <utility>
#include <Windows.h>
#include <bit>
#include <bitset>
#include <typeinfo>
#include "basicslib.h"
#include "safepixel0,3.h"

void foo(vector<int> vec) {

    // Modifying vector inside function
    vec.push_back(8);
    for (auto i : vec) {
        cout << i << " ";
    }
    cout << endl;
}
bool issand(Pixel* a) {
    return a->getint('t') == 's';
}
bool isair(Pixel* a, Pixel* b) {
    return a->getint('t') == 'a';
}

int main()
{
    int col = 20;
    int row = 20;
    Pixel** arr = new Pixel * [col];
    for (int i = 0; i < col; i++) {
        arr[i] = new Pixel[row];
    }
    vector<funcexunit> a;
    funcarr tempwrite;
    a.push_back({tempwrite,issand});
    vector<pair<int, int>> updateset;//unused
    vector<updatee> changeset;
    checkfor(arr, col, row, updateset, a, changeset);
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
