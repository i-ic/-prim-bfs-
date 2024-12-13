/* ������ */

#include <graphics.h>
#include "initset.h"
#include "bits/stdc++.h"
#pragma comment(lib,"Winmm.lib")//������Ч����api

struct block {
public:
    int x;
    int y;
    block(int x, int y) {
        this->x = x;
        this->y = y;
    }
};
//��ʾ��ͼ�еķ����Լ������λ��

int map[BLOCK_WIDTH + 10][BLOCK_HEIGHT + 10];
std::vector<block*> openlist;//��ѡ�б�
std::vector<block*> list;// ����һ�����ڴ洢��Χ·�ڵ���б�
block* myprev[BLOCK_WIDTH + 10][BLOCK_HEIGHT + 10]; 
/* ���ڼ�¼���ڵ㣬ͬʱ��������bfsѰ�����·�� */

// ��������
void clearScreen(COLORREF RGB);//������ͼ���ҳ�ʼ����ͼ��ɫ
void blockColor(int x, int y, COLORREF RGB);//��x��yλ�û���ɫΪRGB�ķ���
void init(void);//��ʼ��

void clearScreen(COLORREF RGB) { //��ͼ,���Ӷ�n*m
    for (int y = 0; y <= BLOCK_HEIGHT; y++) {
        for (int x = 0; x <= BLOCK_WIDTH; x++) {
            blockColor(x, y, RGB);
        }
    }
}

void blockColor(int x, int y, COLORREF RGB) {
    setfillcolor(RGB); setlinecolor(COLORREF RGB(0, 0, 0));
    fillrectangle(x * BLOCK_XY, y * BLOCK_XY, BLOCK_XY + x * BLOCK_XY, BLOCK_XY + y * BLOCK_XY);
}

int main(void) {
    srand((unsigned)time(NULL)); //���������
    initgraph(WIDTH + BLOCK_XY, HEIGHT + BLOCK_XY);//������ͼ����
    BeginBatchDraw();
    cleardevice();//�����ʾ
    init();//�����򣬳�ʼ���Թ����Զ���ʼ����
    mciSendString(_T("open levelup.mp3 alias bkmusic"), NULL, 0, NULL);//������Ч
    mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//ѭ������
    Sleep(1000);
    mciSendString(_T("close bkmusic"), NULL, 0, NULL);//ֹͣ����
    blockColor(1, 1, beginPoint);
    blockColor(BLOCK_WIDTH - 1, BLOCK_HEIGHT - 1, endPoint);
    FlushBatchDraw();//��������
    while (1);//���ִ��ڲ����ر�
}
