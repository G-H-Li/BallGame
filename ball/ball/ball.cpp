#include "pch.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <vector>
#include <conio.h>
#include <time.h>
#include "basketball.h"
#include "basketball1.h"

using namespace std;

const string board = "███";  //定义木板的形状
static int state = 1;  //定义游戏状态，1为游戏正常，0为游戏失败
static int CXKx = 30, CXKy = 26;  //定义游戏人物的初始显示位置
static int speed = 500;
static vector<vector<int> >obstacle;    //用vector定义障碍物
								
void roundOne();
void roundTwo();
void showBoundary();
void init();

//初始化障碍物二维数组,待优化
void initObstacle(const char file[])
{
	int buffer[2];
	fstream level;
	level.open(file, ios::in);
	if (level.is_open())
	{
		while (!level.eof())
		{
			level >> buffer[0] >> buffer[1];
			vector<int> a;
			a.push_back(buffer[0]);
			a.push_back(buffer[1]);
			obstacle.push_back(a);
			a.clear();
		}
		level.close();
	}
	else
		cout << "游戏初始化失败";
}

//移动光标的函数，输入为横坐标和纵坐标,输出字符的颜色
void moveTo(int x, int y, int color=7)
{
	HANDLE hout;
	COORD pos;
	pos.X = x;
	pos.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hout, color);
	SetConsoleCursorPosition(hout, pos);
}

//隐藏光标，提高用户体验
void hide()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}

//游戏失败后显示事物
void gameOver()
{
	system("cls");
	moveTo(36, 15);
	string str = "你失败了呢，律师函警告一次";
	for (unsigned int i = 0; i < str.size(); i++)
	{
		Sleep(100);
		cout << str[i];
	}
	Sleep(1000);
	cout << endl;
}

//显示游戏胜利之后的动画
void win()
{
	system("cls");
	moveTo(36, 15);
	string str = "恭喜恭喜，喜提NBA最娘大使";
	for (unsigned int i = 0; i < str.size(); i++)
	{
		Sleep(100);
		cout << str[i];
	}
	Sleep(1000);
	cout << endl;
}

//刷新所有数据
void refresh()
{
	CXKx = 30; CXKy = 26;
	speed = 500;
	state = 1;
	obstacle.clear();
}

//清除箭头
void clearArry(int y)
{
	moveTo(21, y);
	cout << "  ";
	//hide();
}

//显示箭头
void showArry(int y = 16)
{
	moveTo(21, y);
	cout << "->";
	hide();
}

//设置界面,调节小球运动速度
void setting()
{
	int y=14, i=1;
	system("cls");
	showBoundary();
	moveTo(23, 11, 4);
	cout << "设  置";
	moveTo(15, 13);
	cout << "调节小球速度：";
	moveTo(23, 14);
	cout << "慢";
	moveTo(23, 15);
	cout << "中";
	moveTo(23, 16);
	cout << "快";
	showArry(14);
	while (i)
	{
		if (_kbhit())
		{
			char x = _getch();
			if (x == '\r')
			{
				if (y == 14)
				{
					i = 0;
					speed = 500;
					init();
				}
				else if (y == 15)
				{
					i = 0;
					speed = 250;
					init();
				}
				else if (y == 16)
				{
					i = 0;
					speed = 150;
					init();
				}
			}
			else if (x == 's')
			{
				if (y != 16)
				{
					clearArry(y);
					showArry(y + 1);
					y += 1;
				}
				else
				{
					clearArry(y);
					y = 14;
					showArry(y);
				}
			}
			else if (x == 'w')
			{
				if (y == 14)
				{
					clearArry(y);
					y = 16;
					showArry(y);
				}
				else
				{
					clearArry(y);
					showArry(y - 1);
					y -= 1;
				}
			}
		}
	}
}

//操作说明指南
void guide()
{
	showBoundary();
	moveTo(23, 14, 4);
	cout << "操作说明";
	moveTo(12, 15);
	cout << "请首先将输入调节为英文输入法";
	moveTo(15, 16);
	cout << "a：控制人物向左移动";
	moveTo(15, 17);
	cout << "d: 控制人物向右移动";
	moveTo(15, 18);
	cout << "p: 暂停游戏";
	moveTo(15, 19);
	cout << "o: 返回主界面";
	Sleep(3000);
}

//清除操作指南
void clearGuide()
{
	moveTo(23, 14);
	cout << "        ";
	moveTo(12, 15);
	cout << "                            ";
	for (int i = 15; i < 20; i++)
	{
		moveTo(15, i);
		cout << "                    ";
	}
}

//游戏初始界面
void init()
{
	system("cls");
	showBoundary();
	state = 1;
	int i = 1, y = 16;
	moveTo(10, 11, 5);
	cout << "大家好，我是练习时长两年半的练习生";
	moveTo(15, 12, 5);
	cout << "喜欢唱、跳、rap、篮球";
	moveTo(24, 13, 5);
	cout << "music";
	moveTo(23, 16);
	cout << "开始游戏";
	moveTo(23, 17);
	cout << "设    置";
	moveTo(23, 18);
	cout << "退出游戏";
	showArry();
	while (i)
	{
		if (_kbhit())
		{
			char x = _getch();
			if (x == '\r')
			{
				if (y == 16)
				{
					i = 0;
					roundOne();
				}
				else if (y == 17)
				{
					i = 0;
					setting();
				}
				else if (y == 18)
				{
					i = 0;
					exit(0);
				}
			}
			else if (x == 's')
			{
				if (y != 18)
				{
					clearArry(y);
					showArry(y + 1);
					y += 1;
				}
				else
				{
					clearArry(y);
					y = 16;
					showArry(y);
				}
			}
			else if (x == 'w')
			{
				if (y == 16)
				{
					clearArry(y);
					y = 18;
					showArry(y);
				}
				else
				{
					clearArry(y);
					showArry(y - 1);
					y -= 1;
				}
			}
		}
	}
}

//关卡过渡界面
void transition()
{
	system("cls");
	showBoundary();
	moveTo(28, 15);
	cout << "第二关";
	hide();
	Sleep(1000);
	system("cls");
}

//游戏胜负判断逻辑
void judgeWin()
{
	if (state == 2)
	{
		state = 3;
		roundTwo();
	}
	else if (state == 4)
	{
		win();
		init();
	}
	else if (state == 0)
	{
		gameOver();
		init();
	}
}

//显示游戏边界
void showBoundary()
{
	char xpic = '_';
	char ypic = '|';
	for (int x = 0; x < 60; x++)
	{
		moveTo(x, 0);
		cout << xpic;
		moveTo(x, 29);
		cout << xpic;
	}
	for (int y = 0; y < 30; y++)
	{
		moveTo(0, y);
		cout << ypic;
		moveTo(60, y);
		cout << ypic;
	}
}

//显示撞球的人
void showCXK(char x='a')
{
	if (x == 'a')
	{
		moveTo(CXKx, CXKy);
		cout << "⊙" << endl;
	}
	else
	{
		moveTo(CXKx, CXKy);
		cout << " ⊙" << endl;
	}
	moveTo(CXKx, (CXKy+1));
	cout << "<|>" << endl;
	if (x == 'a')
	{
		moveTo(CXKx, (CXKy + 2));
		cout << " /\\";
	}
	else
	{
		moveTo(CXKx, (CXKy + 2));
		cout << "/\\";
	}
	hide();
}

//撞球人的移动,输入为a或者d
void moveCXK(char x)
{
	if (x == 'a')
	{
		CXKx--;
		if (CXKx <= 0)
		{
			CXKx = 1;
		}
	}
	
	if (x == 'd')
	{
		CXKx++;
		if (CXKx >= 58)
		{
			CXKx = 57;

		}
	}
}

//清除撞球人
void clearCXK()
{
	for (int i = 0; i < 3; i++)
	{
		moveTo(CXKx, (CXKy + i));
		cout << "   ";
		hide();
	}
}

//显示障碍物
void showObstacle()
{
	srand((unsigned)time(NULL));
	for (unsigned int i = 0; i < obstacle.size()-1; i++)
	{
		int color = rand() % 9 + 1, temp = 0;
		if (color == temp)
		{
			if (color == 9)
			{
				color -= 1;
			}
			else
			{
				color += 1;
			}
		}
		moveTo(obstacle[i][0], obstacle[i][1], color);
		temp = color;
		cout << board;
	}
}

//清除障碍物
void clearBoard(int x, int y)
{
	vector<vector<int>>::iterator its;
	vector<int>::iterator itx;
	moveTo(x, y);
	cout << "      ";
	if (obstacle.size() != 1)
	{
		for (its = obstacle.begin(); its < obstacle.end()-1; its++)
		{
			itx = (*its).begin();
			int a = (int)*itx;
			if (a == x)
			{
				itx += 1;
				int b = (int)*itx;
				if (b == y)
				{
					its = obstacle.erase(its);
				}
			}
		}
	}
}

//第一关
void roundOne()
{
	basketball ball0;
	system("cls");
	guide();
	system("cls");

	clock_t start, start1;
	start = start1 = clock();

	showBoundary();
	initObstacle("1.txt");
	showObstacle();
	showCXK();
	ball0.initBall(4);
	while (state == 1)
	{
		if (_kbhit())
		{
			char x = _getch();
			if (x == 'a' || x == 'd')
			{
				if (clock() - start1 > 0)
				{
					clearCXK();
					moveCXK(x);
					showCXK(x);
					start1 = clock();
				}
			}
			else if (x == 'p')
			{
				guide();
				clearGuide();
			}
			else if (x == 'e')
			{
				obstacle.clear();
				state = 3;
				roundTwo();
			}
			else if (x == 'o')
			{
				init();
			}
		}
		if (clock() - start > speed)
		{
			ball0.clearBall();
			ball0.moveBall(CXKx, CXKy, state, clearBoard, obstacle);
			ball0.showBall(4);
			if (obstacle.size() == 1) state = 2;
			judgeWin();
			start = clock();
		}
	}
	refresh();
	//init(ball0);
}

//第二关
void roundTwo()
{
	transition();

	clock_t start1, start2, start3;
	start1= start2 = start3= clock();

	basketball b1;
	basketball1 b2;

	showBoundary();
	initObstacle("2.txt");
	showObstacle();
	showCXK();
	b1.initBall(4);
	b2.initBall(5);
	while (state == 3)
	{
		if (_kbhit())
		{
			char x = _getch();
			if (x == 'a' || x == 'd')
			{
				clearCXK();
				moveCXK(x);
				showCXK(x);
			}
			else if (x == 'p')
			{
				guide();
				clearGuide();
			}
			else if (x == 'q')
			{
				obstacle.clear();
				state = 1;
				roundOne();
			}
			else if (x == 'o')
			{
				init();
			}
		}

		if ((clock() - start1) > (speed+100))
		{
			b1.clearBall();
			b1.moveBall(CXKx, CXKy, state, clearBoard, obstacle);
			b1.judgeBall(b2.ballX, b2.ballY, b2.xOffset, b2.yOffset);
			b1.showBall(4);
			if (obstacle.size() == 1) state = 4;
			judgeWin();
			start1 = clock();
		}
		if (clock() - start2 > speed)
		{
			b2.clearBall();
			b2.moveBall(CXKx, CXKy, state, clearBoard, obstacle);
			b2.judgeBall(b1.ballX, b1.ballY, b1.xOffset, b1.yOffset);
			b2.showBall(5);
			if (obstacle.size() == 1) state = 4;
			judgeWin();
			start2 = clock();
		}
	}
	b1.ballRefresh();
	b2.ballRefresh();
	refresh();
}
int main()
{
	init();
	return 0;
}

