#pragma once
#include <iostream>
#include <utility>
#include <Windows.h>
#include <vector>
#include <bit>
#include <bitset>
#include "basicslib.h"
using namespace std;

typedef bitset<1> bit;

void errp(char a) {
    switch (a)
    {
    default:
        cout << "error at type: " << a <<endl;
        break;
    }
}

class Pixel {
public:
    char type;
    char gettype() {
        return type;
    }
    bit getbit(char a) {
        switch (a)
        {
        default:
            errp(type);
            return 0;
            break;
        }
    }
    void writebit(char a, bit b) {
        switch (a)
        {
        default:
            errp(type);
            return;
            break;
        }
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

typedef Change<bit>(*ptobf)(Pixel);
typedef Change<int> (*ptoif)(Pixel);
typedef Change<float>(*ptoff)(Pixel);
typedef Change<Pixel>(*ptopf)(Pixel);
typedef bool (*conditionchar)(Pixel);
struct func2d {
    conditionchar condition;
    bool toupdate;
    int x;
    int y;
    bitset<2> typef;
};
struct funcarr {
    void** arr = nullptr;
    func2d* settingarr = nullptr;
    int size1 = 0;
    ~funcarr() {
        delete[] arr;
    }
    void addell(ptobf func, int x, int y, bool toupdate=true,conditionchar condition=truec) {
        resize(arr, size1, size1 + 1);
        resize(settingarr, size1, size1 + 1);
        func2d a;
        a.condition = condition;
        a.toupdate = toupdate;
        a.x = x;
        a.y = y;
        a.typef = 0;
        settingarr[size1] = a;
        arr[size1] = func;
        size1++;
    }
    void addell(ptoif func, int x, int y, bool toupdate = true, conditionchar condition = truec) {
        resize(arr, size1, size1 + 1);
        resize(settingarr, size1, size1 + 1);
        func2d a;
        a.condition = condition;
        a.toupdate = toupdate;
        a.x = x;
        a.y = y;
        a.typef = 1;
        settingarr[size1] = a;
        arr[size1] = func;
        size1++;
    }
    void addell(ptoff func, int x, int y, bool toupdate = true, conditionchar condition = truec) {
        resize(arr, size1, size1 + 1);
        resize(settingarr, size1, size1 + 1);
        func2d a;
        a.condition = condition;
        a.toupdate = toupdate;
        a.x = x;
        a.y = y;
        a.typef = 2;
        settingarr[size1] = a;
        arr[size1] = func;
        size1++;
    }
    void addell(ptopf func, int x, int y, bool toupdate = true, conditionchar condition = truec) {
        resize(arr, size1, size1 + 1);
        resize(settingarr, size1, size1 + 1);
        func2d a;
        a.condition = condition;
        a.toupdate = toupdate;
        a.x = x;
        a.y = y;
        a.typef = 3;
        settingarr[size1] = a;
        arr[size1] = func;
        size1++;
    }
    int size() {
        return size1;
    }; 
    bitset<2> typef(int i) {
        if (i < size1) {
            return (settingarr[i].typef);
        }
        else {
            cout << "ERROR OUT OF INDEX X";
        }

    };
    int x(int i) {
        if (i < size1) {
            return (settingarr[i].x);
        }
        else {
            cout << "ERROR OUT OF INDEX X";
        }

    };
    int y(int i) {
        if (i < size1) {
            return (settingarr[i].y);
        }
        else {
            cout << "ERROR OUT OF INDEX Y";
        }
    };
    ptobf funcb(int i) {
        if (i < size1) {
            return (*(ptobf*)arr[i]);
        }
        else {
            cout << "ERROR OUT OF INDEX FUNCB";
        }
    };
    ptoif funci(int i) {
        if (i < size1) {
            return (*(ptoif*)arr[i]);
        }
        else {
            cout << "ERROR OUT OF INDEX FUNCI";
        }
    };
    ptoff funcf(int i) {
        if (i < size1) {
            return (*(ptoff*)arr[i]);
        }
        else {
            cout << "ERROR OUT OF INDEX FUNCF";
        }
    };
    ptopf funcp(int i) {
        if (i < size1) {
            return (*(ptopf*)arr[i]);
        }
        else {
            cout << "ERROR OUT OF INDEX FUNCP";
        }
    };
    conditionchar cond(int i) {
        if (i < size1) {
            return (settingarr[i].condition);
        }
        else {
            cout << "ERROR OUT OF INDEX COND";
        }
    };
    bool doupdate(int i) {
        if (i < size1) {
            return (settingarr[i].toupdate);
        }
        else {
            cout << "ERROR OUT OF INDEX DOUPDATE";
        }
    };
};
struct change {
    int y;
    int x;
    bitset<2> typef;
    char path;
    void* value;
};
void saferunup(Pixel** arr, int col, int row, int x, int y, funcarr& a, vector<pair<int, int>>& newupdateset, vector<change>& changeset) {
    int d = a.size();
    for (int i = 0; d > i; i++) {
        if(a.cond(i)(arr[x + a.x(i)][y + a.y(i)])){
            switch (a.typef(i).to_ulong())
            {
            case(0):
                Change<bit> b=a.funcb(i)(arr[x + a.x(i)][y + a.y(i)]);
            case(1):
                Change<bit> b = a.funcb(i)(getvalue(arr,x + a.x(i),y + a.y(i));
            default:
                break;
            }
            arr[x + a.x(i)][y + a.y(i)] = 
            if(a.doupdate(i)){
                newupdateset.push_back({ (x + a.x(i)),(y + a.y(i))});
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
