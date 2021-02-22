// Heibaiqi-vs15.cpp : 定义控制台应用程序的入口点。
//
// 黑白棋.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <locale>
#include <windows.h>
/*该程序仍有bug,无人维护 2015 12 18
bug已排除 2015 12 31
*/
//HijjTf68&*
//李志鑫
//柯南王
//郑州市
using namespace std;
//dark white:0
#define BOARD_COLOR 0 //(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)
#define STONE_COLOR (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)
//red
#define LAST_STEP_COLOR (FOREGROUND_RED)
/*0:blank 1:black 2:white 3: set-able*/
int board[9][9];
bool luozi[9][9];
int analyzeBoard(int h[][9], int);
/*传递坐标用*/
int x, y;
int N; /*遍历深度 级别*/
int L; /*先手 or 后手*/
int state[9][9];
int inf = -10000;
int direction[8][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}, {-1, 1}, {-1, -1}, {1, 1}, {1, -1}};
/*四个角特殊对待,目的就是抢到四个角*/
int value(int state[][9])
{
	int t = 0;
	if (state[8][8] == 1)
		t = t - 400;
	if (state[1][1] == 1)
		t = t - 400;
	if (state[1][8] == 1)
		t = t - 400;
	if (state[8][1] == 1)
		t = t - 400;

	if (state[8][8] == 2)
		t = t + 400;
	if (state[1][1] == 2)
		t = t + 400;
	if (state[1][8] == 2)
		t = t + 400;
	if (state[8][1] == 2)
		t = t + 400;
	return t;
}
int evalue(int state[][9])
{
	int t = 0;
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			if (i == 1 || i == 8 || j == 1 || j == 8)
				switch (state[i][j])
				{
				case 1:
					if (i == j || abs(i - j) == 7)
						t -= 400;
					else
						t -= 10;
					break;
				case 2:
					if (i == j || abs(i - j) == 7)
						t += 400;
					else
						t += 10;
					break;
				}
		}
	}
	return t;
}
/*开始游戏,设置*/
int gameStart()
{
	cout << "                        黑白棋" << endl;
	cout << "             请选择难度" << endl;
	cout << "         1为简单，2为困难，3为变态" << endl;
	cin >> N;
	if (N > 0 && N < 4)
		N = 2 * N;
	else
		N = 2;
	system("cls");
	cout << "                  请选择先后手" << endl;
	cout << "                1为先手，2为后手" << endl;
	cin >> L;
	if (L == 2)
	{
		x = 4;
		y = 3;
	}
	system("cls");
	return 0;
}
/*
!!本程序最重要的函数,递归ai算法,看懂这个即可
基本思想是这样的,重复1 2:
1计算当前能下的所有点,假设下子
2接着计算对方能下的点,假设下子

如果在指定次数递归后能获得最高分数(即获得4个角),则优先下该处

该算法不考虑实际的势力分布和边的情况,只考虑占角,实际上占角基本意味着获胜
*/
int dfs(int state[9][9], int depth, int player)
{
	int x1, y1;
	int setStone(int[][9], int, int, int); /*声明*/
	int x2, y2;
	int mi;
	int ma;
	int ret;
	/*递归深度为N,结束*/
	if (!analyzeBoard(state, 3 - player) && !analyzeBoard(state, player) || depth == N)
		return evalue(state);
	else
	{
		mi = -inf;
		ma = inf;
		for (int i = 1; i < 9; i++)
			for (int j = 1; j < 9; j++)
			{
				analyzeBoard(state, player);
				/*如果该处可以落子*/
				if (luozi[i][j])
				{
					int ti[9][9];
					/*存储state*/
					for (int i = 1; i < 9; i++)
						for (int j = 1; j < 9; j++)
						{
							ti[i][j] = state[i][j];
						}

					setStone(state, player, i, j);
					ret = dfs(state, depth + 1, 3 - player);
					mi = mi;
					/*恢复state*/
					for (int i = 1; i < 9; i++)
						for (int j = 1; j < 9; j++)
						{
							state[i][j] = ti[i][j];
						}
					if (ret <= mi)
					{
						mi = ret;
						x1 = i;
						y1 = j;
					}
					if (ret >= ma)
					{
						ma = ret;
						x2 = i;
						y2 = j;
					}
				}
			}
	}
	if (player == 1)
		ret = mi;
	else
		ret = ma;
	if (depth == 1)
	{
		x = x2;
		y = y2;
	}
	return ret;
}
/*计算下期后的棋子改变*/
int setStone(int boar[9][9], int o, int a, int b)
{
	int x, y;
	x = a;
	y = b;
	boar[a][b] = o;
	for (int k = 0; k < 8; k++)
	{
		x = a + direction[k][0];
		y = b + direction[k][1];
		if (boar[x][y] == o || boar[x][y] == 0 || boar[x][y] == 3)
			continue;
		while (x > 0 && x < 9 && y > 0 && y < 9)
		{
			if (boar[x][y] == o)
			{
				int m = a + direction[k][0], n = b + direction[k][1];
				while (((m == x) + (n == y)) != 2)
				{
					boar[m][n] = o;
					m = m + direction[k][0];
					n = n + direction[k][1];
				}
				break;
			}
			else if (boar[x][y] == 3 - o)
			{
				x = x + direction[k][0];
				y = y + direction[k][1];
				continue;
			}
			else if (boar[x][y] == 0 || boar[x][y] == 3)
			{
				break;
			}
		}
	}
	return 1;
}
/*计算哪些位置可以下子,方法就是找到之间是否有对方的子*/
//判断函数是否能落子，1为黑棋，2为白棋，并将board中能落子的对应赋值成3，返回0则为无子可下，返回1则有子可下
int analyzeBoard(int boar[9][9], int o)
{
	int num = 0;
	/*先将能下的位置设成空*/
	for (int x = 1; x < 9; x++)
		for (int y = 1; y < 9; y++)
		{
			if (boar[x][y] == 3)
				boar[x][y] = 0;
		}
	/*清空luozi*/
	memset(luozi, false, sizeof(luozi));

	for (int i = 1; i < 9; i++)
		for (int j = 1; j < 9; j++)
		{
			if (boar[i][j] == 0)
			{
				for (int k = 0; k < 8; k++)
				{
					if (luozi[i][j])
						break;
					int a, b;
					a = i;
					b = j;
					a = a + direction[k][0];
					b = b + direction[k][1];
					if (boar[a][b] == o || boar[a][b] == 0)
						continue;
					while (a > 0 && a < 9 && b > 0 && b < 9)
					{
						a = a + direction[k][0];
						b = b + direction[k][1];
						if (boar[a][b] == o)
						{
							luozi[i][j] = true;
							num = 1;
							break;
						}
						else if (boar[a][b] == 3 - o)
							continue;
						else if (boar[a][b] == 0)
							break;
					}
				}
			}
		}
	for (int m = 1; m < 9; m++)
		for (int n = 1; n < 9; n++)
		{
			if (luozi[m][n])
				boar[m][n] = 3;
		}
	return num;
}
/*绘制棋盘*/
void printBoard()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, BOARD_COLOR | FOREGROUND_INTENSITY);
	cout << "    1   2   3   4   5   6   7   8" << endl;
	cout << " ┌ ─ ┬ ─ ┬ ─ ┬ ─ ┬ ─ ┬ ─ ┬ ─ ┬ ─ ┐" << endl;
	for (int i = 1; i < 9; i++)
	{
		cout << i;
		for (int j = 1; j < 9; j++)
		{
			cout << "│ ";
			if (i == x && j == y)
			{
				SetConsoleTextAttribute(hOut, LAST_STEP_COLOR | FOREGROUND_INTENSITY);
			}
			else
			{
				SetConsoleTextAttribute(hOut, STONE_COLOR | FOREGROUND_INTENSITY);
			}
			if (board[i][j] == 1)
				cout << "●";
			else if (board[i][j] == 2)
				cout << "○";
			else if (board[i][j] == 3)
				cout << "＋"; //＋
			else if (board[i][j] == 0)
				cout << "  ";
			SetConsoleTextAttribute(hOut, BOARD_COLOR | FOREGROUND_INTENSITY);
		}

		cout << "│ ";
		if (i == 3)
			cout << "        前一步所下子为" << '(' << x << ',' << y << ')';
		else if (i == 5)
		{
			int num1 = 0;
			for (int t = 1; t < 9; t++)
				for (int u = 1; u < 9; u++)
				{
					if (board[t][u] == 1)
						num1 = num1 + 1;
				}
			if (num1 == 0)
				exit(0); //在这里结束程序
			cout << "        当前黑子数为:" << num1;
		}
		else if (i == 6)
		{
			int num2 = 0;
			for (int t = 1; t < 9; t++)
				for (int u = 1; u < 9; u++)
				{
					if (board[t][u] == 2)
						num2 = num2 + 1;
				}
			if (num2 == 0)
				exit(0); //在这里结束程序
			cout << "        当前白子数为:" << num2;
		}

		cout << endl;
		if (i != 8)
			cout << " ├ ─ ┼ ─ ┼ ─ ┼ ─ ┼ ─ ┼ ─ ┼ ─ ┼ ─ ┤" << endl;
		else
			cout << " └ ─ ┴ ─ ┴ ─ ┴ ─ ┴ ─ ┴ ─ ┴ ─ ┴ ─ ┘" << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "chs");
	/*初始化棋盘*/
	for (int j = 1; j < 9; j++)
		for (int i = 1; i < 9; i++)
			board[j][i] = 0;

	gameStart();
	/*初始化棋盘预先放置的棋子*/
	if (L == 1)
	{
		board[4][4] = 1;
		board[4][5] = 2;
		board[5][4] = 2;
		board[5][5] = 1;
	}
	else if (L == 2)
	{
		board[4][3] = 2;
		board[4][4] = 2;
		board[4][5] = 2;
		board[5][4] = 2;
		board[5][5] = 1;
	}

	int player; /*当前计算的玩家 1,2*/
	player = 1;
	/*当双方都可以下子*/
	while (analyzeBoard(board, 3 - player) || analyzeBoard(board, player))
	{
		/*不能下直接跳过*/
		if (!analyzeBoard(board, player))
		{
			player = 3 - player;
			continue;
		}

		/*玩家下子只放置*/
		if (player == 1)
		{
			system("cls");
			printBoard();
			int k, l;
			cout << "请输入要下的棋子坐标 横+空格+纵 ,输入 0 0 认输" << endl;
			while (cin >> k >> l)
			{
				if (k == 0)
				{
					goto surr;
				}
				else if (board[k][l] == 3)
					break;
				else
					cout << "输入棋子坐标错误，请重输" << endl;
			}
			setStone(board, 1, k, l);
			player = 3 - player;
			system("cls");
			printBoard();
		}
		/*电脑下子要分析*/
		else
		{
			Sleep(1000);
			/*拷贝分析盘*/
			for (int i = 1; i < 9; i++)
				for (int j = 1; j < 9; j++)
				{
					state[i][j] = board[i][j];
				}

			dfs(state, 1, 2);
			if (x < 1 || y < 1)
				continue;
			setStone(board, player, x, y);
			//system("cls");
			//printBoard();
			player = 3 - player;
		}
	}
	int hei = 0, bai = 0;
	system("cls");
	printBoard();
	for (int i = 1; i < 9; i++)
		for (int j = 1; j < 9; j++)
		{
			if (board[i][j] == 1)
				hei = hei + 1;
			else if (board[i][j] == 2)
				bai = bai + 1;
		}

	if (hei > bai)
		cout << "You Win\n";
	else
	surr:
		cout << "You Lose\n";
	system("pause");
	return 0;
}
