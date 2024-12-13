/* ��С��������ʼ���������Թ� */

#include <graphics.h>
#include "initset.h"
#include "bits/stdc++.h"
#pragma comment(lib,"Winmm.lib")//������Ч����api

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

extern int map[BLOCK_WIDTH + 10][BLOCK_HEIGHT + 10];
extern std::vector<block*> openlist;//��ѡ�б�
extern std::vector<block*> list;
extern block* myprev[BLOCK_WIDTH + 10][BLOCK_HEIGHT + 10]; 
/* ���ڼ�¼���ڵ㣬ͬʱ��������bfsѰ�����·�� */

// ��������
void blockColor(int x, int y, COLORREF RGB);//��x��yλ�û���ɫΪRGB�ķ���
void init(void);//��ʼ��
void addList(int x, int y);//��x,y���ܲ���·�Ľڵ�����ѡ�б�
void reDarw(void);//ˢ����Ļ
void prim(void);//prim��ѭ��
bool through(int x, int y);//��x,y��������һ������Ѿ����·��·���ͨ
void bfs(void); //BFSѰ��·��

void init(void) {
    openlist.clear();
        for (int y = 0; y <= BLOCK_HEIGHT; y++) {     // ��ͼ��ʼ��Ϊǽ,���Ӷ�n*m
            for (int x = 0; x <= BLOCK_WIDTH; x++) {
                map[x][y] = 1;
                myprev[x][y] = nullptr;
            }
        }
        map[1][1] = 0;    // ��ʼ����㡢�յ�
        map[BLOCK_WIDTH - 1][BLOCK_HEIGHT - 1] = 0;
        addList(1, 1);        // ���ڵ���ӽڵ���ǽ�ڼ����ѡ�б�
    prim();//
    bfs();
}

void prim(void) { //ÿ�������౻����һ�� ���ѭ��n*m,�ڲ��ػ��ƺ���n*m,���Ӷ�Ϊn2*m2/REF��Ϊ������ĸ��Ӷ�ƿ��
    mciSendString(_T("open orb.mp3 alias bkmusic1"), NULL, 0, NULL);//������Ч
    mciSendString(_T("play bkmusic1 repeat"), NULL, 0, NULL);//ѭ������
    while (openlist.size() > 0) { //ֱ�����еĽڵ㶼�Ѿ������ʹ�
        int Index = rand() % openlist.size();        // �Ӵ�ѡ�����ѡһ����ʼ�ڵ�
        block* kaishi = openlist[Index];        // ����ʼ�ڵ���������һ������Ѿ����·�Ľڵ��ͨ
        if (through(kaishi->x, kaishi->y)) {
            map[kaishi->x][kaishi->y] = 0;        // ����ʼ�ڵ���·
            addList(kaishi->x, kaishi->y);     // ����ʼ�ڵ���ӽڵ��е�����ǽ�ڼ����ѡ�б�
        }
        openlist.erase(openlist.begin() + Index);        // �Ӵ�ѡ·�����Ƴ���ʼ�ڵ�
        blockColor(kaishi->x, kaishi->y, selected);
        FlushBatchDraw();
        if (openlist.size() % REF == 0) {
            reDarw();
        }
    }
    for (int i = 0; i < 4; ++i) { //��֤�Թ��н�
        through(BLOCK_WIDTH - 1,BLOCK_HEIGHT - 1);
        through(BLOCK_WIDTH - 3, BLOCK_HEIGHT - 3);
    }
    reDarw();
    mciSendString(_T("close bkmusic1"), NULL, 0, NULL);//ֹͣ����
}

bool through(int x, int y) { //���Ӷ�o1
    list.clear();
    // ����ӽڵ㣬�����·��������б�
    for (int i = 0; i < 4; ++i) {
        if (y + dir2[i][1] > 0 && x + dir2[i][0] > 0 && 
            y + dir2[i][1] < BLOCK_HEIGHT && x + dir2[i][0] < BLOCK_WIDTH &&
            map[x + dir2[i][0]][y + dir2[i][1]] == 0) {
                block* temp = new block(x + dir1[i][0], y + dir1[i][1]);
                list.push_back(temp);
        }
    }
    if (list.size() != 0) {
        int AIndexea = rand() % list.size();// ���б������ѡ��һ��·�ڵ�
        block* A = list[AIndexea];
        map[A->x][A->y] = 0;// ��x��y��A��ͨ
        return true;
    } else {
        return false;
    }
}

void addList(int x, int y) { //���Ӷ�o1
    // ����ӽڵ㣬�����ǽ�ڣ����һ�û�б����뵽��ѡ�б��У���ô�ͽ������뵽��ѡ�б���
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

void reDarw(void) { //���Ӷ�n*m
    for (int y = 0; y <= BLOCK_HEIGHT; y++) {
        for (int x = 0; x <= BLOCK_WIDTH; x++) {
            if (map[x][y] == 1) {
                blockColor(x, y, wal);
            } else if (map[x][y] == 2) {
                blockColor(x, y, wal);
            } else {
                blockColor(x, y, road);
            }
        }
    }
    FlushBatchDraw();
}
