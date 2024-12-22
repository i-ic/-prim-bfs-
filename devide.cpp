#include <graphics.h>
#include "initset.h"
#include "bits/stdc++.h"
#include <random>

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
void crossinit(void);
void crossDivide(int x1, int y1, int x2, int y2);
void reDarw(void);

void crossinit(void) {
    openlist.clear();
    for (int y = 1; y <= BLOCK_HEIGHT; y++) {
        for (int x = 1; x <= BLOCK_WIDTH; x++) {
            map[x][y] = 0;
            myprev[x][y] = nullptr;
        }
    }
    for (int y = 0; y <= BLOCK_HEIGHT; y++) {
        map[0][y] = 1;
        map[BLOCK_WIDTH][y] = 1;
    }
    for (int x = 1; x <= BLOCK_WIDTH; x++) {
        map[x][0] = 1;
        map[x][BLOCK_HEIGHT] = 1;
    }
    reDarw();
    mciSendString(_T("open orb.mp3 alias bkmusic1"), NULL, 0, NULL);
    mciSendString(_T("play bkmusic1 repeat"), NULL, 0, NULL);
    crossDivide(0, 0, BLOCK_WIDTH, BLOCK_HEIGHT);
    reDarw();
    mciSendString(_T("close bkmusic1"), NULL, 0, NULL);
}

int randRange(int s, int e) {
    if (s == e) return e;
    return rand() % (e - s + 1) + s;
}

void crossDivide(int x1, int y1, int x2, int y2) {
    if (x2 - x1 <= 3 || y2 - y1 <= 3) return; 

    int vx = (randRange(x1 + 2, x2 - 2) | 1) - 1; 
    int hy = (randRange(y1 + 2, y2 - 2) | 1) - 1; 
    
    for (int x = x1 + 1; x <= x2 - 1; x++) {
        map[x][hy] = 1;
        blockColor(x, hy, wal);
    }
    FlushBatchDraw();

    for (int y = y1 + 1; y <= y2 - 1; y++) {
        map[vx][y] = 1;
        blockColor(vx, y, wal);
    }
    FlushBatchDraw();

    int xh1 = randRange(x1 + 1, vx - 1) | 1;
    int xh2 = randRange(vx + 1, x2 - 1) | 1;
    int yh1 = randRange(y1 + 1, hy - 1) | 1;
    int yh2 = randRange(hy + 1, y2 - 1) | 1;

    std::vector<int> randDirs = { 0, 1, 2, 3 };
    std::shuffle(randDirs.begin(), randDirs.end(), std::mt19937(std::random_device()()));

    for (int i = 0; i < 3; i++) {
        switch (randDirs[i]) {
        case 0:
            map[xh1][hy] = 0; 
            blockColor(xh1, hy, road);
            FlushBatchDraw();
            break;
        case 1:
            map[xh2][hy] = 0;
            blockColor(xh2, hy, road);
            FlushBatchDraw();
            break;
        case 2:
            map[vx][yh1] = 0;
            blockColor(vx,yh1, road);
            FlushBatchDraw();
            break;
        case 3:
            map[vx][yh2] = 0;
            blockColor(vx,yh2, road);
            FlushBatchDraw();
            break;
        }
    }

    crossDivide(x1, y1, vx, hy);
    crossDivide(vx, y1, x2, hy);
    crossDivide(x1, hy, vx, y2);
    crossDivide(vx, hy, x2, y2);
}

