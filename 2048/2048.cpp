#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define UP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4
using namespace std;
int N;

void Print(vector<vector<int>> maps);
void Log(vector<vector<int>> maps);
long long solve(vector<vector<int>> maps, int k);
void move(vector<vector<int>>& maps, int mode);
int main()
{
	scanf("%d", &N);
	vector<vector<int>> maps = vector<vector<int>>(N + 1, vector<int>(N + 1));
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			int tmp;
			scanf("%d", &tmp);
			maps[i][j] = tmp;
		}
	}

	//Log(maps);
	long long ans = solve(maps, 1);
	printf("%lld\n", ans);
	return 0;
}

void Log(vector<vector<int>> maps)
{
	vector<vector<int>> tmp = maps;
	printf("UP\n");
	move(tmp, LEFT);
	Print(tmp);
}

void Print(vector<vector<int>> maps)
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			printf("%d ", maps[i][j]);
		}
		printf("\n");
	}
}
void move(vector<vector<int>>& maps, int mode)
{
	vector<vector<bool>> collision = vector<vector<bool>>(N + 1, vector<bool>(N + 1, false));
	switch (mode)
	{
	case UP:
		for (int col = 1; col <= N; col++)
		{
			for (int row = 1; row <= N; row++)
			{
				int check = maps[row][col];
				if (check == 0)
					continue;
				for (int up = row - 1; up >= 1; up--)
				{
					if (check == maps[up][col] && !collision[up][col])
					{
						collision[up][col] = true;
						maps[row][col] = 0;
						maps[up][col] += check;
						break;
					}
					else if (maps[up][col] != 0)
					{
						maps[row][col] = 0;
						maps[up + 1][col] = check;
						break;
					}
					else if (up == 1 && maps[up][col] == 0)
					{
						maps[row][col] = 0;
						maps[up][col] = check;
					}
				}
			}
		}
		break;
	case DOWN:
		for (int col = 1; col <= N; col++)
		{
			for (int row = N; row >= 1; row--)
			{
				int check = maps[row][col];
				if (check == 0)
					continue;
				for (int down = row + 1; down <= N; down++)
				{
					if (check == maps[down][col] && !collision[down][col])
					{
						collision[down][col] = true;
						maps[row][col] = 0;
						maps[down][col] += check;
						break;
					}
					else if (maps[down][col] != 0)
					{
						maps[row][col] = 0;
						maps[down - 1][col] = check;
						break;
					}
					else if (down == N && maps[down][col] == 0)
					{
						maps[row][col] = 0;
						maps[down][col] = check;
					}
				}
			}
		}
		break;
	case LEFT:
		for (int row = 1; row <= N; row++)
		{
			for (int col = 1; col <= N; col++)
			{
				int check = maps[row][col];
				if (check == 0)
					continue;
				for (int left = col - 1; left >= 1; left--)
				{
					if (check == maps[row][left] && !collision[row][left])
					{
						collision[row][left] = true;
						maps[row][col] = 0;
						maps[row][left] += check;
						break;
					}
					else if (maps[row][left] != 0)
					{
						maps[row][col] = 0;
						maps[row][left + 1] = check;
						break;
					}
					else if (left == 1 && maps[row][left] == 0)
					{
						maps[row][col] = 0;
						maps[row][left] = check;
					}
				}
			}
		}
		break;
	case RIGHT:
		for (int row = 1; row <= N; row++)
		{
			for (int col = N; col >= 1; col--)
			{
				int check = maps[row][col];
				if (check == 0)
					continue;
				for (int right = col + 1; right <= N; right++)
				{
					if (check == maps[row][right] && !collision[row][right])
					{
						collision[row][right] = true;
						maps[row][col] = 0;
						maps[row][right] += check;
						break;
					}
					else if (maps[row][right] != 0)
					{
						maps[row][col] = 0;
						maps[row][right - 1] = check;
						break;
					}
					else if (right == N && maps[row][right] == 0)
					{
						maps[row][col] = 0;
						maps[row][right] = check;
					}
				}
			}
		}
		break;
	}
}

long long solve(vector<vector<int>> maps, int k)
{
	//기저조건
	if (k == 6)
	{
		long long MaxV = 0;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (MaxV < maps[i][j])
					MaxV = maps[i][j];
			}
		}
		return MaxV;
	}

	long long ans = 0;
	vector<vector<int>> tmp = maps;

	// move UP
	move(tmp, UP);
	ans = max(ans, solve(tmp, k + 1));
	tmp = maps;

	// move LEFT
	move(tmp, LEFT);
	ans = max(ans, solve(tmp, k + 1));
	tmp = maps;

	// move RIGHT
	move(tmp, RIGHT);
	ans = max(ans, solve(tmp, k + 1));
	tmp = maps;

	// move DOWN
	move(tmp, DOWN);
	ans = max(ans, solve(tmp, k + 1));
	tmp = maps;

	return ans;
}
