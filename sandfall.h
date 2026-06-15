#pragma once
#include <vector>
#include "basicslib.h"
#include "constdata.h"
#include "safepixel1,2,5.h"


void gateopen(Pixel*** arr, int col, int row, pairset& pairupdateset) {
    for (pair<int, int> n : pairupdateset.os[CLOSEGATE]) {
        if (arr[n.first][n.second]->type==GATE) {
            delete arr[n.first][n.second];
            arr[n.first][n.second] = new Void;
        }
    }
}
//template <int Size, int Funcsize>
//void gateclose(Pixel*** arr, int col, int row,
//    pairset& pairupdateset,
//    funcexunit<Size, Funcsize>& funcs, vector<updatee>& changeset, updatesets whatupdetesetuse) {
//    for (pair<int, int> n : pairupdateset.os[whatupdetesetuse]) {
//        if (funcs.cond1(arr[n.first][n.second])) {
//            arr[n.first][n.second]=new Counductor;
//        }
//    }
//}
