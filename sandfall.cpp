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
#include "Header.h"
bool isair(Pixel* a, Pixel* b) {
    return (a)->getint(TYPEV) == VOIDM;
}
bool issand1(Pixel* a) {
    return (a)->getint(TYPEV) == SAND;
}
bool iswater1(Pixel* a) {
    return (a)->getint(TYPEV) == WATER;
}
bool iswater(Pixel* a, Pixel* b) {
    return (a)->getint(TYPEV) == WATER;
}
Changeb testf(Pixel* a, Pixel* b) {
    return { 0 };
}
void printboard(Pixel*** arr, int COL, int ROW) {
    string output;
    for (int i = 0; COL > i; i++) {
        for (int j = 0; ROW > j; j++) {
                output+=static_cast<char>((arr[i][j]->getint(TYPEV)));
                if (output.back() == '\0') {
                    output.pop_back();
                    output += ' ';
                }
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

void pointsetBasicMat(Pixel*** arr, int COL, int ROW,int x,int y,vector<updatesets> a, pairset& updateset, BasicMat b) {
    delete arr[x & maskx][y & masky];
    arr[x & maskx][y & masky] = new BasicMat{b};
    for (updatesets k : a) {
        updateset.ns[k].push_back({ x & maskx,y & masky });
    }
}





int main()
{
    int COL = pow(2, 4);
    int ROW = pow(2, 4);
    constexpr auto FRAMERATE = 20;

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
    for (int j = 1; j < 5; j++) {
        arr[10][j] = new BasicMat;
        arr[10][j]->type = BEDROCK;
    }
    for (int j = 10; j < 16; j++) {
        arr[10][j] = new BasicMat;
        arr[10][j]->type = BEDROCK;
    }
    for (int i = 0; i < COL; i++) {
        arr[i][0] = new BasicMat;
        arr[i][0]->type = BEDROCK;
    }
    for (int i = 0; i < COL; i++) {
        arr[i][6] = new BasicMat;
        arr[i][6]->type = BEDROCK;
    }
    for (int i = 0; i < COL; i++) {
        arr[i][8] = new BasicMat;
        arr[i][8]->type = BEDROCK;
    }
    for (int i = 0; i < COL; i++) {
        arr[i][15] = new BasicMat;
        arr[i][15]->type = BEDROCK;
    }

    //update templates
    vector<pair<int, int>> cross;
    cross.push_back({ 0, 0 });
    cross.push_back({ 1, 0 });
    cross.push_back({ -1, 0 });
    cross.push_back({ 0, 1 });
    cross.push_back({ 0, -1 });

    //functions
    funcexunit<3,1> sandfall;
    sandfall.func.addell(1, 0, {}, {{isair,{1,0}}}, true, false);
    sandfall.func.addell(1, 1, { {1,1} }, { {isair,{1,1}} }, true, false);
    sandfall.func.addell(1, -1, { {1,-1} }, { {isair,{1,-1}} }, true, false);
    sandfall.func.doupdatesg(cross);
    sandfall.nuscords = { SANDFALL };
    sandfall.cond1 = issand1;

    funcexunit<5, 1> waterfall;
    waterfall.func.addell(1, 0, {}, { {isair,{1,0}} }, true, false);
    waterfall.func.addell(1, 1, { {1,1} }, { {isair,{1,1}} }, true, false);
    waterfall.func.addell(1, -1, { {1,-1} }, { {isair,{1,-1}} }, true, false);
    waterfall.func.addell(0, 1, {}, { {isair,{0,1}},{iswater,{1,1}} }, true, false);
    waterfall.func.addell(0, -1, {}, { {isair,{0,-1}},{iswater,{1,-1}} }, true, false);
    waterfall.func.doupdatesg(cross);
    waterfall.nuscords = { SANDFALL };
    waterfall.cond1 = iswater1;


    int gg = 0;
    int i = 0;
    auto frame = chrono::high_resolution_clock::now();
    auto endframe = chrono::high_resolution_clock::now();
    BasicMat Examplesand;
    Examplesand.type = SAND;
    BasicMat Examplewater;
    Examplewater.type = WATER;

    pairset updateset(10, COL, ROW);
    for (int i = 0; i < 10; i++) {
        updateset.os.push_back({});
    }

    vector<updatesets> updatesets;
    updatesets.push_back(SANDFALL);
    vector<updatee> changeset;


    while (!gg) {


        printboard(arr, COL, ROW);
        frame = chrono::high_resolution_clock::now();
        //delete arr[0][5];
        //arr[0][5] = new BasicMat;
        //arr[0][5]->type = WATER;
        update(arr, COL, ROW, updateset, updatesets, sandfall, changeset);
        update(arr, COL, ROW, updateset, updatesets, waterfall, changeset);
        applychangeset(arr, COL, ROW, changeset);
        pointsetBasicMat(arr, COL, ROW, 3, 3, { SANDFALL }, updateset, Examplesand);
        pointsetBasicMat(arr, COL, ROW, 3, 13, { SANDFALL }, updateset, Examplewater);
        updateset.refresh();

        endframe = chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::microseconds(1000000/FRAMERATE-(chrono::duration_cast<chrono::microseconds>(endframe - frame).count())));

        //if (i == 32) {
        //    end = chrono::high_resolution_clock::now();
        //    cout << "time:" << chrono::duration_cast<chrono::microseconds>(end - before).count() << endl;
        //}
        //i++;
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
