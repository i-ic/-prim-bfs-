#include <graphics.h>
#include "initset.h"
#include "bits/stdc++.h"
#pragma comment(lib,"Winmm.lib")

extern struct block {
public:
    int x;
    int y;
    block(int x, int y) {
        this->x = x;
        this->y = y;
    }
};


extern int map[BLOCK_WIDTH + 10][BLOCK_HEIGHT + 10];
extern std::vector<block*> openlist;
extern std::vector<block*> list;
extern block* myprev[BLOCK_WIDTH + 10][BLOCK_HEIGHT + 10]; 

void blockColor(int x, int y, COLORREF RGB);
void priminit(void);
void primAddList(int x, int y);
void reDarw(void);
void prim(void);
bool primThrough(int x, int y);

void priminit(void) {
    openlist.clear();
    for (int y = 0; y <= BLOCK_HEIGHT; y++) {
        for (int x = 0; x <= BLOCK_WIDTH; x++) {
            map[x][y] = 1;
            myprev[x][y] = nullptr;
        }
    }
    map[1][1] = 0;
    map[BLOCK_WIDTH - 1][BLOCK_HEIGHT - 1] = 0;
    reDarw();
    primAddList(1, 1);
    prim();
}

void prim(void) {
    mciSendString(_T("open orb.mp3 alias bkmusic1"), NULL, 0, NULL);
    mciSendString(_T("play bkmusic1 repeat"), NULL, 0, NULL);
    while (openlist.size() > 0) {
        int Index = rand() % openlist.size();
        block* begin = openlist[Index];
        if (primThrough(begin->x, begin->y)) {
            map[begin->x][begin->y] = 0;
            primAddList(begin->x, begin->y);
            blockColor(begin->x, begin->y, road);
            FlushBatchDraw();
        }
        openlist.erase(openlist.begin() + Index);
    }
    for (int i = 0; i < 4; ++i) {
        primThrough(BLOCK_WIDTH - 1,BLOCK_HEIGHT - 1);
        primThrough(BLOCK_WIDTH - 3, BLOCK_HEIGHT - 3);
    }
    reDarw();
    mciSendString(_T("close bkmusic1"), NULL, 0, NULL);
}

bool primThrough(int x, int y) {
    list.clear();
    for (int i = 0; i < 4; ++i) {
        if (y + dir2[i][1] > 0 && x + dir2[i][0] > 0 && 
            y + dir2[i][1] < BLOCK_HEIGHT && x + dir2[i][0] < BLOCK_WIDTH &&
            map[x + dir2[i][0]][y + dir2[i][1]] == 0) {
                block* temp = new block(x + dir1[i][0], y + dir1[i][1]);
                list.push_back(temp);
        }
    }
    if (list.size() != 0) {
        int Index = rand() % list.size();
        block* A = list[Index];
        map[A->x][A->y] = 0;
        blockColor(A->x, A->y, road);
        FlushBatchDraw();
        return true;
    } else {
        return false;
    }
}

void primAddList(int x, int y) {
    for (int i = 0; i < 4; ++i) {
        if (x + dir2[i][0] > 0 && y + dir2[i][1] > 0 &&
            x + dir2[i][0] < BLOCK_WIDTH && y + dir2[i][1] < BLOCK_HEIGHT &&
            map[x + dir2[i][0]][y + dir2[i][1]] == 1) {
                block* temp = new block(x + dir2[i][0], y + dir2[i][1]);
                openlist.push_back(temp);
                map[x + dir2[i][0]][y + dir2[i][1]] = 2;
        }
    }
}

