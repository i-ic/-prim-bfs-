#pragma once

enum Info {
	WIDTH = 1920,
	HEIGHT = 1080,
	BLOCK_XY = 12,
};

const int BLOCK_WIDTH = WIDTH / (BLOCK_XY);
const int BLOCK_HEIGHT = HEIGHT / (BLOCK_XY);
const int dir1[][2] = { {0,1},{0,-1},{1,0},{-1,0} };
const int dir2[][2] = { {0,2},{0,-2},{2,0},{-2,0} };

#define road COLORREF RGB(220,220,220)
#define wal COLORREF RGB(30,30,30)
#define picked COLORREF RGB(150,30,30)
#define beginPoint COLORREF RGB(0,255,0)
#define endPoint COLORREF RGB(255,0,0)
#define shortestPath COLORREF RGB(255,255,0)