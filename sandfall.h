#pragma once
#include <vector>
#include "basicslib.h"
#include "constdata.h"
#include "safepixel1,2,5.h"
#include "BMPreader.h"


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




void pixeltopixel(Pixelbmp a, Pixel*& b) {
    if(a.a>0){
        switch ((a.b) + ((a.g) << 8) + ((a.r) << 16))
        {
        case 0xFFD898:
            delete b;
            b = new BasicMat;
            b->type = SAND;
            break;
        case 0xC0CCD6:
            delete b;
            b = new Counuctor;
            b->type = IRON;
            //cout << 'I';
            break;
        case 0xC8481E:
            delete b;
            b = new Counuctor;
            b->type = COPPER;
            break;
        case 0x000000:
            delete b;
            b = new BasicMat;
            b->type = BEDROCK;
            break;
        case 0x78B4E9:
            delete b;
            b = new BasicMat;
            b->type = WATER;
            break;
        case 0xFF7326:
            delete b;
            b = new BasicMat;
            b->type = MOLTEN_IRON;
            break;
        case 0xFF9926:
            delete b;
            b = new BasicMat;
            b->type = MOLTEN_COPPER;
            break;
        case 0x82919D:
            delete b;
            b = new Counuctor;
            b->type = GATE;
            break;
        default:
            break;
        }
    }
}

void pictoarr(vector<vector<Pixelbmp>>& pic, Pixel***& arr, int COL, int ROW) {
    if ((pic.size() != COL) or pic[0].size() != ROW) cout << "PIC AND BOARD NOT THE SAME SIZE";
    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < ROW; j++) {
          pixeltopixel(pic[i][j], arr[i][j]);
          //print(pic[i][j]);
          //cout << arr[i][j]->type<<'\n';
        }
    }
}
