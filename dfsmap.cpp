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
std::vector<block*> lists;
extern block* myprev[BLOCK_WIDTH + 10][BLOCK_HEIGHT + 10];

void dfsmap();
void dfsthrough(int x, int y);
bool check(int x, int y);
void blockColor(int x, int y, COLORREF RGB);
void dfsinit(void);
void primAddList(int x, int y);
void reDarw(void);
void prim(void);
bool primThrough(int x, int y);

void dfsinit() {
	openlist.clear();
	for (int y = 0; y <= BLOCK_HEIGHT; y++) {
		for (int x = 0; x <= BLOCK_WIDTH; x++) {
			map[x][y] = 1;
			myprev[x][y] = nullptr;
		}
	}
	map[1][1] = 0;
	block* temp = new block(1, 1);
	openlist.push_back(temp);
	reDarw();
	dfsmap();
}
void dfsmap() {
	mciSendString(_T("open orb.mp3 alias bkmusic1"), NULL, 0, NULL);
	mciSendString(_T("play bkmusic1 repeat"), NULL, 0, NULL);
	while (openlist.size() > 0) {
		int Index = (int)openlist.size() - 1;
		block* A = openlist[Index];
		while (!check(A->x, A->y)) {
			A = openlist[Index];
			if (Index == 0) return;
			--Index;
		}
		dfsthrough(A->x, A->y);
	}
	reDarw();
	mciSendString(_T("close bkmusic1"), NULL, 0, NULL);
}
void dfsthrough(int x, int y) {
	list.clear();
	lists.clear();
	for (int i = 0; i < 4; ++i) {
		if (y + dir2[i][1] > 0 && x + dir2[i][0] > 0 &&
			y + dir2[i][1] < BLOCK_HEIGHT && x + dir2[i][0] < BLOCK_WIDTH &&
			map[x + dir2[i][0]][y + dir2[i][1]] == 1) {
			block* temp = new block(x + dir1[i][0], y + dir1[i][1]);
			block* a = new block(x + dir1[i][0], y + dir1[i][1]);
			block* aa = new block(x + dir2[i][0], y + dir2[i][1]);
			list.push_back(a);
			lists.push_back(aa);
		}
	}
	if (list.size() != 0) {
		int Index = rand() % list.size();
		block* B = list[Index];
		block* BB = lists[Index];
		map[B->x][B->y] = 0;
		map[BB->x][BB->y] = 0;
		blockColor(B->x, B->y, road);
		blockColor(BB->x, BB->y, road);
		FlushBatchDraw();
		openlist.push_back(BB);

	}
}
bool check(int x, int y) {
	bool temp = 0;
	for (int i = 0; i < 4; ++i) {
		if (y + dir2[i][1] > 0 && x + dir2[i][0] > 0 &&
			y + dir2[i][1] < BLOCK_HEIGHT && x + dir2[i][0] < BLOCK_WIDTH &&
			map[x + dir2[i][0]][y + dir2[i][1]] == 1) {
			temp = 1;
		}
	}
	return temp;
}