/* ��С��������ʼ���������Թ� */

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
static const int BLOCK_WIDTH = WIDTH / (BLOCK_XY);//С����x������ 
static const int BLOCK_HEIGHT = HEIGHT / (BLOCK_XY);//С����y������ 

#define lu COLORREF RGB(220,220,220)//·����ɫ
#define qiangbi COLORREF RGB(30,30,30)//ǽ����ɫ
#define qidian COLORREF RGB(0,255,0)//�����ɫ
#define zhongdian COLORREF RGB(255,0,0)//�յ���ɫ
#define xuanzhong COLORREF RGB(190,50,50)//ѡ����ɫ

extern struct block {
public:
    int x;
    int y;
    block(int x, int y) {
        this->x = x;
        this->y = y;
    }
};
//��ʾ��ͼ�еķ����Լ������λ��

extern int map[BLOCK_WIDTH][BLOCK_HEIGHT];
extern vector<block*> openlist;//��ѡ�б�
extern vector<block*> list;
extern block* myprev[BLOCK_WIDTH][BLOCK_HEIGHT]; 
/* ���ڼ�¼���ڵ㣬ͬʱ��������bfsѰ�����·�� */

// ��������
void clearscreen(COLORREF RGB);//������ͼ���ҳ�ʼ����ͼ��ɫ
void BLOCK_color(int x, int y, COLORREF RGB);//��x��yλ�û���ɫΪRGB�ķ���
void init(void);//��ʼ��
void add_list(int x, int y);//��x,y���ܲ���·�Ľڵ�����ѡ�б�
void redarw(void);//ˢ����Ļ
void prim(void);//prim��ѭ��
void through(int x, int y);//��x,y��������һ������Ѿ����·��·���ͨ
void bfs(void); //BFSѰ��·��
void drawShortestPath(block* start, block* end); //����·��

void init(void) {
    openlist.clear();
        for (int y = 0; y < BLOCK_HEIGHT; y++)     // ��ͼ��ʼ��Ϊǽ
        {
            for (int x = 0; x < BLOCK_WIDTH; x++) 
            {
                map[x][y] = 1;
                myprev[x][y] = nullptr;
            }
        }
        map[1][1] = 0;    // ��ʼ����㡢�յ�
        map[BLOCK_WIDTH - 2][BLOCK_HEIGHT - 2] = 0;
        add_list(1, 1);        // ���ڵ���ӽڵ���ǽ�ڼ����ѡ�б�
    prim();
    bfs();
}

void prim(void) {
    mciSendString(_T("open orb.mp3 alias bkmusic1"), NULL, 0, NULL);//������Ч
    mciSendString(_T("play bkmusic1 repeat"), NULL, 0, NULL);//ѭ������
    while (openlist.size() > 0) //ֱ�����еĽڵ㶼�Ѿ������ʹ�
    {

        int Index = rand() % openlist.size();        // �Ӵ�ѡ�����ѡһ����ʼ�ڵ�
        block* kaishi = openlist[Index];        // ����ʼ�ڵ���������һ������Ѿ����·�Ľڵ��ͨ
        through(kaishi->x, kaishi->y);
        map[kaishi->x][kaishi->y] = 0;        // ����ʼ�ڵ���·
        add_list(kaishi->x, kaishi->y);        // ����ʼ�ڵ���ӽڵ��е�����ǽ�ڼ����ѡ�б�
        openlist.erase(openlist.begin() + Index);        // �Ӵ�ѡ·�����Ƴ���ʼ�ڵ�
        BLOCK_color(kaishi->x, kaishi->y, xuanzhong);
        FlushBatchDraw();
        redarw();
    }
    mciSendString(_T("close bkmusic1"), NULL, 0, NULL);//ֹͣ����
    openlist.clear();
    if (map[BLOCK_WIDTH - 1][BLOCK_HEIGHT - 2] == 1 || map[BLOCK_WIDTH - 2][BLOCK_HEIGHT - 1] == 1 || map[BLOCK_WIDTH - 3][BLOCK_HEIGHT - 2] == 1 || map[BLOCK_WIDTH - 2][BLOCK_HEIGHT - 3] || 1)
    {
        map[BLOCK_WIDTH - 3][BLOCK_HEIGHT - 3] = 0;map[BLOCK_WIDTH - 4][BLOCK_HEIGHT - 3] = 0;
        map[BLOCK_WIDTH - 5][BLOCK_HEIGHT - 3] = 0;map[BLOCK_WIDTH - 6][BLOCK_HEIGHT - 3] = 0;
        map[BLOCK_WIDTH - 6][BLOCK_HEIGHT - 2] = 0;map[BLOCK_WIDTH - 2][BLOCK_HEIGHT - 3] = 0;
        FlushBatchDraw();
        redarw();
    }
}

void through(int x, int y) 
{
    list.clear();
    // ����Ϸ��Ľڵ㣬�����·��������б�
    if (y - 2 >= 0 && map[x][y - 2] == 0) 
    {
        block* a = new block(x, y - 1);
        list.push_back(a);
    }
    //��
    if (y + 2 <= BLOCK_HEIGHT && map[x][y + 2] == 0) 
    {
        block* b = new block(x, y + 1);
        list.push_back(b);
    }
    //��
    if (x - 2 >= 0 && map[x - 2][y] == 0) 
    {
        block* c = new block(x - 1, y);
        list.push_back(c);
    }
    //��
    if (x + 2 <= BLOCK_WIDTH && map[x + 2][y] == 0) 
    {
        block* d = new block(x + 1, y);
        list.push_back(d);
    }
    int AIndexea = rand() % list.size();// ���б������ѡ��һ��·�ڵ�
    block* A = list[AIndexea];
    // ��x��y��A��ͨ
        map[A->x][A->y] = 0;
}

void add_list(int x, int y) 
{
    // ����Ϸ��Ľڵ㣬�����ǽ�ڣ����һ�û�б����뵽��ѡ�б��У���ô�ͽ������뵽��ѡ�б���
    if (y - 2 >= 0 && map[x][y - 2] == 1) 
    {
        block* a = new block(x, y - 2);
        openlist.push_back(a);
        map[x][y - 2] = 2;
    }
    //��
    if (y + 2 <= BLOCK_HEIGHT && map[x][y + 2] == 1) 
    {
        block* b = new block(x, y + 2);
        openlist.push_back(b);
        map[x][y + 2] = 2;
    }
    //��
    if (x - 2 >= 0 && map[x - 2][y] == 1) 
    {
        block* c = new block(x - 2, y);
        openlist.push_back(c);
        map[x - 2][y] = 2;
    }
    //��
    if (x + 2 <= BLOCK_WIDTH && map[x + 2][y] == 1) 
    {
        block* d = new block(x + 2, y);
        openlist.push_back(d);
        map[x + 2][y] = 2;
    }
}

void redarw(void) 
{
    for (int y = 0; y < BLOCK_HEIGHT; y++) 
    {
        for (int x = 0; x < BLOCK_WIDTH; x++) 
        {
            if (map[x][y] == 1) 
            {
                BLOCK_color(x, y, qiangbi);
            }
            else if (map[x][y] == 2) 
            {
                BLOCK_color(x, y, qiangbi);
            }
            else if (map[x][y] == 0) 
            {
                BLOCK_color(x, y, lu);
            }
        }
    }
    FlushBatchDraw();
}
