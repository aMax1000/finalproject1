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
#include "BMPreader.h"
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
    //d
    //switch (type)
    //{
    //default:
    //    cout << "CANNONT FIND ELEMENT: " << path << " AT TYPE " << type << endl;
    //    break;
    //}
}


//General Pixel class with dummy fucntions
class Pixel {
protected:

public:

    matreals type = VOIDM;

    virtual bool getbit(variableb a) {
        switch (a)
        {
        default:
            errp(type, a);
            return 0;
            break;
        }
    }
    virtual void writebit(variableb a, bool b) {
        switch (a)
        {
        default:
            errp(type, a);
            return;
            break;
        }
    }
    virtual int getint(variablei a) {
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
    virtual void writeint(variablei a, int b);
    virtual void writedint(variablei a, int b) {
        switch (a)
        {
        default:
            errp(type, a);
            break;
        }
    };
    virtual float getfloat(variablef a) {
        switch (a)
        {
        case TEMPRATURE:
            return 0;
            break;
        default:
            errp(type, a);
            return 0;
            break;
        }
    }
    virtual void writefloat(variablef a, float b) {
        switch (a)
        {
        case TEMPRATURE:
            break;
        default:
            errp(type, a);
            return;
            break;
        }
    }
    virtual void writedfloat(variablef a, float b) {
        switch (a)
        {
        case TEMPRATURE:
            break;
        default:
            errp(type, a);
            break;
        }
    };
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
    float t = 0;
    BasicMat() {
        t = 0;
    }
    virtual float getfloat(variablef a) {
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
    virtual void writefloat(variablef a, float b) {
        switch (a)
        {
        case(TEMPRATURE):
            //cout << "temp before"<<t << endl;
            t = b;
            //cout << "temp after" << t << endl;
            break;
        default:
            errp(type, a);

            break;
        }
        return;
    }
    virtual void writedfloat(variablef a, float b) {
        switch (a)
        {
        case(TEMPRATURE):
            //cout << "temp before"<<t << endl;
            t += b;
            //cout << "temp after" << t << endl;
            break;
        default:
            errp(type, a);

            break;
        }
        return;
    };
};
class Counuctor : public BasicMat {
public:
    bool charge = 0;
    bool cooldown = 0;
    Counuctor() {
        charge = 0;
        cooldown = 0;
    }
    virtual bool getbit(variableb a) {
        switch (a)
        {
        case POWER:
            //cout << '2';
            return charge;
            break;
        case ELCOLDOWN:
            return cooldown;
            break;
        default:
            errp(type, a);
            return 0;
            break;
        }
    }
    virtual void writebit(variableb a, bool b) {
        switch (a)
        {
        case POWER:
            //cout << 't';
            charge = b;
            break;
        case ELCOLDOWN:
            cooldown = b;
            break;
        default:
            errp(type, a);
            return;
            break;
        }
    }
};

void rewrite_type(Pixel* a, classes type) {
    Pixel* b;
    switch (type)
    {
    case VOIDC:
        b = new Void;
        break;
    case BASICMAT:
        b = new BasicMat;
        break;
    case COUNDUCTOR:
        b = new Counuctor;
        break;
    //case PARTICLE:
    //    return;
    default:
        cout << "ERROR AT REWRITING CLASS";
        return;
    }
    for (auto d : paramiterclasses(static_cast<classes>(consti(a->type, TYPE)))) {
        switch (d.second)
        {
        case 0:
            b->writebit(d.first.bv, a->getbit(d.first.bv));
            break;
        case 1:
            b->writeint(d.first.iv, a->getint(d.first.iv));
            break;
        case 2:
            b->writefloat(d.first.fv, a->getfloat(d.first.fv));
            break;
        default:
            cout << "ERROR AT REWRITING CLASS 2";
            break;
        }
    }

    delete a;
    a = b;

}

void Pixel::writeint(variablei a, int b) {
    switch (a)
    {
    case TYPEV:
        type = static_cast<matreals>(b);
        if (consti(type, TYPE) != consti(static_cast<matreals>(b), TYPE)) {
            rewrite_type(this, static_cast<classes>(consti(static_cast<matreals>(b), TYPE)));
        }
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
bool truec1(Pixel* a) {
    return true;
}
//path and value to change on Pixel
struct Changeb {
    variableb path;
    bool value;
};
struct Changei {
    variablei path;
    int value;
};
struct Changef {
    variablef path;
    float value;
};
struct Changes {
    int x;
    int y;
};
struct Changeid {
    variablei path;
    int value;
};
struct Changefd {
    variablef path;
    float value;
};

//functions to change individual pixels
typedef Changeb(*ptobf)(Pixel*, Pixel*);
typedef Changei(*ptoif)(Pixel*, Pixel*);
typedef Changef(*ptoff)(Pixel*, Pixel*);
typedef Changeid(*ptoidf)(Pixel*, Pixel*);
typedef Changefd(*ptofdf)(Pixel*, Pixel*);
typedef bool (*conditionchar)(Pixel*, Pixel*);
typedef bool (*conditionchar1)(Pixel*);

union U {
    ptobf b;
    ptoif i;
    ptoff f;
    ptoidf id;
    ptofdf fd;
};

struct toupdate {
    vector<updatesets> updatesetsss;
    vector<vector<pair<int, int>>> toupdates;
    void create(vector<pair<updatesets, vector<pair<int, int>>>> a) {
        for (pair<updatesets, vector<pair<int, int>>> n : a) {
            updatesetsss.push_back(n.first);
            toupdates.push_back(n.second);
        }
    }
    void push_back(updatesets updatesetsss1, vector<pair<int, int>> toupdates1) {
        updatesetsss.push_back(updatesetsss1);
        toupdates.push_back(toupdates1);
    }
    void clear() {
        updatesetsss.clear();
        toupdates.clear();
    }
};

//settings of functions
template <int Funcsize>
struct func2d {
    vector<pair<conditionchar, pair<int, int>>> condition;
    toupdate toupdates;
    bool breakontrue;
    bool reverceapply = false;
    int size = 1;
    array<pair<pair<int, int>, pair<U, unsigned char>>, Funcsize> func;
};

//object to run array of functions with settings


template <int Size, int Funcsize>
struct funcarr {
    array<func2d<Funcsize>, Size> settingarr;
    toupdate toupdatesg;
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
        for (pair<updatesets, vector<pair<int, int>>> n : a) {
            toupdatesg.push_back(n.first, n.second);
        }
    }
    void addell(vector<pair<pair<int, int>, unsigned char>> f, vector<U> f2,
        vector<pair<updatesets, vector<pair<int, int>>>> toupdates1,
        vector<pair<conditionchar, pair<int, int>>> condition, bool breakontrue1 = false, bool reverceapply1 = false) {
        array<pair<pair<int, int>, pair<U, unsigned char>>, Funcsize> func;
        if (f.size() != f2.size()) cout << "ERROR AT ADDELL";
        for (int i = 0; i < f.size(); i++) {
            func[i].first = f[i].first;
            func[i].second.second = f[i].second;
            func[i].second.first = f2[i];
        }
        func2d<Funcsize> a;
        a.condition = condition;
        a.toupdates.create(toupdates1);
        a.breakontrue = breakontrue1;
        a.reverceapply = reverceapply1;
        a.size = f.size();
        a.func = func;
        settingarr.at(size1) = a;
        size1++;
    }
    void addell(pair<int, int> cords, vector<pair<updatesets, vector<pair<int, int>>>> toupdates1,
        vector<pair<conditionchar, pair<int, int>>> condition, bool breakontrue1 = false) {
        func2d<1> a;
        a.condition = condition;
        a.toupdates.create(toupdates1);
        a.breakontrue = breakontrue1;
        a.reverceapply = false;
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
    toupdate& doupdate(int i) {
        if (i < size1) {
            return (settingarr[i].toupdates);
        }
        else {
            cout << "ERROR OUT OF INDEX DOUPDATE";
        }
    };
    bool breakontrue(int i) {
        if (i < size1) {
            return settingarr[i].breakontrue;
        }
        else {
            cout << "ERROR OUT OF INDEX breakontrue";
        }
    }
    bool reverceapply(int i) {
        if (i < size1) {
            return settingarr[i].reverceapply;
        }
        else {
            cout << "ERROR OUT OF INDEX breakontrue";
        }
    }
    int size(int i) {
        if (i < size1) {
            return settingarr[i].size;
        }
        else {
            cout << "ERROR OUT OF INDEX breakontrue";
        }
    }
    toupdate& doupdateg() {
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
        Changeid id;
        Changefd fd;
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
    pairset(int col, int row) {
        for (int i = 0; i < UPDATESETCOUNT.count; i++) {
            newupdatesett* aboba = new newupdatesett{ col,row };
            os.push_back({});
            ns.push_back(*aboba);
            if (i < UPDATESETCOUNT.count2) {
                for (int k = 0; k < col; k++) {
                    for (int j = 0; j < row; j++) {
                        os[i].push_back({ k,j });

                    }
                }
            }
        }
    }
    void refresh() {
        for (int i = 0; i < ns.size(); i++) {
            if (i != EVERYTHING) os[i] = ns[i].arr;
        }
        for (int i = 0; i < EVERYTHING; i++) {
            for (pair<int, int> a1 : ns[EVERYTHING].arr) {
                os[i].push_back(a1);
            }
        }
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
        //cout << "value: " << ((a.data.f).value)<< endl;
        (arr[a.x][a.y])->writefloat((a.data.f).path, (a.data.f).value);
        break;
    case(3):
        //cout << "g1";
        //cout << "first"<< "x"<<a.data.s.x<<"y"<< a.data.s.y << "   " << "second"<<"x"<<a.x<<"y"<<a.y << endl;
        swap(arr[a.data.s.x][a.data.s.y], arr[a.x][a.y]);
        //cout << "first" << "x" << a.data.s.x << "y" << a.data.s.y << "   " << "second" << "x" << a.x << "y" << a.y << endl;
        break;
    case(4):
        //cout << "value: " << ((a.data.f).value)<< endl;
        (arr[a.x][a.y])->writedint((a.data.i).path, (a.data.i).value);
        break;
    case(5):
        //cout << "value: " << ((a.data.f).value)<< endl;
        (arr[a.x][a.y])->writedfloat((a.data.f).path, (a.data.f).value);
        //cout << "a";
        break;
    default:
        cout << "ERROR AT APPLYING CHANGE VALUE";
        break;
    }
}

//running array of functions
template <int Size, int Funcsize>
void saferunup(Pixel*** arr, int col, int row, int x, int y, funcarr<Size, Funcsize>& a,
    vector<newupdatesett>& newupdateset, vector<updatee>& changeset) {
    updatee upd = {};
    int d = a.size();
    int start = true;
    int i2 = 0;
    Pixel* initialpixel = getvalue(arr, x, y);
    for (int i = 0; d > i; i++) {
        //cout << "a";

        if (runcondarr(a.cond(i), arr, col, row, x, y)) {
            //cout << "g3";
            for (int u = 0; u < a.size(i); u++) {
                const pair<pair<int, int>, pair<U, unsigned char>>& k = a.funb(i)[u];
                upd.x = (x + k.first.first) & maskx;
                upd.y = (y + k.first.second) & masky;
                switch (k.second.second)
                {
                case(0):
                    //b.a = new ;
                    //cout << 'g';
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
                    //cout << "change tempr:" << upd.data.f.value<<endl;
                    break;
                case(3):
                    //cout << "c1";
                    upd.data.s = { x, y };
                    upd.typeoffunc = 3;
                    break;
                case(4):
                    upd.data.id = (k.second.first.id)(arr[upd.x][upd.y], initialpixel);
                    upd.typeoffunc = 4;
                    break;
                case(5):
                    upd.data.fd = (k.second.first.fd)(arr[upd.x][upd.y], initialpixel);
                    //cout << "data:"<<upd.data.fd.value<<endl;
                    upd.typeoffunc = 5;
                    break;
                default:
                    cout << "ERROR AT NAME OF FUCNTION";
                    break;
                }
                if (a.reverceapply(i)) {
                    //cout << 'c';
                    upd.x = x & maskx;
                    upd.y = y & masky;
                }
                changeset.push_back(upd);
            }
            if (start) {
                i2 = 0;
                for (updatesets j : a.doupdateg().updatesetsss) {
                    for (pair<int, int> k : a.doupdateg().toupdates[i2]) {
                        newupdateset[j].push_back({ (x + k.first) & maskx ,(y + k.second) & masky });
                        //print(k);
                    }
                    i2++;
                }
                start = false;
            }

            i2 = 0;
            for (updatesets j : a.doupdate(i).updatesetsss) {
                for (pair<int, int> k : a.doupdate(i).toupdates[i2]) {
                    newupdateset[j].push_back({ (x + k.first) & maskx ,(y + k.second) & masky });
                }
                i2++;
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
template <int Size, int Funcsize>
struct funcexunit {
    vector<updatesets> whatupdetesetuse;
    funcarr<Size, Funcsize> func;
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
template <int Size, int Funcsize>
void checkfor(Pixel*** arr, int col, int row, vector<newupdatesett>& newupdateset,
    funcexunit<Size, Funcsize>& funcs, vector<updatee>& changeset) {
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
template <int Size, int Funcsize>
void update(Pixel*** arr, int col, int row,
    pairset& pairupdateset,
    funcexunit<Size, Funcsize>& funcs, vector<updatee>& changeset, updatesets whatupdetesetuse, bool instantapply = false) {
    for (pair<int, int> n : pairupdateset.os[whatupdetesetuse]) {
        if (funcs.cond1(arr[n.first][n.second])) {
            saferunup(arr, col, row, n.first, n.second, funcs.func, (pairupdateset.ns), changeset);
        }
    }
    if (instantapply) applychangeset(arr, col, row, changeset);
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
