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

bool issand(Pixel** a, int col, int row, int x, int y) {
    return (a[x][y]).getint('t') == 's';
}
bool isair(Pixel** a,int col,int row,int x,int y) {
    return (a[x][y]).getint('t') == 'a';
}
bool isairdiag(Pixel** a, int col, int row, int x, int y) {
    return (*getvalue(a,col,row,x-1,y)).getint('t') != 'a' and (a[x][y]).getint('t') == 'a';
}
bool isairdiag2(Pixel** a, int col, int row, int x, int y) {
    return (*getvalue(a, col, row, x + 1, y)).getint('t') != 'a'
        and (*getvalue(a, col, row, x + 2, y)).getint('t') != 'a'
        and (a[x][y]).getint('t') == 'a';
}
Changei gravity(Pixel* a, Pixel* b) {
    Changei c;
    c.path = 't';
    c.value = 's';
    return c;
};
Changei returngravity(Pixel* a, Pixel* b) {
    Changei c;
    c.path = 't';
    c.value='a';
    return c;
};
void printboard(Pixel** arr, int col, int row) {
    for (int i = 0; col > i; i++) {
        for (int j = 0; row > j; j++) {
            std::cout << static_cast<char>((arr[i][j]).getint('t')) << ' ';
        }
        std::cout << std::endl;
    }
}

int main()
{
    //Air b;
    //Pixel* a = &b;
    //cout << b.getint('t');
    int col = 2;
    int row = 2;
    Air asss;
    Sand sand;
    Pixel** arr = new Pixel * [col];
    for (int i = 0; i < col; i++) {
        arr[i] = new Pixel[row];
    }
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            arr[i][j] = asss;
        }
    }
    arr[0][1] = sand;
    //cout<< (*(arr[0][9])).getint('t');
    vector<funcexunit> a;
    vector<funcexunit> b;
    funcexunit t;
    int gg=0;
    funcarr tempwrite;
    tempwrite.addell(gravity,1,0,true, isair);
    //tempwrite.addell(gravity, 1, 1, true, isairdiag);
    //tempwrite.addell(gravity, 1, -1, true, isairdiag2);
    t.addell(tempwrite, issand);
    a.push_back(t);
    b.push_back(t);
    vector<pair<int, int>> updateset;//unused
    vector<updatee> changeset;
    while(!gg){
    checkfor(arr, col, row, updateset, a, changeset);
    printboard(arr, col, row);
    cin >> gg;
    }
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
   
