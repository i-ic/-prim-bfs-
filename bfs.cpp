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
void bfs(void);
void drawShortestPath(block* start, block* end);

void drawShortestPath(block* start, block* end) {
    block* current = end;
    while (current != start) {
        blockColor(current->x, current->y, shortestPath);
        current = myprev[current->x][current->y];
        FlushBatchDraw();
    }
}
void bfs(void)
{
    std::queue<block*> bfsQueue;
    int cnt = 1920;
    COLORREF bfsPath = RGB(190,190,cnt / 10);
    block* start = new block(1, 1);
    block* end = new block(BLOCK_WIDTH - 1, BLOCK_HEIGHT - 1);
    bfsQueue.push(start);
    mciSendString(_T("open portal.mp3 alias bkmusic2"), NULL, 0, NULL);
    mciSendString(_T("play bkmusic2 repeat"), NULL, 0, NULL);
    while (!bfsQueue.empty()) {
        block* current = bfsQueue.front();
        bfsQueue.pop();
        if (current->x == end->x && current->y == end->y) {
            drawShortestPath(start, end);
            mciSendString(_T("close bkmusic2"), NULL, 0, NULL);
            blockColor(1, 1, beginPoint);
            blockColor(BLOCK_WIDTH - 1, BLOCK_HEIGHT - 1, endPoint);
            FlushBatchDraw();
            return;
        }
        for (int i = 0; i < 4; ++i) {
            if (current->x + dir1[i][0] > 0 && current->y + dir1[i][1] > 0 && 
                current->x + dir1[i][0] < BLOCK_WIDTH && current->y + dir1[i][1] < BLOCK_HEIGHT &&
                map[current->x + dir1[i][0]][current->y + dir1[i][1]] == 0 && 
                myprev[current->x + dir1[i][0]][current->y + dir1[i][1]] == nullptr){
                    block* temp = new block(current->x + dir1[i][0], current->y + dir1[i][1]);
                    myprev[temp->x][temp->y] = current;
                    bfsQueue.push(temp);
                    cnt++;
                    bfsPath = RGB(max(50,190 - (cnt / 50)),max(50, 190 - (cnt / 50)), min(255, cnt / 10));
                    blockColor(temp->x, temp->y, bfsPath);
                    FlushBatchDraw();
            }
        }
    }
    exit(1);
}