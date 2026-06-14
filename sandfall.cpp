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

static bool isair(Pixel* a, Pixel* b) {
    return (a)->getint(TYPEV) == VOIDM;
}
static bool issimplefallable(Pixel* a) {
    return constb(a->type,IS_SIMPLEFALLABLE);
}
static bool issimplefloatable1(Pixel* a) {
    return constb(a->type, IS_SIMPLEFLOATABLE);
}
static bool issimplefloatable(Pixel* a, Pixel* b) {
    return constb(a->type, IS_SIMPLEFLOATABLE);
}
static Changefd termalexcange(Pixel* a, Pixel* b) {
    float ret = (a->getfloat(TEMPRATURE)-b->getfloat(TEMPRATURE))
        *constf((a->type), THERMAL_CONDUCIVITY) * constf((b->type), THERMAL_CONDUCIVITY);
    //cout << "datepre: " << ret << endl;
    return { TEMPRATURE,ret};
}
static Changei melt(Pixel* a, Pixel* b) {
    //cout << "melt_type: " << consti(a->type, MELT_TYPE) << endl;
    return { TYPEV,consti(a->type,MELT_TYPE)};
}
static Changei solidify(Pixel* a, Pixel* b) {
    return { TYPEV,consti(a->type,SOLID_TYPE)};
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

char displaypixel(Pixel* a) {
    switch (a->type) {
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
    default:
        std::cout << "UNDISPLAYABLE PIXEL";
        return ' ';
    }

};

static void printboard(Pixel*** arr, int COL, int ROW) {
    string output;
    for (int i = 0; COL > i; i++) {
        for (int j = 0; ROW > j; j++) {
            output += displaypixel(arr[i][j]);
            output += ' ';
        }
        output += "| \n";
    }
    for (int j = 0; ROW > j; j++) {
        output += "--";
    }
    output += "\n";
    //std::system("cls");
    cout << output;
    output.clear();
}
static void printboardtemprature(Pixel*** arr, int COL, int ROW) {
    for (int i = 0; COL > i; i++) {
        for (int j = 0; ROW > j; j++) {
            cout<< ((arr[i][j]->getfloat(TEMPRATURE)));
            cout << ' ';
        }
        cout << "| \n";
    }
    for (int j = 0; ROW > j; j++) {
        cout << "--";
    }
    cout << endl;
}


static void pointsetBasicMat(Pixel*** arr, int COL, int ROW, int x, int y, vector<updatesets> a, pairset& updateset, BasicMat b) {
    delete arr[x & maskx][y & masky];
    arr[x & maskx][y & masky] = new BasicMat{ b };
    for (updatesets k : a) {
        updateset.ns[k].push_back({ x & maskx,y & masky });
    }
}





int main()
{



    int COL = pow(2, 4);
    int ROW = pow(2, 4);
    constexpr auto FRAMERATE = 2;

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
    //for (int i = 0; i < COL; i += 2) {
    //    for (int j = 0; j < ROW; j++) {
    //        arr[i][j] = new BasicMat;
    //        arr[i][j]->type = SAND;
    //    }
    //}

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

    for (int i = 0; i < COL-1; i++) {
        for (int j = 0; j < 3; j++) {
            arr[i][j] = new BasicMat;
            arr[i][j]->type = COPPER;
        }

    }

    //update templates
    //vector<pair<int, int>> cross;
    //cross.push_back({ 0, 0 });
    //cross.push_back({ 1, 0 });
    //cross.push_back({ -1, 0 });
    //cross.push_back({ 0, 1 });
    //cross.push_back({ 0, -1 });

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
        { TERMAL, {{1,0}} },
        },
        { {isair,{1,0}} },
        true);

    sandfall.func.addell(
        { 1, 1 },
        { 
        {FALLING, { {1,1} }}, 
        { TERMAL, {{1,1}} },
        },
        { {isair,{1,1}},{isair,{0,1}} },
        true);

    sandfall.func.addell(
        { 1, -1 },
        { 
        {FALLING, { {1,-1} } }, 
        { TERMAL, {{1,-1}} },
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
        { { TERMAL, {{0,1}} }, },
        { {isair,{0,1}},{issimplefloatable,{1,0}} },
        true);

    waterfall.func.addell(
        { 0, -1 },
        { { TERMAL, {{0,-1}} }, },
        { {isair,{0,-1}},{issimplefloatable,{1,0}} },
        true);
    
    funcexunit<6, 1> termal;
    termal.cond1 = instvoid1;
    termal.func.doupdatesg({
        { TERMAL, {{0,0}} },
        });

    vector<U> temp2 = {};
    U* a = new U;
    temp2.push_back(*a);
    temp2[0].fd=termalexcange;
    termal.func.addell(
        { {{0,1},{5}} },
        temp2,
        {},
        {},
        false,
        true
        );
    termal.func.addell(
        { {{0,-1},{5}} },
        temp2,
        {},
        {},
        false,
        true
        );
    termal.func.addell(
        { {{1,0},{5}} },
        temp2,
        {},
        {},
        false,
        true
        );
    termal.func.addell(
        { {{-1,0},{5}} },
        temp2,
        {},
        {},
        false,
        true
        );

    temp2[0].i = melt;
    termal.func.addell(
        { {{0,0},{1}} },
        temp2,
        { {EVERYTHING, { {0,0} } } },
        { {canmelt,{0,0}} },
        true
    );
    temp2[0].i = solidify;
    termal.func.addell(
        { {{0,0},{1}} },
        temp2,
        { {EVERYTHING, { {0,0} } } },
        { {cansolidify,{0,0}} },
        true
    );



    int gg = 0;
    int i = 0;
    auto frame = chrono::high_resolution_clock::now();
    auto endframe = chrono::high_resolution_clock::now();
    BasicMat Examplesand;
    Examplesand.type = SAND;
    BasicMat Examplewater;
    Examplewater.type = WATER;
    BasicMat hotiron;
    hotiron.type = IRON;
    hotiron.t = 999;

    pairset updateset(UPDATESETCOUNT.count, COL, ROW);
    //for (int i = 0; i < 10; i++) {
    //    updateset.os.push_back({});
    //}

    vector<updatee> changeset;

    auto before = chrono::high_resolution_clock::now();
    while (!gg) {
        frame = chrono::high_resolution_clock::now();
        //printboardtemprature(arr, COL, ROW);
        printboard(arr, COL, ROW);
        //vector<funcexunit<3, 1>> temp = {sandfall};
        update(arr, COL, ROW, updateset, termal, changeset, TERMAL);
        update(arr, COL, ROW, updateset, sandfall, changeset, FALLING);
        //vector<funcexunit<5, 1>> temp2 = {waterfall};
        update(arr, COL, ROW, updateset, waterfall, changeset, FLOATING);
        
        applychangeset(arr, COL, ROW, changeset);
        //pointsetBasicMat(arr, COL, ROW, 3, 3, { FALLING }, updateset, Examplesand);
        //pointsetBasicMat(arr, COL, ROW, 3, 13, { WATERFALL }, updateset, Examplewater);
        pointsetBasicMat(arr, COL, ROW, 0, 1, { TERMAL }, updateset, hotiron);
        updateset.refresh();

        endframe = chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::microseconds(1000000 / FRAMERATE - (chrono::duration_cast<chrono::microseconds>(endframe - frame).count())));

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
