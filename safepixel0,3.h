#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <Windows.h>
#include <bit>
#include <bitset>
#include <typeinfo>
#include <any>
#include "basicslib.h"
using namespace std;

typedef bitset<1> bit;
//Can disable error messages for some types of "CANNONT FIND ELEMENT" 
void errp(char type,char path) { 
    switch (type)
    {
    default:
        cout << "CANNONT FIND ELEMENT: "<< path << "AT TYPE" << type << endl;
        break;
    }
}


//General Pixel class with dummy fucntions
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
            errp(type,a);
            return 0;
            break;
        }
    }
    void writebit(char a, bit b) {
        switch (a)
        {
        default:
            errp(type, a);
            return;
            break;
        }
    }
    int getint(char a) {
        switch (a)
        {
        default:
            errp(type, a);
            return 0;
            break;
        }
    }
    void writeint(char a,int b) {
        switch (a)
        {
        default:
            errp(type, a);
            return;
            break;
        }
    }
    float getfloat(char a, float b) {
        switch (a)
        {
        default:
            errp(type, a);
            return 0;
            break;
        }
    }
    void writefloat(char a) {
        switch (a)
        {
        default:
            errp(type, a);
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
        errp(type, a);;
        return NULLPIXEL;
        break;
    }
}
void Pixel::writePixel(char a, Pixel b) {
    switch (a)
    {
    default:
        errp(type, a);;
        return;
        break;
    }
}


// Derived classes-materials
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
            errp(type, a);
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
            errp(type, a);
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
            errp(type, a);
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
            errp(type, a);
            return;
            break;
        }
    }
};

//transition of cordinates to loop the board
void cordtrans(int col, int row, int x, int y, int& x1, int& y1) {
    if (x >= col) {
        x1 = x - col;
    }else if(x<0){
        x1 = x + col;
    }
    else {
        x1 = x;
    }
    if (y >= row) {
        x1 = x - row;
    }
    else if (y < 0) {
        y1 = y + row;
    }
    else {
        y1 = y;
    }
}
//getting and setting of elements of board with transition 
Pixel getvalue(Pixel** arr, int col, int row, int x, int y) {
    int x1=0;
    int y1 = 0;
    cordtrans(col, row, x, y, x1, y1);
    return arr[x1][y1];
}
void setvalue(Pixel**& arr, int col, int row, int x, int y, Pixel a) {
    int x1 = 0;
    int y1 = 0;
    cordtrans(col, row, x, y, x1, y1);
    arr[x1][y1]=a;
}
bool truec(Pixel a) {
    return true;
}
//functions to change individual pixels
typedef Change<bit>(*ptobf)(Pixel);
typedef Change<int> (*ptoif)(Pixel);
typedef Change<float>(*ptoff)(Pixel);
typedef Change<Pixel>(*ptopf)(Pixel);
typedef bool (*conditionchar)(Pixel);

//settings of functions
struct func2d {
    conditionchar condition;
    bool toupdate;
    int x;
    int y;
    bitset<2> typef;
};

//object to run array of functions with settings
struct funcarr {
    void** arr = nullptr;
    func2d* settingarr = nullptr;
    int size1 = 0;
    ~funcarr() {
        delete[] arr;
    }
    void addell(void* func, int x, int y, bool toupdate=true,conditionchar condition=truec) {
        resize(arr, size1, size1 + 1);
        resize(settingarr, size1, size1 + 1);
        func2d a;
        a.condition = condition;
        a.toupdate = toupdate;
        a.x = x;
        a.y = y;
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
            cout << "ERROR OUT OF INDEX FUNCB";
        }
    };
    ptoff funcf(int i) {
        if (i < size1) {
            return (*(ptoff*)arr[i]);
        }
        else {
            cout << "ERROR OUT OF INDEX FUNCB";
        }
    };
    ptopf funcp(int i) {
        if (i < size1) {
            return (*(ptopf*)arr[i]);
        }
        else {
            cout << "ERROR OUT OF INDEX FUNCB";
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

//path and value to change on Pixel
template<typename T>
struct Change {
    T value;
    char path;
};

//derivative of Pixel with coords of change
struct updatee {
    int y;
    int x;
    void* a;
    bitset<2> typeoffunc;
};  

char getpath(void* a) {
    
}


//running array of functions
void saferunup(Pixel** arr, int col, int row, int x, int y, funcarr& a, vector<pair<int, int>>& newupdateset, vector<updatee>& changeset) {
    int d = a.size();
    for (int i = 0; d > i; i++) {
        updatee b;
        int x1;
        int y1;
        Change<bit> bi;
        Change<int> in;
        Change<float> floa;
        Change<Pixel> pixe;
        if(a.cond(i)(getvalue(arr, col, row, x + a.x(i), y + a.y(i)))){
            b.x = x + a.x(i);
            b.y = y + a.y(i);
            switch (typeid(a.funcb(i)).name()[3])
            {
            case('b'):
                bi = (a.funcb(i))(getvalue(arr, col, row, x + a.x(i), y + a.y(i)));
                b.a = &bi;
                break;
            case('i'):
                in = (a.funci(i))(getvalue(arr, col, row, x + a.x(i), y + a.y(i)));
                b.a = &in;
                break;
            case('f'):
                floa = (a.funcf(i))(getvalue(arr, col, row, x + a.x(i), y + a.y(i)));
                b.a = &floa;
                break;
            case('p'):
                pixe = (a.funcp(i))(getvalue(arr, col, row, x + a.x(i), y + a.y(i)));
                b.a = &pixe;
                break;
            default:
                cout << "ERROR AT NAME OF FUCNTION";
                break;
            }
                
            if(a.doupdate(i)){
                cordtrans(col, row, x, y, x1, y1);
                newupdateset.push_back({x1,y1});
            }
            changeset.push_back(b);
        }
    }
    return;
}
//function with condition to trigger it 
struct funcexunit {
    funcarr func;
    conditionchar cond;
};
//checking for target pixel paramiters among Pixels market to update
void update(Pixel**& arr, int col, int row, 
    vector<pair<int, int>> updateset, vector<pair<int, int>>& newupdateset, 
    vector<funcexunit> funcs, vector<updatee>& changeset) 
{
    Pixel point;
    for (pair<int, int> n : updateset) {
        point = getvalue(arr, col, row, n.first, n.second);
        for(funcexunit a : funcs){
            if(a.cond(point)){
                saferunup(arr, col, row, n.first, n.second, a.func,newupdateset, changeset);
            }
        }
    }
    return;
}


void applychange(Pixel**& arr, int col, int row, updatee a) {
    switch (a.typeoffunc.to_ulong())
    {
    case 0:
        writebit(a.a.)
    default:
        break;
    }
}
void applychangeset(Pixel**& arr, int col, int row, vector<updatee>& changeset) {
    for (updatee a : changeset) {

    }
}

//template<typename T>
//void saferun(T**& arr, int col, int row, int x, int y, funcarr& a) {
//    int d = a.size();
//    for (int i = 0; d > i; i++) {
//        if (not(((a.x(i) + x >= col) or (a.y(i) + y >= row)) or ((a.x(i) + x < 0) or (a.y(i) + y < 0)))) {
//            if (a.cond(i)) {
//                arr[x + a.x(i)][y + a.y(i)] = a.func(i)(arr[x + a.x(i)][y + a.y(i)]);
//            }
//        }
//    }
//    return;
//}
//bool scanfor(char**& arr, int col, int row, char target, funcarr& func) {
//    bool a = false;
//    for (int i = 0; col > i; i++) {
//        for (int j = 0; row > j; j++) {
//            if (arr[i][j] == target) {
//                a = true;
//                saferun(arr, col, row, i, j, func);
//            }
//        }
//    }
//    return a;
//}
