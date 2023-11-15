/* ���������Թ�·�����������·�� */

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

#define bfsPath COLORREF RGB(200,200,255)//BFS·����ɫ
#define shortestPath COLORREF RGB(255,255,0)//���·����ɫ
#define qidian COLORREF RGB(0,255,0)//�����ɫ
#define zhongdian COLORREF RGB(255,0,0)//�յ���ɫ

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
void through(int x, int y);//��x,y��������һ������Ѿ����·�Ľڵ��ͨ
void bfs(void); //BFSѰ��·��
void drawShortestPath(block* start, block* end); //����·��

void drawShortestPath(block* start, block* end) {
    block* current = end;
    while (current != start) {
        BLOCK_color(current->x, current->y, shortestPath);
        current = myprev[current->x][current->y];
    }
}

void bfs(void) 
{
    queue<block*> bfsQueue;//���б����ڵ㡢�Ƚ��ȳ�
    block* start = new block(1, 1);
    block* end = new block(BLOCK_WIDTH - 2, BLOCK_HEIGHT - 2);
    bfsQueue.push(start);
    mciSendString(_T("open portal.mp3 alias bkmusic2"), NULL, 0, NULL);//������Ч
    mciSendString(_T("play bkmusic2 repeat"), NULL, 0, NULL);//ѭ������
    while (!bfsQueue.empty())     //�ж϶����Ƿ�Ϊ�գ�����Ϊ�ձ�ʾ��·��(�������޽��Թ�)
    {
        block* current = bfsQueue.front();
        bfsQueue.pop();//ɾ���������²��Ԫ��
        if (current->x == end->x && current->y == end->y) //�ж��Ƿ񵽴�Ŀ��ڵ�
        {
            drawShortestPath(start, end);//�������·��
            mciSendString(_T("close bkmusic2"), NULL, 0, NULL);//ֹͣ����
            BLOCK_color(1, 1, qidian);
            BLOCK_color(BLOCK_WIDTH - 2, BLOCK_HEIGHT - 2, zhongdian);
            FlushBatchDraw();//��������
            return;//����bfs
        }
        if (current->y - 1 >= 0 && map[current->x][current->y - 1] == 0 && myprev[current->x][current->y - 1] == nullptr)         // �����ǰ�ڵ���Ͻڵ���δ���ʹ��ģ���ô�ͽ����Ǽ��뵽������
        {
            block* up = new block(current->x, current->y - 1);
            myprev[up->x][up->y] = current;
            bfsQueue.push(up);
            BLOCK_color(up->x, up->y, bfsPath);
            FlushBatchDraw();//��������
        }
        if (current->y + 1 < BLOCK_HEIGHT && map[current->x][current->y + 1] == 0 && myprev[current->x][current->y + 1] == nullptr)         //��
        {
            block* down = new block(current->x, current->y + 1);
            myprev[down->x][down->y] = current;
            bfsQueue.push(down);
            BLOCK_color(down->x, down->y, bfsPath);
            FlushBatchDraw();//��������
        }
        if (current->x - 1 >= 0 && map[current->x - 1][current->y] == 0 && myprev[current->x - 1][current->y] == nullptr)         //��
        {
            block* left = new block(current->x - 1, current->y);
            myprev[left->x][left->y] = current;
            bfsQueue.push(left);
            BLOCK_color(left->x, left->y, bfsPath);
            FlushBatchDraw();//��������
        }
        if (current->x + 1 < BLOCK_WIDTH && map[current->x + 1][current->y] == 0 && myprev[current->x + 1][current->y] == nullptr)         //��
        {
            block* right = new block(current->x + 1, current->y);
            myprev[right->x][right->y] = current;
            bfsQueue.push(right);
            BLOCK_color(right->x, right->y, bfsPath);
            FlushBatchDraw();//��������
        }
    }
    exit(1);
}