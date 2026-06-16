#pragma once
#include <vector>
#include "basicslib.h"
#include "constdata.h"
#include "safepixel1,2,5.h"


void gateopen(Pixel*** arr, int col, int row, pairset& pairupdateset, signed char** gatearr) {
    for (pair<int, int> n : pairupdateset.os[CLOSEGATE]) {
        if (arr[n.first][n.second]->type == GATE and arr[n.first][n.second]->getbit(POWER) and gatearr[n.first][n.second] == 0) {
            delete arr[n.first][n.second];
            arr[n.first][n.second] = new Void;
            gatearr[n.first][n.second] = 3;
            pairupdateset.ns[GATEUPDATE].push_back(n);
        }
    }
}
void gateclose(Pixel*** arr, int col, int row, pairset& pairupdateset, signed char** gatearr) {
    for (pair<int, int> n : pairupdateset.ns[CLOSEGATE].arr) {
        if (gatearr[n.first][n.second] == 1) {
            delete arr[n.first][n.second];
            arr[n.first][n.second] = new Counuctor;
            arr[n.first][n.second]->type=GATE;
            gatearr[n.first][n.second] = 2;
            pairupdateset.ns[GATEUPDATE].push_back(n);
        }
    }
}
void gateupdate(int col, int row, pairset& pairupdateset, signed char** gatearr) {
    for (pair<int, int> n : pairupdateset.os[GATEUPDATE]) {
       gatearr[n.first][n.second] -= 2;
    }
}
