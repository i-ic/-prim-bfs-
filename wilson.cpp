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
extern block* myprev[BLOCK_WIDTH + 10][BLOCK_HEIGHT + 10];
int vis[BLOCK_WIDTH + 10][BLOCK_HEIGHT + 10];

void blockColor(int x, int y, COLORREF RGB);
void wilsoninit(void);
void reDarw(void);
bool checkPath(int x, int y);
std::stack<std::pair<int, int>> next;

void wilsoninit(void) {
    for (int y = 0; y <= BLOCK_HEIGHT; y++) {
        for (int x = 0; x <= BLOCK_WIDTH; x++) {
            map[x][y] = 1; 
            myprev[x][y] = nullptr; 
            vis[x][y] = 1;
        }
    }
    map[1][1] = 0;
    reDarw();
	mciSendString(_T("open orb.mp3 alias bkmusic1"), NULL, 0, NULL);
	mciSendString(_T("play bkmusic1 repeat"), NULL, 0, NULL);
	for (int i = 1; i <= BLOCK_WIDTH / 2; i++) {
		for (int j = 1; j <= BLOCK_HEIGHT / 2; j++) {
			if (i == 1 && j == 1) {
				continue;
			}
			int nx = i * 2 - 1;
			int ny = j * 2 - 1;
			if (!map[nx][ny]) {
				continue;
			}
			next.push({ nx, ny });
			vis[nx][ny] = 0;
			blockColor(nx, ny, picked);
			FlushBatchDraw();
			while (map[nx][ny]) {
				int s = rand() % 4;
				while ((!checkPath(nx + dir2[s][0], ny + dir2[s][1]))) {
					s = rand() % 4;
				}
				nx += dir2[s][0];
				ny += dir2[s][1];
				if (!vis[nx][ny]) {
					while (next.top().first != nx || next.top().second != ny) {
						vis[next.top().first][next.top().second] = 1;
						blockColor(next.top().first, next.top().second, wal);
						FlushBatchDraw();
						next.pop();
					}
				}
				else {
					next.push({ nx, ny });
					vis[nx][ny] = 0;
					if (map[nx][ny] == 1) {
						blockColor(nx, ny, picked);
						FlushBatchDraw();
					}
					else {
						blockColor(nx, ny, road);
						FlushBatchDraw();
					}
				}
			}
			int lx = next.top().first, ly = next.top().second;
			vis[lx][ly] = 1;
			next.pop();
			while (!next.empty()) {
				int nx = next.top().first, ny = next.top().second;
				vis[nx][ny] = 1;
				map[nx][ny] = 0;
				map[(nx + lx) / 2][(ny + ly) / 2] = 0;
				blockColor((nx + lx) / 2,(ny + ly) / 2, road);
				blockColor(nx, ny, road);
				FlushBatchDraw();
				lx = nx, ly = ny;
				next.pop();
			}
		}
	}
	reDarw();
	mciSendString(_T("close bkmusic1"), NULL, 0, NULL);
}

bool checkPath(int x, int y) {
    if (x <= 0 || y <= 0 || x > BLOCK_WIDTH || y > BLOCK_HEIGHT) {
        return false;
    }
    return true;
}