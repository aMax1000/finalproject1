#pragma once
#include <iostream>
#include <utility>
#include <Windows.h>
using namespace std;
template<typename T>
void dpr(T e, char t = ';') {
    cout << e << t;
}
template <typename T>
void resize(T*& arr, int oldsize, int size) {
    T* arr3 = new T[size];
    if(arr!=nullptr){
    for (int i = 0; i < oldsize; i++) {
        arr3[i] = arr[i];
    }
    delete[] arr;
    }
    arr = arr3;

}
void SetColor(int textColor, int bgColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,
        (bgColor << 4) | textColor);
}
template<typename T>
void print(T** arr, int col, int row) {
    for (int i = 0; col > i; i++) {
        for (int j = 0; row > j; j++) {
            std::cout << arr[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}
template <typename T, typename T2>
void print(vector<pair<T, T2>> a) {
    for (pair<T, T2> n : a) {
        cout << n.first << ';' << n.second << '\n';
    }
}
char extactchar(string a, int plase) {
    return a[plase];
}
