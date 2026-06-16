// sandfall.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <utility>
#include <vector>
#include <Windows.h>
#include <bit>
#include <bitset>
#include <typeinfo>
#include <chrono>
#include <array>
#include <stack>
#include <thread>
#include <cstdlib>
#include "basicslib.h"
#include "safepixel1,2,5.h"
#include "constdata.h"
#include "sandfall.h"

static bool isair(Pixel* a, Pixel* b) {
    return (a)->getint(TYPEV) == VOIDM;
}
static bool issimplefallable(Pixel* a) {
    return constb(a->type, IS_SIMPLEFALLABLE);
}
static bool issimplefloatable1(Pixel* a) {
    return constb(a->type, IS_SIMPLEFLOATABLE);
}
static bool issimplefloatable(Pixel* a, Pixel* b) {
    return constb(a->type, IS_SIMPLEFLOATABLE);
}
static Changefd termalexcange(Pixel* a, Pixel* b) {
    float ret = (a->getfloat(TEMPRATURE) - b->getfloat(TEMPRATURE))
        * constf((a->type), THERMAL_CONDUCIVITY) * constf((b->type), THERMAL_CONDUCIVITY);
    //cout << "datepre: " << ret << endl;
    return { TEMPRATURE,ret };
}
static Changei melt(Pixel* a, Pixel* b) {
    //cout << "melt_type: " << consti(a->type, MELT_TYPE) << endl;
    return { TYPEV,consti(a->type,MELT_TYPE) };
}
static Changei solidify(Pixel* a, Pixel* b) {
    return { TYPEV,consti(a->type,SOLID_TYPE) };
}
static bool canmelt(Pixel* a, Pixel* b) {
    //cout << "melt_type: " << consti(a->type, MELT_TYPE) << endl;
    return ((consti(a->type, MELT_TYPE) != -1) and (a->getfloat(TEMPRATURE) >= constf(a->type, MELT_TEMPRATURE)));
}
static bool cansolidify(Pixel* a, Pixel* b) {
    return consti(a->type, SOLID_TYPE) != -1 and a->getfloat(TEMPRATURE) <= constf(a->type, SOLID_TEMPRATURE);
}
static bool instvoid1(Pixel* a) {
    return (consti(a->type, TYPE) != VOIDC);
}
static bool inconductor1(Pixel* a) {
    //cout << (consti(a->type, TYPE) == COUNDUCTOR and !a->getbit(ELCOLDOWN));
    return (consti(a->type, TYPE) == COUNDUCTOR and !(a->getbit(ELCOLDOWN)));

}
static bool inconductor(Pixel* a, Pixel* b) {
    return (!(a->getbit(ELCOLDOWN)) and !(a->getbit(POWER)));
}
static Changeb charging(Pixel* a, Pixel* b) {
    return { POWER,true };
}
static Changeb discharging(Pixel* a, Pixel* b) {
    return { POWER,false };
}
static Changeb coolcharging(Pixel* a, Pixel* b) {
    return { ELCOLDOWN,true };
}
static Changeb discoolcharging(Pixel* a, Pixel* b) {
    return { ELCOLDOWN,false };
}
//static bool isgatecloseablestrong(Pixel* a, Pixel* b) {
//    return a->getbit(ISGATE) and !a->getbit(ELCOLDOWN);
//}

//d
//static bool ischarge(Pixel* a, Pixel* b) {
//    return a->getbit(POWER) and !a->getbit(ELCOLDOWN);
//}
static bool ischarge1(Pixel* a) {
    return ((a->getbit(POWER)) and !(a->getbit(ELCOLDOWN)));
}
static bool iscoolcharge1(Pixel* a) {
    return ((a->getbit(ELCOLDOWN)));
}
//static bool isgate(Pixel* a, Pixel* b) {
//    return (a->type == GATE);
//}
//static Changei disablegate(Pixel* a, Pixel* b) {
//    return { TYPEV,VOIDM };
//}

char pixelchar(int type) {
    switch (type) {
    case VOIDM:
        return ' ';
        break;
    case BEDROCK:
        return 'B';
        break;
    case IRON:
        return 'I';
        break;
    case COPPER:
        return 'C';
        break;
    case MOLTEN_COPPER:
        return 'L';
        break;
    case MOLTEN_IRON:
        return 'L';
        break;
    case SAND:
        return 'S';
        break;
    case WATER:
        return 'W';
        break;
    case GATE:
        return 'G';
        break;
    default:
        std::cout << "UNDISPLAYABLE PIXEL";
        return ' ';
    }
}
char pixelcolors(int type) {
    switch (type) {
    case VOIDM:
        return 0;
        break;
    case BEDROCK:
        return 8;
        break;
    case IRON:
        return 7;
        break;
    case COPPER:
        return 6;
        break;
    case MOLTEN_COPPER:
        return 14;
        break;
    case MOLTEN_IRON:
        return 6;
        break;
    case SAND:
        return 14;
        break;
    case WATER:
        return 9;
        break;
    case GATE:
        return 8;
        break;
    default:
        std::cout << "UNDISPLAYABLE PIXEL";
        return ' ';
    }
}
int termalcolors(float tempr) {
    if (tempr < 200) {
        return 0;
    }
    else if (tempr < 400) {
        return 4;
    }
    else if (tempr < 600) {
        return 12;
    }
    else if (tempr < 800) {
        return 6;
    }
    else if (tempr < 1000) {
        return 14;
    }
    else {
        return 15;
    }
}
void displaypixel(Pixel* a) {
    //cout << a->getbit(POWER);
    if (a->getbit(POWER)) {
        SetColor(pixelcolors(a->type), 14);
    }
    else if (a->getbit(ELCOLDOWN)) {
        SetColor(pixelcolors(a->type), 6);
    }
    else {
        int t = termalcolors(a->getfloat(TEMPRATURE));
        if (t == 0) {
            SetColor(0, pixelcolors(a->type));
        }
        else {
            SetColor(pixelcolors(a->type), t);
        }
    }

    cout << pixelchar(a->type);
    SetColor(7, 0);
};

static void printboard(Pixel*** arr, int COL, int ROW) {
    std::system("cls");
    for (int i = 0; COL > i; i++) {
        for (int j = 0; ROW > j; j++) {
            displaypixel(arr[i][j]);
            cout << ' ';
        }
        cout << "| \n";
    }
    for (int j = 0; ROW > j; j++) {
        cout << "--";
    }
    cout << '\n';
    SetColor(7, 0);
}
static void printboardtemprature(Pixel*** arr, int COL, int ROW) {
    for (int i = 0; COL > i; i++) {
        for (int j = 0; ROW > j; j++) {
            cout << ((arr[i][j]->getfloat(TEMPRATURE)));
            cout << ' ';
        }
        cout << "| \n";
    }
    for (int j = 0; ROW > j; j++) {
        cout << "--";
    }
    cout << '\n';
}


static void pointsetBasicMat(Pixel*** arr, int COL, int ROW, int x, int y, vector<updatesets> a, pairset& updateset, BasicMat b) {
    delete arr[x & maskx][y & masky];
    arr[x & maskx][y & masky] = new BasicMat{ b };
    for (updatesets k : a) {
        updateset.ns[k].push_back({ x & maskx,y & masky });
    }
}
static void pointsetBasicMat(Pixel*** arr, int COL, int ROW, int x, int y, vector<updatesets> a, pairset& updateset, Counuctor b) {
    delete arr[x & maskx][y & masky];
    arr[x & maskx][y & masky] = new Counuctor{ b };
    for (updatesets k : a) {
        updateset.ns[k].push_back({ x & maskx,y & masky });
    }
}

//struct mainb {
//    int COL;
//    int ROW;
//    constexpr auto FRAMERATE;
//    constexpr auto SKIPFRAMES;
//
//};



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    int COL = pow(2, 5);
    int ROW = pow(2, 5);
    constexpr auto FRAMERATE = 5;
    constexpr auto SKIPFRAMES = 1;
    signed char** gatearr = new signed char *[COL];
    for (int i = 0; i < COL; i++) {
        gatearr[i] = new signed char [ROW];
        for (int j = 0; j < ROW; j++) {
            gatearr[i][j] = 0;
        }
    }


    setmasks(COL, ROW);
    Pixel*** arr = new Pixel * *[COL];
    for (int i = 0; i < COL; i++) {
        arr[i] = new Pixel * [ROW];
    }
    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < ROW; j++) {
            arr[i][j] = new Void;
        }
    }
    //d
    //for (int i = 0; i < COL; i += 2) {
    //    for (int j = 0; j < ROW; j++) {
    //        arr[i][j] = new BasicMat;
    //        arr[i][j]->type = SAND;
    //    }
    //}

    //d
    //for (int j = 1; j < 5; j++) {
    //    arr[10][j] = new BasicMat;
    //    arr[10][j]->type = BEDROCK;
    //}
    //for (int j = 10; j < 16; j++) {
    //    arr[10][j] = new BasicMat;
    //    arr[10][j]->type = BEDROCK;
    //}
    //for (int i = 0; i < COL; i++) {
    //    arr[i][0] = new BasicMat;
    //    arr[i][0]->type = BEDROCK;
    //}
    //for (int i = 0; i < COL; i++) {
    //    arr[i][6] = new BasicMat;
    //    arr[i][6]->type = BEDROCK;
    //}
    //for (int i = 0; i < COL; i++) {
    //    arr[i][8] = new BasicMat;
    //    arr[i][8]->type = BEDROCK;
    //}
    //for (int i = 0; i < COL; i++) {
    //    arr[i][15] = new BasicMat;
    //    arr[i][15]->type = BEDROCK;
    //}

    for (int i = 0; i < COL - 1; i++) {
        for (int j = 3; j < 14; j++) {
            arr[i][j] = new Counuctor;
            arr[i][j]->type = COPPER;
        }

    }
    for (int i = 0; i < COL - 1; i++) {
        for (int j = 0; j < 2; j++) {
            arr[i][j] = new Counuctor;
            arr[i][j]->type = GATE;
        }

    }

    //functions
    funcexunit<3, 1> sandfall;

    sandfall.cond1 = issimplefallable;
    sandfall.func.doupdatesg({
        { FLOATING, { {0,1},{0,-1} }},
        { FALLING, { {-1,1},{-1,-1},{-1,0}}},
        });
    //cout << sandfall.func.toupdatesg.toupdates[1].size();

    sandfall.func.addell(
        { 1, 0 },
        {
        { FALLING, {{1,0}} },
        { FLOATING, {{1,0}} },
        { TERMAL, {{1,0}} },
        },
        { {isair,{1,0}} },
        true);

    sandfall.func.addell(
        { 1, 1 },
        {
        {FALLING, { {1,1} }},
        { FLOATING, {{1,1}} },
        { TERMAL, {{1,1}} },
        },
        { {isair,{1,1}},{isair,{0,1}} },
        true);

    sandfall.func.addell(
        { 1, -1 },
        {
        {FALLING, { {1,-1} } },
        {FLOATING, {{1,-1}} },
        {TERMAL, {{1,-1}} },
        },
        { {isair,{1,-1}},{isair,{0,-1}} },
        true);




    funcexunit<2, 1> waterfall;
    waterfall.cond1 = issimplefloatable1;
    waterfall.func.doupdatesg({
        { FLOATING, { {0,1},{0,-1} }},
        { FALLING, { {-1,1},{-1,-1},{-1,0}}},
        });

    waterfall.func.addell(
        { 0, 1 },
        { { TERMAL, {{0,1}} },
        { FLOATING, {{0,1}} },
        { FALLING, {{0,1}} }, },
        { {isair,{0,1}},{issimplefloatable,{1,0}} },
        true);

    waterfall.func.addell(
        { 0, -1 },
        {
        { TERMAL, {{0,-1}} },
        { FLOATING, {{0,-1}} },
        { FALLING, {{0,-1}} },
        },
        { {isair,{0,-1}},{issimplefloatable,{1,0}} },
        true);


    vector<U> temp1 = {};
    U* a = new U;
    temp1.push_back(*a);

    vector<U> temp4 = {};
    temp4.push_back(*a);
    temp4.push_back(*a);
    temp4.push_back(*a);
    temp4.push_back(*a);

    funcexunit<3, 4> termal;
    termal.cond1 = instvoid1;
    termal.func.doupdatesg({
        { TERMAL, {{0,0}} },
        });

    temp4[0].fd = termalexcange;
    temp4[1].fd = termalexcange;
    temp4[2].fd = termalexcange;
    temp4[3].fd = termalexcange;
    termal.func.addell(
        { {{0,1},{5}},{{0,-1},{5}},{{1,0},{5}},{{-1,0},{5}} },
        temp4,
        {},
        {},
        false,
        true
    );
    temp1[0].i = melt;
    termal.func.addell(
        { {{0,0},{1}} },
        temp1,
        { {EVERYTHING, { {0,0} } } },
        { {canmelt,{0,0}} },
        true
    );
    temp1[0].i = solidify;
    termal.func.addell(
        { {{0,0},{1}} },
        temp1,
        { {EVERYTHING, { {0,0} } } },
        { {cansolidify,{0,0}} },
        true
    );

    vector<U> temp2 = {};
    temp2.push_back(*a);
    temp2.push_back(*a);



    funcexunit<5, 2> charge;
    charge.cond1 = ischarge1;
    charge.func.doupdatesg(
    { 
    {ELCOLDOWNS, { {0,0} } },
    {CLOSEGATE, { {0,1} } },
    {CLOSEGATE, { {0,-1} } },
    {CLOSEGATE, { {1,0} } },
    {CLOSEGATE, { {-1,0} } },

    });

    temp1[0].b = charging;

    charge.func.addell(
        { {{0,1},{0}} },
        temp1,
        { {ELECTRISITY, { {0,1} }} },
        { {inconductor,{0,1}} }
    );
    charge.func.addell(
        { {{0,-1},{0}} },
        temp1,
        { {ELECTRISITY, { {0,-1} }}},
        { {inconductor,{0,-1}} }
    );
    charge.func.addell(
        { {{1,0},{0}} },
        temp1,
        { {ELECTRISITY, { {1,0} }}},
        { {inconductor,{1,0}} }
    );
    charge.func.addell(
        { {{-1,0},{0}} },
        temp1,
        { {ELECTRISITY, { {-1,0} }}},
        { {inconductor,{-1,0}} }
    );

    temp2[0].b = discharging;
    temp2[1].b = coolcharging;
    charge.func.addell(
        { {{0,0},{0}},{{0,0},{0}} },
        temp2,
        {},
        {}
    );

    temp1[0].b = discoolcharging;
    funcexunit<1, 1> discoolcharge;
    discoolcharge.cond1 = iscoolcharge1;
    discoolcharge.func.addell(
        { {{0,0},{0}} },
        temp1,
        {},
        {}
    );
    //arr[1][0] = new BasicMat;
    //arr[1][0]->type = COPPER;

    int gg = 0;
    int i = 0;
    auto frame = chrono::high_resolution_clock::now();
    auto endframe = chrono::high_resolution_clock::now();
    pairset updateset(COL, ROW);
    vector<updatee> changeset;

    BasicMat Examplesand;
    Examplesand.type = SAND;

    BasicMat Examplewater;
    Examplewater.type = WATER;

    Counuctor hotiron;
    hotiron.type = IRON;
    hotiron.t = 1999;

    Counuctor electroiron;
    electroiron.type = IRON;
    electroiron.charge = true;

    //d
    //auto before = chrono::high_resolution_clock::now();
    while (!gg) {
        frame = chrono::high_resolution_clock::now();
        if (!(i % SKIPFRAMES)) {
            //d
            //printboardtemprature(arr, COL, ROW);
            printboard(arr, COL, ROW);
        }
        update(arr, COL, ROW, updateset, termal, changeset, TERMAL, true);
        update(arr, COL, ROW, updateset, discoolcharge, changeset, ELCOLDOWNS);
        update(arr, COL, ROW, updateset, charge, changeset, ELECTRISITY);
        gateclose(arr, COL, ROW, updateset, gatearr);
        gateopen(arr, COL, ROW, updateset, gatearr);
        gateupdate(COL, ROW, updateset, gatearr);

        applychangeset(arr, COL, ROW, changeset);

        update(arr, COL, ROW, updateset, sandfall, changeset, FALLING);
        update(arr, COL, ROW, updateset, waterfall, changeset, FLOATING);

        applychangeset(arr, COL, ROW, changeset);
        //pointsetBasicMat(arr, COL, ROW, 3, 3, { FALLING }, updateset, Examplesand);
        //pointsetBasicMat(arr, COL, ROW, 3, 13, { WATERFALL }, updateset, Examplewater);
        pointsetBasicMat(arr, COL, ROW, 2, 9, { TERMAL }, updateset, hotiron);
        pointsetBasicMat(arr, COL, ROW, 30, 1, { ELECTRISITY }, updateset, electroiron);
        updateset.refresh();
        endframe = chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::microseconds(1000000 / FRAMERATE - (chrono::duration_cast<chrono::microseconds>(endframe - frame).count())));
        
        //d
        //if (i == 8) {
        //    auto end = chrono::high_resolution_clock::now();
        //    cout << "time:" << chrono::duration_cast<chrono::microseconds>(end - before).count() << endl;
        //}
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
