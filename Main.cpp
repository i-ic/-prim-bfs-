#include <graphics.h>
#include "initset.h"
#include "bits/stdc++.h"
#pragma comment(lib,"Winmm.lib")

struct block {
public:
    int x;
    int y;
    block(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

int map[BLOCK_WIDTH + 10][BLOCK_HEIGHT + 10];
std::vector<block*> openlist;
std::vector<block*> list;
block* myprev[BLOCK_WIDTH + 10][BLOCK_HEIGHT + 10]; 

void blockColor(int x, int y, COLORREF RGB);
void priminit(void);
void kruskalinit(void);
void dfsinit(void);
void crossinit(void);
void wilsoninit(void);
void reDarw(void);
void dfs(void);
void bfs(void);
void menu(void);

void blockColor(int x, int y, COLORREF RGB) {
    setfillcolor(RGB); setlinecolor(COLORREF RGB(0, 0, 0));
    fillrectangle(x * BLOCK_XY, y * BLOCK_XY, BLOCK_XY + x * BLOCK_XY, BLOCK_XY + y * BLOCK_XY);
}

void reDarw(void) {
    for (int y = 0; y <= BLOCK_HEIGHT; y++) {
        for (int x = 0; x <= BLOCK_WIDTH; x++) {
            if (map[x][y] == 1) {
                blockColor(x, y, wal);
            }
            else if (map[x][y] == 2) {
                blockColor(x, y, wal);
            }
            else {
                blockColor(x, y, road);
            }
        }
    }
    FlushBatchDraw();
}


int main(void) {
    srand((unsigned)time(NULL));
    menu();
    while (1);
}

void menu()
{
    printf("*****************************************************\n");
    printf("*           ��ӭʹ������Թ���������� V2.0         *\n");
    printf("*****************************************************\n");
    printf("*                ��ѡ���Թ��������㷨               *\n");
    printf("*****************************************************\n");
    printf("*                 1 �����prim�㷨                  *\n");
    printf("*                 2 �����kruskal�㷨               *\n");
    printf("*                 3 ������������㷨                *\n");
    printf("*                 4 ʮ�ֵݹ黮���㷨                *\n");
    printf("*                 5 wilson�㷨������������ߣ�      *\n");
    printf("*****************************************************\n");
    printf("ѡ��Ҫ���еĲ���\n");
    int operate = -1;
    int operateSolve = -1;
    std::cin >> operate;
    system("cls");
    if (operate >= 1 && operate <= 3) {
        printf("*****************************************************\n");
        printf("*           ��ӭʹ������Թ���������� V2.0         *\n");
        printf("*****************************************************\n");
        printf("*                ��ѡ���Թ�������㷨               *\n");
        printf("*****************************************************\n");
        printf("*                 1 ������������㷨���Ƽ���        *\n");
        printf("*                 2 ������������㷨                *\n");
        printf("*****************************************************\n");
        printf("ѡ��Ҫ���еĲ���\n");
        std::cin >> operateSolve;
    }
    else if (operate >= 4 && operate <= 5) {
        printf("*****************************************************\n");
        printf("*           ��ӭʹ������Թ���������� V2.0         *\n");
        printf("*****************************************************\n");
        printf("*                ��ѡ���Թ�������㷨               *\n");
        printf("*****************************************************\n");
        printf("*                 1 ������������㷨                *\n");
        printf("*                 2 ������������㷨���Ƽ���        *\n");
        printf("*****************************************************\n");
        printf("ѡ��Ҫ���еĲ���\n");
        std::cin >> operateSolve;
    }
    else {
        exit(1);
    }
    if (operateSolve != 1 && operateSolve != 2) {
        exit(1);
    }
    system("cls");
    initgraph(WIDTH + BLOCK_XY, HEIGHT + BLOCK_XY);
    BeginBatchDraw();
    cleardevice();
    mciSendString(_T("open levelup.mp3 alias bkmusic"), NULL, 0, NULL);
    mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
    Sleep(1000);
    mciSendString(_T("close bkmusic"), NULL, 0, NULL);
    blockColor(1, 1, beginPoint);
    blockColor(BLOCK_WIDTH - 1, BLOCK_HEIGHT - 1, endPoint);
    FlushBatchDraw();
    switch (operate)
    {
        case 1:
            priminit();
            break;
        case 2:
            kruskalinit();
            break;
        case 3:
            dfsinit();
            break;
        case 4:
            crossinit();
            break;
        case 5:
            wilsoninit();
            break;
    }
    switch (operateSolve)
    {
        case 1:
            dfs();
            break;
        case 2:
            bfs();
            break;
    }
}