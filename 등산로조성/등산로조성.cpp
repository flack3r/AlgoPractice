#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <stdio.h>

using namespace std;

vector< vector<int> > arr;
vector< vector< bool > > visit;
int dRow[4] = { 0,0,1,-1 };
int dCol[4] = { 1,-1,0,0 };
int N, K;
int solve(int i, int j, int k);

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		scanf("%d %d", &N, &K);
		arr = vector< vector<int> >(N + 1, vector<int>(N + 1));
		int H = 0;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				int tmp;
				scanf("%d", &tmp);
				arr[i][j] = tmp;
				H = max(H, tmp);
			}
		}

		queue< pair<int, int> > q;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (arr[i][j] == H)
					q.push(make_pair(i, j));
			}
		}

		int ans = 0;
		while (!q.empty())
		{
			visit = vector< vector<bool> >(N + 1, vector<bool>(N + 1, false));
			pair<int, int> tmp = q.front();
			q.pop();
			//printf("start: %d , %d\n", tmp.first, tmp.second);
			visit[tmp.first][tmp.second] = true;
			ans = max(ans, solve(tmp.first, tmp.second, K));
		}

		printf("#%d %d\n", t, ans);
	}
	return 0;
}

int solve(int i, int j, int k)
{
	//printf("%d %d visit\n", i, j);
	int ans = 0;
	for (int d = 0; d < 4; d++)
	{
		int next_row = i + dRow[d];
		int next_col = j + dCol[d];
		if (next_row < 1 || next_row > N || next_col < 1 || next_col > N)
			continue;

		//낮은 곳으로 그냥 감.
		if (arr[next_row][next_col] < arr[i][j] && !visit[next_row][next_col])
		{
			visit[next_row][next_col] = true;
			ans = max(ans, solve(next_row, next_col, k));
			visit[next_row][next_col] = false;
		}
		else
		{
			int tmp = arr[next_row][next_col];
			for (int tmpk = 1; tmpk <= k; tmpk++)
			{
				if (tmp - tmpk < arr[i][j] && !visit[next_row][next_col])
				{
					arr[next_row][next_col] -= tmpk;
					visit[next_row][next_col] = true;
					ans = max(ans, solve(next_row, next_col, 0));
					visit[next_row][next_col] = false;
					arr[next_row][next_col] += tmpk;
				}
			}
		}
	}
	return ans + 1;
}