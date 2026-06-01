// sandfall.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <utility>
#include <Windows.h>
#include <bit>
#include <bitset>
#include <typeinfo>
#include <chrono>
#include <array>
#include <stack>
#include "basicslib.h"
#include "safepixel0,3.h"

bool isair(Pixel*** a, int COL, int ROW, int ay, int ax) {
    return (a[ay][ax])->getint('t') == 'a';
}
bool issand(Pixel*** a, int COL, int ROW, int ay, int ax) {
    return (a[ay][ax])->getint('t') == 's';
}
void printboard(Pixel*** arr, int COL, int ROW) {
    for (int i = 0; COL > i; i++) {
        for (int j = 0; ROW > j; j++) {
            std::cout << static_cast<char>((arr[i][j]->getint('t'))) << ' ';
        }
        std::cout << std::endl;
    }
}

//class customstr {
//private:
//    int* arr=nullptr;
//public:
//    //ДЕСТРУКТОР РАБОТАЕТ 2 РАЗА ЕСЛИ ОБЬЕКТ В ВЕКТОРЕ
//    //~customstr() {
//    //    delete[] arr;
//    //}
//    customstr() {
//        arr= new int[5] { 1, 2, 3, 4, 5 };
//    }
//
//    int getvalue(int i) {
//        if (i < 5) {
//            return arr[i];
//        }
//    }
//};
//void testfun2(customstr& a) {
//    for (int i = 0; i < 5; i++) {
//        cout << a.getvalue(i);
//    }
//    cout << endl;
//}
//
//void testfun(vector<customstr>& a) {
//    for (customstr i:a) {
//        testfun2(i);
//    }
//}

constexpr auto COL = 1000;
constexpr auto ROW = 1000;

int main()
{
    //vector<customstr> intarr;
    //customstr abbb;
    //for (int i = 0; i < 5; i++) {
    //    intarr.push_back(abbb);
    //}
    //testfun(intarr);
    auto before = chrono::high_resolution_clock::now();
    auto before1 = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    Pixel*** arr = new Pixel ** [COL];
    for (int i = 0; i < COL; i++) {
        arr[i] = new Pixel*[ROW];
    }
    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < ROW; j++) {
            Air air;
            arr[i][j] = new Air;    
        }
    }
    for (int i = 0; i < COL;i++) {
        Sand sand;
        arr[0][i] = new Sand;
    }
    //stack
    //array<Pixel**,COL> arr1;
    //for (int i = 0; i < COL; i++) {
    //    array<Pixel*, ROW> a;
    //    arr1[i]=a;
    //}
    //Pixel*** arr = *&arr1;
    //Air air[COL][ROW] = {};
    //for (int i = 0; i < COL; i++) {
    //    for (int j = 0; j < ROW; j++) {
    //        arr[i][j] = air[i]+j;    
    //    }
    //}

    //for (int i = 0; i < COL; i++) {
    //    Sand sand;
    //    arr[2][i] = &sand;
    //}
    //for (int i = 0; i < COL; i++) {
    //    Sand sand;
    //    arr[4][i] = &sand;
    //}
    //for (int i = 0; i < COL; i++) {
    //    Sand sand;
    //    arr[6][i] = &sand;

    //}
    //for (int i = 0; i < COL; i++) {
    //    Sand sand;
    //    arr[8][i] = &sand;
    //}
    //for (int i = 0; i < COL; i++) {
    //    Sand sand;
    //    arr[10][i] = &sand;
    //}
    
    vector<funcexunit> a;
    vector<funcexunit> b;
    funcexunit t;
    int gg = 0;
    funcarr tempwrite;
    tempwrite.addell(gravity, 1, 0, true, isair);
    tempwrite.addell(returngravity, 0, 0, true, isair2);
    //tempwrite.addell(gravity, 1, 1, true, isairdiag);
    //tempwrite.addell(gravity, 1, -1, true, isairdiag2);
    t.addell(tempwrite, issand);
    a.push_back(t);
    b.push_back(t);
    vector<pair<int, int>> updateset;//unused
    vector<updatee> changeset;
    int i = 0;
    cout << sizeof(arr[0][0])<<endl;
    cout << sizeof(*arr[0][0]) << endl;
    before = chrono::high_resolution_clock::now();;
    while (!gg) {
        
        //cout<<a[0].func.x(0)<<endl;
        before1 = chrono::high_resolution_clock::now();;
        checkfor(arr, COL, ROW, updateset, a, changeset);
        end = chrono::high_resolution_clock::now();;
        //cout << "checkfor time:" << chrono::duration_cast<chrono::microseconds>(end - before1).count() << endl;
        //printboard(arr, COL, ROW);
        //cout << changeset[0].typeoffunc<<endl;
        //cin >> gg;
        //cout << "a3: " << static_cast<int>((*(Changei*)changeset[0].a).path) << endl;
        before1 = chrono::high_resolution_clock::now();;
        applychangeset(arr, COL, ROW, changeset);
        end = chrono::high_resolution_clock::now();
        //cout << "apply time:" << chrono::duration_cast<chrono::microseconds>(end - before1).count() << endl;
        //cout << a[0].func.x(0) << endl;
        //cout<<updateset.size();
        updateset.clear();
        //if (log2(i) == floor(log2(i))) {
        //    cout << i <<'\n';
        //}
        if (i == 32) {
            end = chrono::high_resolution_clock::now();
            cout << "time:" << chrono::duration_cast<chrono::microseconds>(end - before).count() << endl;
        }
        i++;
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
