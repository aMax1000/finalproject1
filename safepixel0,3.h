#pragma once
#include <iostream>
#include <utility>
#include <Windows.h>
#include <set>
#include <unordered_set>
#include "basicslib.h"
using namespace std;



void errp(char a) {
    switch (a)
    {
    default:
        cout << "error at type" << a;
        break;
    }
}

class Pixel {
public:
    char type;
    char gettype() {
        return type;
    }
    int getint(char a) {
        switch (a)
        {
        default:
            errp(type);
            return 0;
            break;
        }
    }
    void writeint(char a,int b) {
        switch (a)
        {
        default:
            errp(type);
            return;
            break;
        }
    }
    float getfloat(char a, float b) {
        switch (a)
        {
        default:
            errp(type);
            return 0;
            break;
        }
    }
    void writefloat(char a) {
        switch (a)
        {
        default:
            errp(type);
            return;
            break;
        }
    }
    Pixel getPixel(char a);
    void writePixel(char a, Pixel b);
    
};
Pixel NULLPIXEL;
Pixel Pixel::getPixel(char a) {
    switch (a)
    {
    default:
        errp(type);
        return NULLPIXEL;
        break;
    }
}
void Pixel::writePixel(char a, Pixel b) {
    switch (a)
    {
    default:
        errp(type);
        return;
        break;
    }
}


// Derived class
class Sand : public Pixel {
public:
    char type = 's';
    float t = 0;
    float getfloat(char a) {
        switch (a)
        {
        case('t'): 
            return t;
        default:
            errp(type);
            return 0;
            break;
        }
    }
    void writefloat(char a,float b) {
        switch (a)
        {
        case('t'):
            t = b;
        default:
            errp(type);
            return;
            break;
        }
    }
};
class Air : public Pixel {
public:
    char type = 'a';
    float t = 0;
    float getfloat(char a) {
        switch (a)
        {
        case('t'):
            return t;
        default:
            errp(type);
            return 0;
            break;
        }
    }
    void writefloat(char a, float b) {
        switch (a)
        {
        case('t'):
            t = b;
        default:
            errp(type);
            return;
            break;
        }
    }
};
bool truec(Pixel a) {
    return true;
}

template<typename T>
struct Change {
    T value;
    char path;
};

typedef Change<int> (*ptoif)(Pixel);
typedef Change<float>(*ptoff)(Pixel);
typedef Change<Pixel>(*ptopf)(Pixel);
typedef bool (*conditionchar)(Pixel);
struct func2d {
    conditionchar condition;
    ctocf func;
    bool toupdate;
    int x;
    int y;
};
struct funcarr {
    void** arr = new void*[1];
    int size1 = 0;
    ~funcarr() {
        delete[] arr;
    }
    void addell(ptoif func, int x, int y, bool toupdate=true,conditionchar condition=truec) {
        resize(arr, size1, size1 + 1);
        func2d a;
        a.condition = condition;
        a.func = func;
        a.toupdate = toupdate;
        a.x = x;
        a.y = y;
        arr[size1] = &a;
        size1++;
    }
    int size() {
        return size1;
    };
    int x(int i) {
        if (i < size1) {
            return (*(int*)(arr[i]).x);
        }
        else {
            cout << "ERROR OUT OF INDEX X";
        }

    };
    int y(int i) {
        if (i < size1) {
            return (arr[i].y);
        }
        else {
            cout << "ERROR OUT OF INDEX Y";
        }
    };
    ctocf func(int i) {
        if (i < size1) {
            return (arr[i].func);
        }
        else {
            cout << "ERROR OUT OF INDEX FUNC";
        }
    };
    conditionchar cond(int i) {
        if (i < size1) {
            return (arr[i].condition);
        }
        else {
            cout << "ERROR OUT OF INDEX COND";
        }
    };
    bool doupdate(int i) {
        if (i < size1) {
            return (arr[i].toupdate);
        }
        else {
            cout << "ERROR OUT OF INDEX DOUPDATE";
        }
    };
};

template<typename T>
void saferunup(T**& arr, int col, int row, int x, int y, funcarr& a, vector<pair<int, int>>& newupdateset) {
    int d = a.size();
    for (int i = 0; d > i; i++) {
        if (not(((a.x(i) + x >= col) or (a.y(i) + y >= row)) or ((a.x(i) + x < 0) or (a.y(i) + y < 0)))) {
            if(a.cond(i)(arr[x + a.x(i)][y + a.y(i)])){
                arr[x + a.x(i)][y + a.y(i)] = a.func(i)(arr[x + a.x(i)][y + a.y(i)]);
                if(a.doupdate(i)){
                    newupdateset.push_back({ (x + a.x(i)),(y + a.y(i))});
                }
            }
        }
    }
    return;
}


bool update(char**& arr, int col, int row, char target,vector<pair<int, int>> updateset, vector<pair<int, int>>& newupdateset, funcarr& funcarr) {
    bool a = false;
    for (pair<int, int> n : updateset) {
        if(arr[n.first][n.second]==target){
            saferunup(arr, col, row, n.first, n.second, funcarr,newupdateset);
        }
    }
    return a;
}





template<typename T>
void saferun(T**& arr, int col, int row, int x, int y, funcarr& a) {
    int d = a.size();
    for (int i = 0; d > i; i++) {
        if (not(((a.x(i) + x >= col) or (a.y(i) + y >= row)) or ((a.x(i) + x < 0) or (a.y(i) + y < 0)))) {
            if (a.cond(i)) {
                arr[x + a.x(i)][y + a.y(i)] = a.func(i)(arr[x + a.x(i)][y + a.y(i)]);
            }
        }
    }
    return;
}
bool scanfor(char**& arr, int col, int row, char target, funcarr& func) {
    bool a = false;
    for (int i = 0; col > i; i++) {
        for (int j = 0; row > j; j++) {
            if (arr[i][j] == target) {
                a = true;
                saferun(arr, col, row, i, j, func);
            }
        }
    }
    return a;
}
