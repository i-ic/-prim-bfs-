/* ������ */

#include <graphics.h>
#include <Windows.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <queue>
#include <conio.h>
#pragma comment(lib,"Winmm.lib")//������Ч����api

using namespace std;

#define WIDTH 1080//�ֱ���
#define HEIGHT 720
#define BLOCK_XY 24//С����߳�
const int BLOCK_WIDTH = WIDTH / (BLOCK_XY);//С����x������ 
const int BLOCK_HEIGHT = HEIGHT / (BLOCK_XY);//С����y������

#define lu COLORREF RGB(220,220,220)//·����ɫ
#define qiangbi COLORREF RGB(30,30,30)//ǽ����ɫ
#define qidian COLORREF RGB(0,255,0)//�����ɫ
#define zhongdian COLORREF RGB(255,0,0)//�յ���ɫ
#define xuanzhong COLORREF RGB(190,50,50)//ѡ����ɫ
#define bfsPath COLORREF RGB(200,200,255)//BFS·����ɫ
#define shortestPath COLORREF RGB(255,255,0)//���·����ɫ

struct block 
{
public:
    int x;
    int y;
    block(int x, int y) 
    {
        this->x = x;
        this->y = y;
    }
};
//��ʾ��ͼ�еķ����Լ������λ��

int map[BLOCK_WIDTH][BLOCK_HEIGHT];
vector<block*> openlist;//��ѡ�б�
vector<block*> list;// ����һ�����ڴ洢��Χ·�ڵ���б�
block* myprev[BLOCK_WIDTH][BLOCK_HEIGHT]; 
/* ���ڼ�¼���ڵ㣬ͬʱ��������bfsѰ�����·�� */

// ��������
void clearscreen(COLORREF RGB);//������ͼ���ҳ�ʼ����ͼ��ɫ
void BLOCK_color(int x, int y, COLORREF RGB);//��x��yλ�û���ɫΪRGB�ķ���
void init(void);//��ʼ��
void add_list(int x, int y);//��x,y���ܲ���·�Ľڵ�����ѡ�б�
void redarw(void);//ˢ����Ļ
void prim(void);//prim��ѭ��
void through(int x, int y);//��x,y��������һ������Ѿ����·�Ľڵ��ͨ
void bfs(void); //BFSѰ��·��
void drawShortestPath(block* start, block* end); //����·��

void clearscreen(COLORREF RGB) 
{
    for (int y = 0; y < BLOCK_HEIGHT; y++) 
    {
        for (int x = 0; x < BLOCK_WIDTH; x++) 
        {
            BLOCK_color(x, y, RGB);
        }
    }
}

void BLOCK_color(int x, int y, COLORREF RGB) 
{
    setfillcolor(RGB); setlinecolor(COLORREF RGB(0, 0, 0));
    fillrectangle(x * BLOCK_XY, y * BLOCK_XY, BLOCK_XY + x * BLOCK_XY, BLOCK_XY + y * BLOCK_XY);
}

int main(void) 
{
    srand((unsigned)time(NULL)); //���������
    initgraph(WIDTH, HEIGHT);//������ͼ����
    BeginBatchDraw();
    cleardevice();//�����ʾ
    init();//�����򣬳�ʼ���Թ����Զ���ʼ����
    mciSendString(_T("open levelup.mp3 alias bkmusic"), NULL, 0, NULL);//������Ч
    mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//ѭ������
    Sleep(1000);
    mciSendString(_T("close bkmusic"), NULL, 0, NULL);//ֹͣ����
    BLOCK_color(1, 1, qidian);
    BLOCK_color(BLOCK_WIDTH - 2, BLOCK_HEIGHT - 2, zhongdian);
    FlushBatchDraw();//��������
    while (1);//���ִ��ڲ����ر�
}
