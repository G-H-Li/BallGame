#include "pch.h"
#include "basketball.h"

//移动光标的函数，输入为横坐标和纵坐标,输出字符的颜色
void basketball::moveTo(int x, int y, int color)
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
void basketball::hide()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}

//播放音乐
void basketball::music(const char file[])
{
	PlaySoundA(file, NULL, SND_FILENAME | SND_ASYNC);
}

//初始化球
void basketball::initBall(int color)
{
	srand((unsigned)time(0));
	ballX = rand() % 39 + 11;
	showBall(color);
	//初始化球的运动方向
	xOffset = rand() % 2;
	if (xOffset == 0)
	{
		xOffset = -1;
	}
}

//显示球
void basketball::showBall(int color)
{
	moveTo(ballX, ballY, color);
	cout << ball;
	hide();

}

//与障碍物的碰撞判断
void basketball::judgeBoard(pf clearBoard, vector<vector<int>> &obstacle)
{
	vector<int> temp;
	for (unsigned int i = 0; i < obstacle.size(); i++)
	{
		if (ballY == obstacle[i][1])//如果与障碍物在同一行
		{
			if (ballX >= obstacle[i][0] && ballX < (obstacle[i][0] + 7)) //如果下一个变换位置在障碍物内部
			{
				if ((ballY - yOffset) > obstacle[i][1])
				{
					ballY = obstacle[i][1] + 1;
					yOffset = 1;
					music("music1.wav");
					for (int h = 0; h < 2; h++)
					{
						temp.push_back(obstacle[i][0]);
						temp.push_back(obstacle[i][1]);
					}
					clearBoard(temp[0], temp[1]);
					break;
				}
				else if ((ballY - yOffset) < obstacle[i][1])
				{
					ballY = obstacle[i][1] - 1;
					yOffset = -1;
					music("music1.wav");
					for (int h = 0; h < 2; h++)
					{
						temp.push_back(obstacle[i][0]);
						temp.push_back(obstacle[i][1]);
					}
					clearBoard(temp[0], temp[1]);
					break;
				}
			}
			else  //如果下个变换位置在障碍物外部
			{
				if (ballX == (obstacle[i][0] - 2) || ballX == (obstacle[i][0] - 1))  //在障碍物左侧
				{
					ballX = obstacle[i][0] - 2;
					xOffset = -1;
					music("music1.wav");
					for (int h = 0; h < 2; h++)
					{
						temp.push_back(obstacle[i][0]);
						temp.push_back(obstacle[i][1]);
					}
					clearBoard(temp[0], temp[1]);
					break;
				}
				else if (ballX == (obstacle[i][0] + 7) || ballX == (obstacle[i][0] + 6)) //在障碍物右侧
				{
					yOffset = -yOffset;
					xOffset = 1;
					music("music1.wav");
					for (int h = 0; h < 2; h++)
					{
						temp.push_back(obstacle[i][0]);
						temp.push_back(obstacle[i][1]);
					}
					clearBoard(temp[0], temp[1]);
					break;
				}
			}
		}
		else if (ballY == (obstacle[i][1] + 1) || ballY == (obstacle[i][1] - 1)) //如果不与障碍物在同一行，但在障碍物上方或下方
		{
			if (ballX >= obstacle[i][0] && ballX <= (obstacle[i][0] + 7))
			{
				yOffset = -yOffset;
				music("music1.wav");
				for (int h = 0; h < 2; h++)
				{
					temp.push_back(obstacle[i][0]);
					temp.push_back(obstacle[i][1]);
				}
				clearBoard(temp[0], temp[1]);
				break;
			}
		}
	}
}

//与撞球的人的碰撞判断
void basketball::judgeCXK(const int &CXKx, const int &CXKy, int &state)
{
	if (ballY == 25)
	{
		if (ballX >= (CXKx - 2) && ballX <= (CXKx + 2))
		{
			yOffset = -1;
			music("music0.wav");
		}
	}
	else if (ballY == 26)
	{
		if (ballX >= CXKx && ballX <= (CXKx + 2))
		{
			ballY = 25;
			yOffset = -1;
			music("music0.wav");
		}
		else if (ballX == (CXKx + 3) || ballX == (CXKx - 2))
		{
			yOffset = -1;
			music("music0.wav");
		}
	}
	else if (ballY == 27)
	{
		if (ballX > (CXKx - 2) && ballX < (CXKx + 3))
		{
			ballY = 25;
			yOffset = -1;
			music("music0.wav");
		}
		else if (ballX == (CXKx + 3) || ballX == (CXKx - 2))
		{
			yOffset = -1;
			music("music0.wav");
		}
	}
	else if (ballY >= 28)
	{
		state = 0;
	}
}

//横坐标上的边界判断
void basketball::judgeX()
{
	if (ballX >= 59)
	{
		ballX = 58;
		xOffset = -1;
		music("music2.wav");
	}
	else if (ballX <= 0)
	{
		ballX = 1;
		xOffset = 1;
		music("music2.wav");
	}
}

//纵坐标上的边界判断
void basketball::judgeY(int &state)
{
	if (ballY <= 0)
	{
		ballY = 1;
		yOffset = 1;
		music("music2.wav");
	}
	else if (ballY >= 28)
	{
		state = 0;
	}
}

//判断球与球之间的碰撞
void basketball::judgeBall(const int &x, const int &y, const int &offx, const int &offy)
{
	if (ballY == y)//下一个位置在同一行
	{
		if (ballX >= (x - 1) && ballX <= (x + 1))
		{
			if (yOffset != offy)
			{
				if (xOffset > 0)
				{
					ballX = x - 2;
					xOffset = -1;
					music("music2.wav");
				}
				else
				{
					ballX = x + 2;
					xOffset = 1;
					music("music2.wav");
				}
			}
			else
			{
				if (xOffset > 0)
				{
					ballX = x - 1;
					if ((ballY - yOffset) < y)
					{
						ballY = y - 1;
					}
					else if ((ballY - yOffset) > y)
					{
						ballY = y + 1;
					}
				}
				else
				{
					ballX = x + 1;
					if ((ballY - yOffset) < y)
					{
						ballY = y - 1;
					}
					else if ((ballY - yOffset) > y)
					{
						ballY = y + 1;
					}
				}
			}
		}
		else if (ballX == (x - 2) || ballX == (x + 2))
		{
			if (xOffset != offx)
			{
				xOffset = -xOffset;
				music("music2.wav");
			}
		}
	}
	else if (ballY == (y + 1) || ballY == (y - 1))
	{
		if (ballX >= (x - 1) && ballX < (x + 1))
		{
			if (xOffset = offx && yOffset != offy)
			{
				yOffset = -yOffset;
				music("music2.wav");
			}
			else if (xOffset = offx && yOffset == offy)
			{
				if (yOffset > 0)
				{
					if (ballY < y)
					{
						yOffset = -yOffset;
						xOffset = -xOffset;
						music("music2.wav");
					}
				}
				else
				{
					if (ballY > y)
					{
						yOffset = -yOffset;
						xOffset = -xOffset;
						music("music2.wav");
					}
				}
			}
		}
	}
}

//控制球的移动，输入为横坐标速度增量和纵坐标速度增量
void basketball::moveBall(const int &CXKx, const int &CXKy, int &state, pf clearBoard, vector<vector<int>> &obstacle)
{
	ballX += xOffset;
	judgeX();
	ballY += yOffset;
	judgeY(state);
	judgeCXK(CXKx, CXKy, state);
	judgeBoard(clearBoard, obstacle);
}

//清除球
void basketball::clearBall()
{
	moveTo(ballX, ballY);
	cout << "  ";
}

//数据刷新
void basketball::ballRefresh()
{
	ballX = ballY = 1;
	xOffset = yOffset = 1;
}


basketball::~basketball()
{
}
