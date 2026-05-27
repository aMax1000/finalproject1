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
#include <set>
using namespace std;

typedef bitset<1> bit;
//Can disable error messages for some types of "CANNONT FIND ELEMENT" 
void errp(char type, char path) {
    switch (type)
    {
    default:
        cout << "CANNONT FIND ELEMENT: " << path << " AT TYPE " << type << endl;
        break;
    }
}


//General Pixel class with dummy fucntions
class Pixel {
protected:

public:
    char type;
    char gettype() {
        return type;
    }
    bit getbit(char a) {
        switch (a)
        {
        default:
            errp(type, a);
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
        case 't':
            return type;
            break;
        default:
            errp(type, a);
            return 0;
            break;
        }
    }
    void writeint(char a, int b) {
        switch (a)
        {
        case 't':
            type = b;
            break;
        default:
            errp(type, a);
            return;
            break;
        }
    }
    float getfloat(char a) {
        switch (a)
        {
        default:
            errp(type, a);
            return 0;
            break;
        }
    }
    void writefloat(char a, float b) {
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

        break;
    }
    return;
}


// Derived classes-materials
class Sand : public Pixel {
public:
    float t;
    Sand() {
        type = 's';
        t = 0;
    }
    float getfloat(char a) {
        switch (a)
        {
        case('T'):
            return t;
            break;
        default:
            errp(type, a);
            break;
        }
        return 0;
    }
    void writefloat(char a, float b) {
        switch (a)
        {
        case('T'):
            t = b;
            break;
        default:
            errp(type, a);

            break;
        }
        return;
    }
};
class Air : public Pixel {
public:

    float tempr = 0;
    Air() {
        type = 'a';
        tempr = 0;
    }
    float getfloat(char a) {
        switch (a)
        {
        case('T'):
            return tempr;
            break;
        default:
            errp(type, a);

            break;
        }
        return 0;
    }
    void writefloat(char a, float b) {
        switch (a)
        {
        case('T'):
            tempr = b;
            break;
        default:
            errp(type, a);
            break;
        }
        return;
    }
};

//transition of cordinates to loop the board
void cordtrans(int col, int row, int x, int y, int& x1, int& y1) {
    if (x < col and x >= 0) {
        x1 = x;
    }
    else if (x < 0) {
        x1 = x + col;
    }else{
        x1 = x - col;
    }
    if (y < row and y >= 0) {
        y1 = y;
    }
    else if (y < 0) {
        y1 =y + row;
    }
    else {
        y1 = y - row;
    }
}
//getting element ta coords of board with transition 
Pixel* getvalue(Pixel*** arr, int col, int row, int x, int y) {
    int x1 = 0;
    int y1 = 0;
    cordtrans(col, row, x, y, x1, y1);
    return arr[x1][y1];
}
//idk why you need with
void setvalue(Pixel*** arr, int col, int row, int x, int y, Pixel a) {
    int x1 = 0;
    int y1 = 0;
    cordtrans(col, row, x, y, x1, y1);
    *arr[x1][y1] = a;
}
bool truec(Pixel*** arr, int col, int row, int x, int y) {
    return true;
}
//path and value to change on Pixel
struct Changeb {
    bit value;
    char path;
};
struct Changei {
    int value;
    char path;
};
struct Changef {
    float value;
    char path;
};
struct Changep {
    Pixel value;
    char path;
};

//functions to change individual pixels
typedef Changeb(*ptobf)(Pixel*, Pixel*);
typedef Changei(*ptoif)(Pixel*, Pixel*);
typedef Changef(*ptoff)(Pixel*, Pixel*);
typedef Changep(*ptopf)(Pixel*, Pixel*);
typedef bool (*conditionchar)(Pixel***, int, int, int, int);

//settings of functions
struct func2d {
    conditionchar condition;
    bool toupdate;
    int x;
    int y;
    bitset<2> typef;
};

//object to run array of functions with settings
class funcarr {
private:

    void** arr = nullptr;
    func2d* settingarr = nullptr;
public:
    int size1 = 0;
    //ДЕКОНСТРУКТОР РАБОТАЕТ 2 РАЗА ЕСЛИ ОБЬЕКТ В ВЕКТОРЕ
    //~funcarr() {
    //    
    //    if (arr != nullptr) {
    //        delete[] arr;
    //    }
    //    if (settingarr != nullptr) {
    //        delete[] settingarr;
    //    }
    //}
    void addell(ptobf func, int x, int y, bool toupdate = true, conditionchar condition = truec) {
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
        settingarr[size1].typef = 0;
    }
    void addell(ptoif func, int x, int y, bool toupdate = true, conditionchar condition = truec) {
        resize(arr, size1, size1 + 1);
        resize(settingarr, size1, size1 + 1);
        func2d a;
        a.condition = condition;
        a.toupdate = toupdate;
        a.x = x;
        a.y = y;
        settingarr[size1] = a;
        arr[size1] = func;
        settingarr[size1].typef = 1;
        //cout << settingarr[size1].x << endl;
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
        settingarr[size1] = a;
        arr[size1] = func;
        size1++;
        settingarr[size1].typef = 2;
    }
    void addell(ptopf func, int x, int y, bool toupdate = true, conditionchar condition = truec) {
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
        settingarr[size1].typef = 3;
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
            //cout << "n " << settingarr[i].x << endl;
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
            return (ptobf)arr[i];
        }
        else {
            cout << "ERROR OUT OF INDEX FUNCB";
        }
    };
    ptoif funci(int i) {
        if (i < size1) {
            return (ptoif)arr[i];
        }
        else {
            cout << "ERROR OUT OF INDEX FUNCB";
        }
    };
    ptoff funcf(int i) {
        if (i < size1) {
            return (ptoff)arr[i];
        }
        else {
            cout << "ERROR OUT OF INDEX FUNCB";
        }
    };
    ptopf funcp(int i) {
        if (i < size1) {
            return (ptopf)arr[i];
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
    int typeof(int i) {
        return settingarr[i].typef.to_ulong();
    }
};


//derivative of Pixel with coords of change
struct updatee {
    int y;
    int x;
    void* a;
    bitset<2> typeoffunc = 1;
};

//running array of functions
void saferunup(Pixel*** arr, int col, int row, int x, int y, funcarr& a, 
    vector<pair<int, int>>& newupdateset, vector<updatee>& changeset) {
    clock_t before2 = clock();
    int d = a.size();
    updatee b;
    int x1;
    int y1;
    Pixel* initialpixel = getvalue(arr, col, row, x, y);
    for (int i = 0; d > i; i++) {
        //cout << "q:: " << a.x(0) << endl;
        cordtrans(col, row, x + a.x(i), y + a.y(i), b.x, b.y);
        if (a.cond(i)(arr, col, row, b.x, b.y)) {

            switch (a.typeof(i))
            {
            case(0):
                b.a = new Changeb;
                *(Changeb*)b.a = (a.funcb(i))(arr[b.x][b.y], initialpixel);
                break;
            case(1):
                b.a = new Changei;
                *(Changei*)b.a = (a.funci(i))(arr[b.x][b.y], initialpixel);
                break;
            case(2):
                b.a = new Changef;
                *(Changef*)b.a = (a.funcf(i))(arr[b.x][b.y], initialpixel);
                break;
            case(3):
                b.a = new Changep;
                *(Changep*)b.a = (a.funcp(i))(arr[b.x][b.y], initialpixel);
                break;
            default:
                cout << "ERROR AT NAME OF FUCNTION";
                break;
            }

            if (a.doupdate(i)) {
                newupdateset.push_back({ b.x,b.y });
            }
            //cout << "a: " << static_cast<int>(in.path)<<endl;
            //cout << "a2: " << static_cast<int>((*(Changei*)b.a).path)<<endl;
            changeset.push_back(b);
            //cout << "a3: " << static_cast<int>((*(Changei*)changeset[0].a).path) << endl;
            /*cout << "a22: " << static_cast<int>((*(Changei*)b.a).path) << endl;*/
        }
        //cout << "Q:: " << a.x(0) << endl;
    }
    //before1+=(clock()- before2);
    return;
}
//function with condition to trigger it 
struct funcexunit {
    funcarr func;
    conditionchar cond;
    void addell(funcarr& func1, conditionchar cond1) {
        func = func1;
        cond = cond1;
    }
};
//checking for target pixel paramiters among Pixels marked to update
//void update(Pixel*** arr, int col, int row,
//    vector<pair<int, int>>& updateset, vector<pair<int, int>>& newupdateset,
//    vector<funcexunit>& funcs, vector<updatee>& changeset) {
//    for (funcexunit a : funcs) {
//        for (pair<int, int> n : updateset) {
//            if (a.cond(arr, row, col, n.first, n.second)) {
//                saferunup(arr, col, row, n.first, n.second, a.func, newupdateset, changeset);
//            }
//        }
//    }
//    return;
//}

//applying 1 change io 1 pixel
void applychange(Pixel*** arr, int col, int row, updatee& a) {
    //cout <<"A: " <<static_cast<int>((*(Changei*)a.a).path);
    switch (a.typeoffunc.to_ulong())
    {
    case(0):
        (*arr[a.x][a.y]).writebit((*(Changeb*)a.a).path, (*(Changeb*)a.a).value);
        break;
    case(1):
        (*arr[a.x][a.y]).writeint(((*(Changei*)a.a).path), (*(Changei*)a.a).value);
        break;
    case(2):
        (*arr[a.x][a.y]).writefloat((*(Changef*)a.a).path, (*(Changef*)a.a).value);
        break;
    case(3):
        (*arr[a.x][a.y]).writePixel((*(Changep*)a.a).path, (*(Changep*)a.a).value);
        break;
    default:
        break;
    }
}
//loops applying
void applychangeset(Pixel*** arr, int col, int row, vector<updatee>& changeset) {
    for (updatee a : changeset) {
        //cout << changeset[0].typeoffunc << endl;
        applychange(arr, col, row, a);
        delete a.a;
    }
    changeset.clear();
}
void checkfor(Pixel*** arr, int col, int row, vector<pair<int, int>>& newupdateset,
    vector<funcexunit>& funcs, vector<updatee>& changeset) {
    auto before1 = chrono::high_resolution_clock::now();;
    auto clockc = chrono::high_resolution_clock::now();;
    for (int x = 0; x < funcs.size();x++) {
        for (int i = 0; i < col; i++) {
            for (int j = 0; j < row; j++) {
                if (funcs[x].cond(arr, row, col, i, j)) {
                    //cout << "e:: "<< funcs[0].func.x(0) << endl;
                    saferunup(arr, col, row, i, j, funcs[x].func, newupdateset, changeset);
                    //cout << "a41: " << static_cast<int>((*(Changei*)changeset[0].a).path) << endl;
                    //cout << "E:: " << funcs[0].func.x(0) << endl;
                }

            }
        }
        //cout << "a44: " << static_cast<int>((*(Changei*)changeset[0].a).path) << endl;
        //cout << "E2:: " << funcs[0].func.x(0) << endl;
    }
    //cout << "E3:: " << funcs[0].func.x(0) << endl;
    auto end = chrono::high_resolution_clock::now();;
    cout << chrono::duration_cast<chrono::nanoseconds>(end - before1).count() << endl;
    return;
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
