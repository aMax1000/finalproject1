#pragma once
#include <iostream>
#include <utility>
#include <Windows.h>
#include <bit>
#include <bitset>
#include <typeinfo>
#include <any>
#include "basicslib.h"
#include <set>
#include <array>
using namespace std;

typedef bitset<1> bit;

enum classes {
    VOIDI,
    BASICMAT
};
vector < pair<classes, pair<int, int>>> typerrdefarr;




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
    //Pixel getPixel(char a);
    //void writePixel(char a, Pixel b);

};
//Pixel NULLPIXEL;
//Pixel Pixel::getPixel(char a) {
//    switch (a)
//    {
//    default:
//        errp(type, a);;
//        return NULLPIXEL;
//        break;
//    }
//}
//void Pixel::writePixel(char a, Pixel b) {
//    switch (a)
//    {
//    default:
//        errp(type, a);;
//
//        break;
//    }
//    return;
//}


// Derived classes-materials

class Void : public Pixel {
public:
};

class BasicMat : public Void {
public:
    float t;
    BasicMat() {
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


Pixel* typeclasschange(Pixel* a,classes b) {
    switch (b)
    {
    case VOIDI:
        Void* ne=new Void(a);
        *ne = *a;
        return;
        break;
    case BASICMAT:
        break;
    default:
        break;
    }
}


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
bool truec(Pixel* a, Pixel* b) {
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
struct Changes {
    int x;
    int y;
};

//functions to change individual pixels
typedef Changeb(*ptobf)(Pixel*, Pixel*);
typedef Changei(*ptoif)(Pixel*, Pixel*);
typedef Changef(*ptoff)(Pixel*, Pixel*);
typedef bool (*conditionchar)(Pixel*, Pixel*);
typedef bool (*conditionchar1)(Pixel*);

//settings of functions
struct func2d {
    vector<pair<conditionchar,pair<int,int>>> condition;
    vector<pair<int, int>> toupdates;
    int x;
    int y;
    bitset<2> typef;
};

//object to run array of functions with settings
template <int Size>
class funcarr {
private:
    union {
        ptobf b;
        ptoif i;
        ptoff f;
    }*arr = nullptr;
    func2d* settingarr = nullptr;
public:
    funcarr() {
        array < union {
            ptobf b;
            ptoif i;
            ptoff f;
        }, Size > arr;
        array <func2d, Size> settingarr;
    }
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
    void addell(ptobf func, int x, int y, vector<pair<int, int>>& toupdates, vector<pair<conditionchar, pair<int, int>>>& condition) {
        if(size1<Size){
        func2d a;
        a.condition = condition;
        a.toupdates = toupdates;
        a.x = x;
        a.y = y;
        settingarr[size1] = a;
        arr[size1].b = func;
        settingarr[size1].typef = 0;
        size1++;
        }
        else {
            cout << "FUNCARR INDEX OVERFLOW";
        }
    }
    void addell(ptoif func, int x, int y, vector<pair<int, int>>& toupdates, vector<pair<conditionchar, pair<int, int>>>& condition) {
        if (size1 < Size) {
            func2d a;
            a.condition = condition;
            a.toupdates = toupdates;
            a.x = x;
            a.y = y;
            settingarr[size1] = a;
            arr[size1].i = func;
            settingarr[size1].typef = 1;
            //cout << settingarr[size1].x << endl;
            size1++;
        }
        else {
            cout << "FUNCARR INDEX OVERFLOW";
        }

    }
    void addell(ptoff func, int x, int y, vector<pair<int, int>>& toupdates, vector<pair<conditionchar, pair<int, int>>>& condition) {
        if (size1 < Size) {
            func2d a;
            a.condition = condition;
            a.toupdates = toupdates;
            a.x = x;
            a.y = y;
            settingarr[size1] = a;
            arr[size1].f = func;
            settingarr[size1].typef = 2;
            size1++;
        }
        else {
            cout << "FUNCARR INDEX OVERFLOW";
        }
    }
    void addell(int x, int y, vector<pair<int, int>>& toupdates, vector<pair<conditionchar, pair<int, int>>>& condition) {
        if (size1 < Size) {
            func2d a;
            a.condition = condition;
            a.toupdates = toupdates;
            a.x = x;
            a.y = y;
            settingarr[size1] = a;
            //arr[size1].s = nullptr;
            settingarr[size1].typef = 3;
            size1++;
        }
        else {
            cout << "FUNCARR INDEX OVERFLOW";
        }
    }
    void safecheck() {
        if (size1 < Size) {
            cout << "FUNCARR ISN`T FULL\n";
        }
        else {
            cout <<"size check successful\n"
        }
    }

    int size() {
        return size1;
    };
    bitset<2> typef(int i) {
        if (i < Size) {
            return (settingarr[i].typef);
        }
        else {
            cout << "ERROR OUT OF INDEX X\n";
        }

    };
    int x(int i) {
        if (i < Size) {
            //cout << "n " << settingarr[i].x << endl;
            return (settingarr[i].x);

        }
        else {
            cout << "ERROR OUT OF INDEX X\n";
        }

    };
    int y(int i) {
        if (i < Size) {
            return (settingarr[i].y);
        }
        else {
            cout << "ERROR OUT OF INDEX Y\n";
        }
    };
    ptobf funcb(int i) {
        if (i < Size) {
            return arr[i].b;
        }
        else {
            cout << "ERROR OUT OF INDEX FUNCB\n";
        }
    };
    ptoif funci(int i) {
        if (i < Size) {
            return arr[i].i;
        }
        else {
            cout << "ERROR OUT OF INDEX FUNCI\n";
        }
    };
    ptoff funcf(int i) {
        if (i < Size) {
            return arr[i].f;
        }
        else {
            cout << "ERROR OUT OF INDEX FUNCF\n";
        }
    };
    //ptosf funcs(int i) {
    //    if (i < size1) {
    //        return arr[i].s;
    //    }
    //    else {
    //        cout << "ERROR OUT OF INDEX FUNCB";
    //    }
    //};
    vector<pair<conditionchar, pair<int, int>>>& cond(int i) {
        if (i < Size) {
            return (settingarr[i].condition);
        }
        else {
            cout << "ERROR OUT OF INDEX COND";
        }
    };
    vector<pair<int, int>>& doupdate(int i) {
        if (i < Size) {
            return (settingarr[i].toupdates);
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
    int y,x;
    bitset<2> typeoffunc;
    union {
        Changeb b;
        Changei i;
        Changef f;
        Changes s;
    } data;
};

bool runcondarr(vector<pair<conditionchar, pair<int, int>>>& a, Pixel*** arr, int col, int row, int x, int y) {
    for (pair<conditionchar, pair<int, int>> i : a) {
        if(!i.first(arr[i.second.first][i.second.second], arr[x][y])) return false;
    }
    return true;
}


//running array of functions
void saferunup(Pixel*** arr, int col, int row, int x, int y, funcarr& a, 
    vector<newupdatesett>& newupdateset, vector<int>& nuscords, vector<updatee>& changeset) {
    clock_t before2 = clock();
    updatee upd = {};
    int d = a.size();
    int x1;
    int y1;
    Pixel* initialpixel = getvalue(arr, col, row, x, y);
    for (int i = 0; d > i; i++) {
        //cout << "q:: " << a.x(0) << endl;
        cordtrans(col, row, x + a.x(i), y + a.y(i), upd.x, upd.y);
        if (runcondarr(a.cond(i),arr, col, row, upd.x, upd.y)) {
            switch (a.typeof(i))
            {
            case(0):
                //b.a = new ;
                upd.data.b = (a.funcb(i))(arr[upd.x][upd.y], initialpixel);
                upd.typeoffunc = 0;
                break;
            case(1):
                upd.data.i = (a.funci(i))(arr[upd.x][upd.y], initialpixel);
                upd.typeoffunc = 1;
                break;
            case(2):
                upd.data.f = (a.funcf(i))(arr[upd.x][upd.y], initialpixel);
                upd.typeoffunc = 2;
                break;
            case(3):
                upd.data.s = { upd.x, upd.y };
                upd.typeoffunc = 3;
                break;
            default:
                cout << "ERROR AT NAME OF FUCNTION";
                break;
            }

            for (pair<int, int> k : a.doupdate(i)) {
                for(int j : nuscords){
                    newupdateset[j].push_back({upd.x+k.first,upd.y+k.second});
                }
            }
            //cout << "a: " << static_cast<int>(in.path)<<endl;
            //cout << "a2: " << static_cast<int>((*(Changei*)b.a).path)<<endl;
            changeset.push_back(upd);
            //cout << "a3: " << static_cast<int>((changeset[0].data.i).path) << endl;
            /*cout << "a22: " << static_cast<int>((*(Changei*)b.a).path) << endl;*/
        }
        //cout << "Q:: " << a.x(0) << endl;
    }
    //before1+=(clock()- before2);
    return;
}
//function with condition to trigger it 
struct funcexunit {
    vector<int>& nuscords;
    funcarr func;
    conditionchar1 cond1;
};
//checking for target pixel paramiters among Pixels marked to update


//applying 1 change io 1 pixel
void applychange(Pixel*** arr, int col, int row, updatee& a) {
    //cout <<"A: " <<static_cast<int>((*(Changei*)a.a).path);
    switch (a.typeoffunc.to_ulong())
    {
    case(0):
        (arr[a.x][a.y])->writebit((a.data.b).path, (a.data.b).value);
        break;
    case(1):
        (arr[a.x][a.y])->writeint((a.data.i).path, (a.data.i).value);
        break;
    case(2):
        (arr[a.x][a.y])->writefloat((a.data.f).path, (a.data.f).value);
        break;
    case(3):
        swap(arr[a.data.s.x][a.data.s.y], arr[a.x][a.y]);
        break;
    default:
        cout << "ERROR AT APPLYING CHANGE VALUE";
        break;
    }
}

struct newupdatesett {
    vector<pair<int, int>> arr;
    vector<vector<bit>> cleararr;
    void push_back(pair<int, int> input){
        if (!cleararr[input.first][input.second].to_ulong()) {
            arr.push_back(input);
            cleararr[input.first][input.second] = true;
        }
    }
};
//loops applying
void applychangeset(Pixel*** arr, int col, int row, vector<updatee>& changeset) {
    for (int i = 0; i < changeset.size(); i++) {
        //cout << changeset[0].typeoffunc << endl;
        applychange(arr, col, row, changeset[i]);
    }
    changeset.clear();
}
void checkfor(Pixel*** arr, int col, int row, vector<newupdatesett>& newupdateset,
    funcexunit& funcs, vector<updatee>& changeset) {
    auto before1 = chrono::high_resolution_clock::now();;
    auto clockc = chrono::high_resolution_clock::now();;
        for (int i = 0; i < col; i++) {
            for (int j = 0; j < row; j++) {
                if (funcs.cond1(arr[i][j])) {
                    //cout << "e:: "<< funcs[0].func.x(0) << endl;
                    saferunup(arr, col, row, i, j, funcs.func, newupdateset, funcs.nuscords, changeset);
                    //cout << "a41: " << static_cast<int>((*(Changei*)changeset[0].a).path) << endl;
                    //cout << "E:: " << funcs[0].func.x(0) << endl;
                }

            }
        }
        //cout << "a44: " << static_cast<int>((*(Changei*)changeset[0].a).path) << endl;
        //cout << "E2:: " << funcs[0].func.x(0) << endl;
    //cout << "E3:: " << funcs[0].func.x(0) << endl;
    auto end = chrono::high_resolution_clock::now();;
    //cout << chrono::duration_cast<chrono::microseconds>(end - before1).count() << endl;
    return;
}
void update(Pixel*** arr, int col, int row,
    vector<pair<int, int>>& updateset, vector<newupdatesett>& newupdateset,
    funcexunit& funcs, vector<updatee>& changeset) {
            for (pair<int, int> n : updateset) {
                if (funcs.cond1(arr[n.first][n.second])) {
                    saferunup(arr, col, row, n.first, n.second, funcs.func, newupdateset, funcs.nuscords, changeset);
                }
            }
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
