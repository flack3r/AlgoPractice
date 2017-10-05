#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>

#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

using namespace std;
int N, M;
vector< vector<int> > arr;
int dRow[4] = { 0,0,-1,1 };
int dCol[4] = { 1,-1,0,0 };

int bfs(int row, int col, int time);
int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		int row, col, time;
		scanf("%d %d %d %d %d", &N, &M, &row, &col, &time);
		arr = vector< vector<int> >(N + 1, vector<int>(M + 1));
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= M; j++)
			{
				int tmp;
				scanf("%d", &tmp);
				arr[i][j] = tmp;
			}
		}

		int ans = bfs(row + 1, col + 1, time);
		if (ans == 1)
			printf("#%d %d\n", t, ans);
		else
			printf("#%d %d\n", t, ans - 1);
	}
	return 0;
}

int bfs(int row, int col, int time)
{
	queue< pair<int, int> > q;
	queue< pair<int, int> > next_q;
	vector< vector<int> > visit(N + 1, vector<int>(M + 1, 0));
	int count = 0;
	int tick = 1;
	q.push(make_pair(row, col));
	while (!q.empty())
	{
		pair<int, int> tmp = q.front();
		q.pop();
		count += 1;
		int next_row;
		int next_col;

		for (int z = 0; z < 4; z++)
		{
			next_row = tmp.first + dRow[z];
			next_col = tmp.second + dCol[z];

			if (next_row < 1 || next_row > N || next_col <1 || next_col > M)
				continue;

			int next_draw = arr[next_row][next_col];
			switch (arr[tmp.first][tmp.second])
			{
			case 1:
				if (z == UP)
				{
					if (next_draw == 1 || next_draw == 2 || next_draw == 5 || next_draw == 6)
					{
						if (visit[next_row][next_col] != 1)
						{
							visit[next_row][next_col] = 1;
							next_q.push(make_pair(next_row, next_col));
						}
					}
				}
				else if (z == DOWN)
				{
					if (next_draw == 1 || next_draw == 2 || next_draw == 4 || next_draw == 7)
					{
						if (visit[next_row][next_col] != 1)
						{
							visit[next_row][next_col] = 1;
							next_q.push(make_pair(next_row, next_col));
						}
					}
				}
				else if (z == LEFT)
				{
					if (next_draw == 1 || next_draw == 3 || next_draw == 4 || next_draw == 5)
					{
						if (visit[next_row][next_col] != 1)
						{
							visit[next_row][next_col] = 1;
							next_q.push(make_pair(next_row, next_col));
						}
					}
				}
				else if (z == RIGHT)
				{
					if (next_draw == 1 || next_draw == 3 || next_draw == 6 || next_draw == 7)
					{
						if (visit[next_row][next_col] != 1)
						{
							visit[next_row][next_col] = 1;
							next_q.push(make_pair(next_row, next_col));
						}
					}
				}
				break;
			case 2:
				if (z == UP)
				{
					if (next_draw == 1 || next_draw == 2 || next_draw == 5 || next_draw == 6)
					{
						if (visit[next_row][next_col] != 1)
						{
							visit[next_row][next_col] = 1;
							next_q.push(make_pair(next_row, next_col));
						}
					}
				}
				else if (z == DOWN)
				{
					if (next_draw == 1 || next_draw == 2 || next_draw == 4 || next_draw == 7)
					{
						if (visit[next_row][next_col] != 1)
						{
							visit[next_row][next_col] = 1;
							next_q.push(make_pair(next_row, next_col));
						}
					}
				}
				break;
			case 3:
				if (z == LEFT)
				{
					if (next_draw == 1 || next_draw == 3 || next_draw == 4 || next_draw == 5)
					{
						if (visit[next_row][next_col] != 1)
						{
							visit[next_row][next_col] = 1;
							next_q.push(make_pair(next_row, next_col));
						}
					}
				}
				else if (z == RIGHT)
				{
					if (next_draw == 1 || next_draw == 3 || next_draw == 6 || next_draw == 7)
					{
						if (visit[next_row][next_col] != 1)
						{
							visit[next_row][next_col] = 1;
							next_q.push(make_pair(next_row, next_col));
						}
					}
				}
				break;
			case 4:
				if (z == UP)
				{
					if (next_draw == 1 || next_draw == 2 || next_draw == 5 || next_draw == 6)
					{
						if (visit[next_row][next_col] != 1)
						{
							visit[next_row][next_col] = 1;
							next_q.push(make_pair(next_row, next_col));
						}
					}
				}
				else if (z == RIGHT)
				{
					if (next_draw == 1 || next_draw == 3 || next_draw == 6 || next_draw == 7)
					{
						if (visit[next_row][next_col] != 1)
						{
							visit[next_row][next_col] = 1;
							next_q.push(make_pair(next_row, next_col));
						}
					}
				}
				break;
			case 5:
				if (z == DOWN)
				{
					if (next_draw == 1 || next_draw == 2 || next_draw == 4 || next_draw == 7)
					{
						if (visit[next_row][next_col] != 1)
						{
							visit[next_row][next_col] = 1;
							next_q.push(make_pair(next_row, next_col));
						}
					}
				}
				else if (z == RIGHT)
				{
					if (next_draw == 1 || next_draw == 3 || next_draw == 6 || next_draw == 7)
					{
						if (visit[next_row][next_col] != 1)
						{
							visit[next_row][next_col] = 1;
							next_q.push(make_pair(next_row, next_col));
						}
					}
				}
				break;
			case 6:
				if (z == LEFT)
				{
					if (next_draw == 1 || next_draw == 3 || next_draw == 4 || next_draw == 5)
					{
						if (visit[next_row][next_col] != 1)
						{
							visit[next_row][next_col] = 1;
							next_q.push(make_pair(next_row, next_col));
						}
					}
				}
				else if (z == DOWN)
				{
					if (next_draw == 1 || next_draw == 2 || next_draw == 4 || next_draw == 7)
					{
						if (visit[next_row][next_col] != 1)
						{
							visit[next_row][next_col] = 1;
							next_q.push(make_pair(next_row, next_col));
						}
					}
				}
				break;
			case 7:
				if (z == LEFT)
				{
					if (next_draw == 1 || next_draw == 3 || next_draw == 4 || next_draw == 5)
					{
						if (visit[next_row][next_col] != 1)
						{
							visit[next_row][next_col] = 1;
							next_q.push(make_pair(next_row, next_col));
						}
					}
				}
				else if (z == UP)
				{
					if (next_draw == 1 || next_draw == 2 || next_draw == 5 || next_draw == 6)
					{
						if (visit[next_row][next_col] != 1)
						{
							visit[next_row][next_col] = 1;
							next_q.push(make_pair(next_row, next_col));
						}
					}
				}
				break;
			}
		}

		if (q.empty() && tick < time)
		{
			while (!next_q.empty())
			{
				q.push(next_q.front());
				next_q.pop();
			}
			tick += 1;
		}
	}

	return count;
}