#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <time.h>
#include <Mmsystem.h>
#include <stdlib.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

class basketball1
{
private:
	const string ball = "●";  //定义球的形状
	typedef void(*pf)(int, int);
	int y;
public:
	basketball1() { ballY = 15; xOffset = yOffset = 1; };
	~basketball1();
	static int xOffset, yOffset;  //定义初始横坐标和纵坐标偏移量
	static int ballY, ballX;  //定义球的初始显示位置
	void initBall(int color);
	void showBall(int color);
	void judgeBoard(pf clearBoard, vector<vector<int>> &obstacle);
	void judgeCXK(const int &CXKx, const int &CXKy, int &state);
	void judgeX();
	void judgeY(int &state);
	void judgeBall(const int &x, const int &y, const int &offx, const int &offy);
	void moveBall(const int &CXKx, const int &CXKy, int &state, pf clearBoard, vector<vector<int>> &obstacle);
	void clearBall();
	void ballRefresh();

	void moveTo(int x, int y, int color = 7);
	void hide();
	void music(const char file[]);
};



