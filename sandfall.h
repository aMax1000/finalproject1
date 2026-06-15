#pragma once
#include <vector>
#include "basicslib.h"
#include "constdata.h"
#include "safepixel1,2,5.h"


template <int Size, int Funcsize>
void gateopen(Pixel*** arr, int col, int row,
    pairset& pairupdateset,
    funcexunit<Size, Funcsize>& funcs, vector<updatee>& changeset, updatesets whatupdetesetuse) {
    for (pair<int, int> n : pairupdateset.os[whatupdetesetuse]) {
        if (funcs.cond1(arr[n.first][n.second])) {
            swap(arr[n.first][n.second],gatearr[n.first][n.second]);
        }
    }
}
template <int Size, int Funcsize>
void gateclose(Pixel*** arr, int col, int row,
    pairset& pairupdateset,
    funcexunit<Size, Funcsize>& funcs, vector<updatee>& changeset, updatesets whatupdetesetuse) {
    for (pair<int, int> n : pairupdateset.os[whatupdetesetuse]) {
        if (funcs.cond1(arr[n.first][n.second])) {
            arr[n.first][n.second]=new Counductor;
        }
    }
}
