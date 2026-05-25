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

bool isair2(Pixel*** a, int col, int row, int ay, int ax) {
    return getvalue(a, col, row, ay + 1, ax)->getint('t') == 'a'
        ;
    //or (*getvalue(a, col, row, y+1, x - 1)).getint('t')=='a'
    //or (*getvalue(a, col, row, y + 1, x + 1)).getint('t') == 'a'
}
bool isair(Pixel*** a, int col, int row, int ay, int ax) {
    return (a[ay][ax])->getint('t') == 'a';
}
bool issand(Pixel*** a, int col, int row, int ay, int ax) {
    return (a[ay][ax])->getint('t') == 's';
}
//bool isairdiag(Pixel** a, int col, int row, int y, int x) {
//    return (*getvalue(a, col, row, y, x - 1)).getint('t') != 'a' and (a[y][x]).getint('t') == 'a';
//}
//bool isairdiag2(Pixel** a, int col, int row, int x, int y) {
//    return (*getvalue(a, col, row, y, x + 1)).getint('t') != 'a'
//        and (*getvalue(a, col, row, y, x + 2)).getint('t') != 'a'
//        and (a[x][y]).getint('t') == 'a';
//}
Changei gravity(Pixel* a, Pixel* b) {
    Changei c;
    c.path = 't';
    c.value = 's';
    return c;
};
Changei returngravity(Pixel* a, Pixel* b) {
    Changei c;
    c.path = 't';
    c.value = 'a';
    return c;
};
void printboard(Pixel*** arr, int col, int row) {
    for (int i = 0; col > i; i++) {
        for (int j = 0; row > j; j++) {
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

int main()
{
    //vector<customstr> intarr;
    //customstr abbb;
    //for (int i = 0; i < 5; i++) {
    //    intarr.push_back(abbb);
    //}
    //testfun(intarr);
    clock_t before = clock();
    int col = 1000;
    int row = 1000;
    Air asss;
    Sand sand;
    Pixel*** arr = new Pixel ** [col];
    for (int i = 0; i < col; i++) {
        arr[i] = new Pixel*[row];
    }
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            arr[i][j] = new Air;    
        }
    }
    for (int i = 0; i < col;i++) {
        arr[0][i] = new Sand;
    }
    //cout<< (*(arr[0][9])).getint('t');
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
    while (!gg) {
        
        //cout<<a[0].func.x(0)<<endl;
        checkfor(arr, col, row, updateset, a, changeset);
        //printboard(arr, col, row);
        //cout << changeset[0].typeoffunc<<endl;
        //cin >> gg;
        //cout << "a3: " << static_cast<int>((*(Changei*)changeset[0].a).path) << endl;
        applychangeset(arr, col, row, changeset);
        //cout << a[0].func.x(0) << endl;
        //cout<<updateset.size();
        updateset.clear();
        //if (log2(i) == floor(log2(i))) {
        //    cout << i <<'\n';
        //}
        if (i == 32) {
            cout << "time:" << static_cast<float>(clock() - before) / CLOCKS_PER_SEC;
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
