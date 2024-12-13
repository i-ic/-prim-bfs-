#pragma once

enum Info {
	WIDTH = 1920,//�ֱ���
	HEIGHT = 1080,
	BLOCK_XY = 12,//С����߳�
	REF = 35//ˢ���ٶ�
};

const int BLOCK_WIDTH = WIDTH / (BLOCK_XY);//С����x������
const int BLOCK_HEIGHT = HEIGHT / (BLOCK_XY);//С����y������ 
const int dir1[][2] = { {0,1},{0,-1},{1,0},{-1,0} };
const int dir2[][2] = { {0,2},{0,-2},{2,0},{-2,0} };

#define road COLORREF RGB(220,220,220)//·����ɫ
#define wal COLORREF RGB(30,30,30)//ǽ����ɫ
#define beginPoint COLORREF RGB(0,255,0)//�����ɫ
#define endPoint COLORREF RGB(255,0,0)//�յ���ɫ
#define selected COLORREF RGB(190,50,50)//ѡ����ɫ
#define shortestPath COLORREF RGB(255,255,0)//���·����ɫ