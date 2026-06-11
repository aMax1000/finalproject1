#pragma once
#include <vector>
#include <iostream>
#include <utility>
#include <Windows.h>
#include <bit>
#include <bitset>
#include <typeinfo>
#include <any>
#include <chrono>
#include <set>
#include <array>
#include "basicslib.h"
#include "constdata.h"
using namespace std;

unsigned short maskx;
unsigned short masky;

void setmasks(int x, int y) {
    maskx = x - 1;
    masky = y - 1;
    //cout << std::bitset<8>(maskx);
}


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

    matreals type;

    bool getbit(variableb a) {
        switch (a)
        {
        default:
            errp(type, a);
            return 0;
            break;
        }
    }
    void writebit(variableb a, bool b) {
        switch (a)
        {
        default:
            errp(type, a);
            return;
            break;
        }
    }
    int getint(variablei a) {
        switch (a)
        {
        case TYPEV:
            return type;
            break;
        default:
            errp(type, a);
            return 0;
            break;
        }
    }
    void writeint(variablei a, int b);
    float getfloat(variablef a) {
        switch (a)
        {
        default:
            errp(type, a);
            return 0;
            break;
        }
    }
    void writefloat(variablef a, float b) {
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
    Void() {
        type = VOIDM;
    }
};

class BasicMat : public Void {
public:
    float t;
    BasicMat() {
        t = 0;
    }
    float getfloat(variablef a) {
        switch (a)
        {
        case(TEMPRATURE):
            return t;
            break;
        default:
            errp(type, a);
            break;
        }
        return 0;
    }
    void writefloat(variablef a, float b) {
        switch (a)
        {
        case(TEMPRATURE):
            t = b;
            break;
        default:
            errp(type, a);

            break;
        }
        return;
    }
};


void rewrite_type(Pixel* a, classes type) {
    delete a;
    switch (type)
    {
    case VOIDC:
        a = new Void;
        return;
    case BASICMAT:
        a = new BasicMat;
        return;
    case COUNDUCTOR:
        return;
    case PARTICLE:
        return;
    default:
        cout << "ERROR AT REWRITING CLASS";
        return;
    }
}

void Pixel::writeint(variablei a, int b) {
    switch (a)
    {
    case TYPEV:
        if (consti(type, TYPE) != consti(static_cast<matreals>(b), TYPE)) {
            rewrite_type(this, static_cast<classes>(consti(static_cast<matreals>(b), TYPE)));
        }
        type = static_cast<matreals>(b);
        break;
    default:
        errp(type, a);
        return;
        break;
    }
}


//getting element ta coords of board with transition 
Pixel* getvalue(Pixel*** arr, int x, int y) {
    return arr[x & maskx][y & masky];
}


bool truec(Pixel* a, Pixel* b) {
    return true;
}
//path and value to change on Pixel
struct Changeb {
    bool value;
    variableb path;
};
struct Changei {
    int value;
    variablei path;
};
struct Changef {
    float value;
    variablef path;
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

union U {
    ptobf b;
    ptoif i;
    ptoff f;
};
template <size_t Sizeupdatesets, size_t Sizemaxupdates>
struct toupdate {
    int couter = 0;
    array<size_t, Sizeupdatesets> updatescount{};
    array<updatesets, Sizeupdatesets> updatesetsss{};
    array<array<pair<int8_t, int8_t>, Sizemaxupdates>, Sizeupdatesets> toupdates{};
    void create(vector<pair<updatesets, vector<pair<int, int>>>> a) {
        for (pair<updatesets, vector<pair<int, int>>> n : a) {
            if (couter == Sizemaxupdates) cout << "OUT OF RANGE Sizeupdatesets";
            updatesetsss[couter] = n.first;
            for (pair<int, int> k : n.second) {
                if (updatescount[couter] == Sizemaxupdates) cout << "OUT OF RANGE Sizemaxupdates";
                toupdates[couter][updatescount[couter]] = k;
                updatescount[couter]++;
            }
            couter++;
        }
    }

    void push_back(pair<updatesets, vector<pair<int, int>>> a) {
        updatesetsss[couter] = a.first;
        for (pair<int, int> k : a.second) {
            if (updatescount[couter] == Sizemaxupdates) cout << "OUT OF RANGE Sizemaxupdates";
            toupdates[couter][updatescount[couter]] = k;
            updatescount[couter]++;
        }
        couter++;
    }
};

//settings of functions
template <size_t Funcsize, size_t Sizeupdatesets, size_t Sizemaxupdates>
struct func2d {
    vector<pair<conditionchar, pair<int, int>>> condition;
    toupdate<Sizeupdatesets, Sizemaxupdates> toupdates;
    bool breakontrue;
    array<pair<pair<int, int>, pair<U, unsigned char>>, Funcsize> func;
};

//object to run array of functions with settings


template <size_t Size, size_t Funcsize, size_t Sizeupdatesets, size_t Sizemaxupdates>
class funcarr {
private:
    array<func2d<Funcsize, Sizeupdatesets, Sizemaxupdates>, Size> settingarr;
    toupdate<Sizeupdatesets, Sizemaxupdates> toupdatesg;
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
    void doupdatesg(vector<pair<updatesets, vector<pair<int, int>>>> a) {
        toupdatesg.create(a);
    }
    void addell(array<pair<pair<int, int>, pair<U, unsigned char>>, Funcsize> func, int x, int y,
        vector<pair<updatesets, vector<pair<int, int>>>> toupdates1,
        vector<pair<conditionchar, pair<int, int>>> condition, bool breakontrue1) {
        func2d<Funcsize,Sizeupdatesets, Sizemaxupdates> a;
        a.condition = condition;
        a.toupdates.create(toupdates1);
        a.breakontrue = breakontrue1;
        a.func = func;
        settingarr.at(size1) = a;
        size1++;
    }
    void addell(pair<int, int> cords, vector<pair<updatesets, vector<pair<int, int>>>> toupdates1,
        vector<pair<conditionchar, pair<int, int>>> condition, bool breakontrue1) {
        func2d<Funcsize, Sizeupdatesets, Sizemaxupdates> a;
        a.condition = condition;
        a.toupdates.create(toupdates1);
        a.breakontrue = breakontrue1;
        pair < pair<int, int>, pair<U, unsigned char>> h;
        h.first = cords;
        h.second.second = 3;
        a.func[0] = h;

        settingarr.at(size1) = a;
        size1++;
    }

    int size() {
        return size1;
    };
    unsigned char typef(int i) {
        if (i < size1) {
            return (settingarr.at(i).typef);
        }
        else {
            cout << "ERROR OUT OF INDEX X\n";
        }

    };
    array<pair<pair<int, int>, pair<U, unsigned char>>, Funcsize> funb(int i) {
        if (i < size1) {
            return settingarr[i].func;
        }
        else {
            cout << "ERROR OUT OF INDEX FUNCB\n";
        }
    };
    vector<pair<conditionchar, pair<int, int>>>& cond(int i) {
        if (i < size1) {
            return (settingarr[i].condition);
        }
        else {
            cout << "ERROR OUT OF INDEX COND";
        }
    };
    toupdate<Sizeupdatesets, Sizemaxupdates>& doupdate(int i) {
        if (i < size1) {
            return (settingarr[i].toupdates);
        }
        else {
            cout << "ERROR OUT OF INDEX DOUPDATE";
        }
    };
    int typeof(int i) {
        if (i < size1) {
            return settingarr[i].typef;
        }
        else {
            cout << "ERROR OUT OF INDEX TYPEOF";
        }
    }
    bool breakontrue(int i) {
        if (i < size1) {
            return settingarr[i].breakontrue;
        }
        else {
            cout << "ERROR OUT OF INDEX breakontrue";
        }
    }
    bool instantapply(int i) {
        if (i < size1) {
            return settingarr[i].instantapply;
        }
        else {
            cout << "ERROR OUT OF INDEX instantapply";
        }
    }
    toupdate<Sizeupdatesets, Sizemaxupdates>& doupdateg() {
        return (toupdatesg);
    };
};


//derivative of Pixel with coords of change
struct updatee {
    int x, y;
    unsigned char typeoffunc;
    union {
        Changeb b;
        Changei i;
        Changef f;
        Changes s;
    } data;
};

//running array of if`s
bool runcondarr(vector<pair<conditionchar, pair<int, int>>>& a, Pixel*** arr, int col, int row, int x, int y) {
    for (pair<conditionchar, pair<int, int>> i : a) {
        //cout << "g4";
        //cout << i.first(arr[i.second.first][i.second.second], arr[x][y]);
        if (!i.first(getvalue(arr, i.second.first + x, i.second.second + y), arr[x][y])) return false;
    }
    return true;
}

//structure for adding updates(not linked to "updatee") for next step
struct newupdatesett {
    bool** cleararr = nullptr;
    newupdatesett(int col, int row) {
        cleararr = new bool* [col];
        for (int i = 0; i < col; i++) {
            cleararr[i] = new bool[row];
            //cout << cleararr[i];
            for (int j = 0; j < row; j++) {
                cleararr[i][j] = false;
            }
        }
        //print(cleararr, col, row);
    }
    vector<pair<int, int>> arr;
    void push_back(pair<int, int> input) {
        //cout << "g6";
        if (!cleararr[input.first][input.second]) {
            arr.push_back(input);
            cleararr[input.first][input.second] = true;
        }
        //cout << "g7";
    }
    void clear1() {
        for (pair<int, int> a : arr) {
            cleararr[a.first][a.second] = false;
        }
        arr.clear();
    }
};
//pair of newupdateset and old updateset
struct pairset {

    vector<newupdatesett> ns;
    vector<vector< pair<int, int>>> os;
    pairset(int len, int col, int row) {
        for (int i = 0; i < len; i++) {
            newupdatesett* aboba = new newupdatesett{ col,row };
            os.push_back({});
            ns.push_back(*aboba);
            for (int k = 0; k < col; k++) {
                for (int j = 0; j < row; j++) {
                    os[i].push_back({ k,j });

                }
            }
        }
    }
    void refresh() {
        //cout << "aboba2";
        for (int i = 0; i < ns.size(); i++) {
            //cout << "aboba3";
            os[i] = ns[i].arr;
            //cout << "aboba31";
        }
        //cout << "aboba4";
        for (int i = 0; i < ns.size(); i++) {
            ns[i].clear1();
        }
    }
};


//applying 1 change io 1 pixel
void applychange(Pixel***& arr, int col, int row, updatee& a) {
    //cout <<"A: " <<static_cast<int>((*(Changei*)a.a).path);
    switch (a.typeoffunc)
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
        //cout << "g1";
        //cout << "first"<< "x"<<a.data.s.x<<"y"<< a.data.s.y << "   " << "second"<<"x"<<a.x<<"y"<<a.y << endl;
        swap(arr[a.data.s.x][a.data.s.y], arr[a.x][a.y]);
        //cout << "first" << "x" << a.data.s.x << "y" << a.data.s.y << "   " << "second" << "x" << a.x << "y" << a.y << endl;
        break;
    default:
        cout << "ERROR AT APPLYING CHANGE VALUE";
        break;
    }
}

//running array of functions
template <size_t Size, size_t Funcsize, size_t Sizeupdatesets, size_t Sizemaxupdates >
void saferunup(Pixel*** arr, int col, int row, int x, int y, funcarr<Size, Funcsize, Sizeupdatesets, Sizemaxupdates>& a,
    vector<newupdatesett>& newupdateset, vector<updatee>& changeset) {
    updatee upd = {};
    int d = a.size();
    int counder2=0;
    int counter1 = a.doupdateg().couter;
    for (int i2 = 0; i2 < counter1; i2++) {
        updatesets j = a.doupdateg().updatesetsss[i2];
        counder2 = a.doupdateg().updatescount[i2];
        for (int i3 = 0; i3 < counder2; i3++) {
            pair<int, int> k = (a.doupdateg().toupdates[i2][i3]);
            newupdateset[j].push_back({ (x + k.first) & maskx ,(y + k.second) & masky });
            //cout << '1';
        }
    }
    Pixel* initialpixel = getvalue(arr, x, y);
    for (int i = 0; d > i; i++) {
        //cout << "a";

        if (runcondarr(a.cond(i), arr, col, row, x, y)) {
            //cout << "g3";
            for (pair<pair<int, int>, pair<U, unsigned char>> k : a.funb(i)) {
                upd.x = (x + k.first.first) & maskx;
                upd.y = (y + k.first.second) & masky;
                switch (k.second.second)
                {
                case(0):
                    //b.a = new ;
                    upd.data.b = (k.second.first.b)(arr[upd.x][upd.y], initialpixel);
                    upd.typeoffunc = 0;
                    break;
                case(1):
                    upd.data.i = (k.second.first.i)(arr[upd.x][upd.y], initialpixel);
                    upd.typeoffunc = 1;
                    break;
                case(2):
                    upd.data.f = (k.second.first.f)(arr[upd.x][upd.y], initialpixel);
                    upd.typeoffunc = 2;
                    break;
                case(3):
                    //cout << "c1";
                    upd.data.s = { x, y };
                    upd.typeoffunc = 3;
                    break;
                default:
                    cout << "ERROR AT NAME OF FUCNTION";
                    break;
                }
                changeset.push_back(upd);
            }
            counter1 = a.doupdate(i).couter;
            for (int i2 = 0; i2 < counter1; i2++) {
                updatesets j = a.doupdate(i).updatesetsss[i2];
                counder2 = a.doupdate(i).updatescount[i2];
                for (int i3 = 0; i3 < counder2; i3++) {
                    pair<int, int> k = a.doupdate(i).toupdates[i2][i3];
                    newupdateset[j].push_back({ (x + k.first) & maskx ,(y + k.second) & masky });
                }
            }
            //cout << "g5";
            //cout << "a: " << static_cast<int>(in.path)<<endl;
            //cout << "a2: " << static_cast<int>((*(Changei*)b.a).path)<<endl;

            if (a.breakontrue(i)) return;
            //cout << "a3: " << static_cast<int>((changeset[0].data.i).path) << endl;
            /*cout << "a22: " << static_cast<int>((*(Changei*)b.a).path) << endl;*/
        }
        //cout << "Q:: " << a.x(0) << endl;
    }
    //before1+=(clock()- before2);
    return;
}

//function with condition to trigger it 
template <size_t Size, size_t Funcsize, size_t Sizeupdatesets, size_t Sizemaxupdates >
struct funcexunit {
    vector<updatesets> whatupdetesetuse;
    funcarr<Size, Funcsize, Sizeupdatesets, Sizemaxupdates> func;
    conditionchar1 cond1;
};
//checking for target pixel paramiters among Pixels marked to update





//loops applying
void applychangeset(Pixel*** arr, int col, int row, vector<updatee>& changeset) {
    for (int i = 0; i < changeset.size(); i++) {
        //cout << changeset[0].typeoffunc << endl;
        applychange(arr, col, row, changeset[i]);
    }
    changeset.clear();
}

//checking all of board for condition
template <size_t Size, size_t Funcsize, size_t Sizeupdatesets, size_t Sizemaxupdates >
void checkfor(Pixel*** arr, int col, int row, vector<newupdatesett>& newupdateset,
    funcexunit<Size, Funcsize, Sizeupdatesets, Sizemaxupdates>& funcs, vector<updatee>& changeset) {
    auto before1 = chrono::high_resolution_clock::now();;
    auto clockc = chrono::high_resolution_clock::now();;
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (funcs.cond1(arr[i][j])) {
                //cout << "g2";
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

//checking only updatesets for condition
template <size_t Size, size_t Funcsize, size_t Sizeupdatesets, size_t Sizemaxupdates>
void update(Pixel*** arr, int col, int row,
    pairset& pairupdateset,
    funcexunit<Size, Funcsize, Sizeupdatesets, Sizemaxupdates>& funcs, vector<updatee>& changeset) {
    for (updatesets i : funcs.whatupdetesetuse)
        for (pair<int, int> n : pairupdateset.os[i]) {
            if (funcs.cond1(arr[n.first][n.second])) {
                saferunup(arr, col, row, n.first, n.second, funcs.func, (pairupdateset.ns), changeset);
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
