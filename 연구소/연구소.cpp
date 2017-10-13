#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

vector< vector<int> > arr;
vector< pair<int,int> > virus;
vector< pair<int, int> > Safety;
vector< vector<bool> > visit;
int wallCount;
int N, M;
int solve();
int bfs(int row, int col);
void InitVisit();
int main()
{
	wallCount = 0;
	scanf("%d %d", &N, &M);
	arr = vector< vector<int> >(N + 1, vector<int>(M + 1));
	visit = vector<vector<bool>>(N + 1, vector<bool>(M + 1, false));
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			int tmp;
			scanf("%d", &tmp);
			arr[i][j] = tmp;
			if (tmp == 1)
				wallCount += 1;
			if (tmp == 2)
				virus.push_back(make_pair(i, j));
			else if(tmp == 0)
				Safety.push_back(make_pair(i, j));
		}
	}

	int ans = solve();
	printf("%d\n", ans);
	return 0;
}

int solve()
{	
	int ans = 0;
	vector<int> wall(Safety.size(), 0);
	wall[Safety.size()-1] = 1; wall[Safety.size() - 2] = 1; wall[Safety.size() - 3] = 1;
	do
	{
		vector< pair<int, int> > putWall;
		for (int i = 0; i < Safety.size(); i++)
		{
			if (wall[i] == 1)
			{
				putWall.push_back(Safety[i]);
			}
		}

		//setting
		for (int i = 0; i < 3; i++)
		{
			int prow = putWall[i].first;
			int pcol = putWall[i].second;
			arr[prow][pcol] = 1;
			//printf("(%d %d) ", prow, pcol);
		}

		int tmp_count = 0;
		InitVisit();
		for (int i = 0; i < virus.size(); i++)
		{
			tmp_count += bfs(virus[i].first, virus[i].second);
		}
		ans = max(ans, N*M - tmp_count - wallCount - 3);
		
		//restore
		for (int i = 0; i < 3; i++)
		{
			int prow = putWall[i].first;
			int pcol = putWall[i].second;
			arr[prow][pcol] = 0;
		}
	} while (next_permutation(wall.begin(), wall.end()));

	return ans;
}

int bfs(int row, int col)
{
	int dRow[4] = { 0,0,1,-1 };
	int dCol[4] = { -1,1,0,0 };
	int virusCount = 0;
	queue < pair<int, int> > q;
	q.push(make_pair(row, col));

	while (!q.empty())
	{
		pair<int, int> tmp = q.front();
		int current_row = tmp.first;
		int current_col = tmp.second;
		q.pop();
		if (visit[current_row][current_col])
			continue;

		virusCount += 1;
		visit[current_row][current_col] = true;
		for (int i = 0; i < 4; i++)
		{
			int next_row = current_row + dRow[i];
			int next_col = current_col + dCol[i];
			if (next_row < 1 || next_row > N || next_col < 1 || next_col > M)
				continue;
			
			if (!visit[next_row][next_col] && arr[next_row][next_col] == 0)
				q.push(make_pair(next_row, next_col));
		}
	}

	return virusCount;
}

void InitVisit()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
			visit[i][j] = false;
	}
}