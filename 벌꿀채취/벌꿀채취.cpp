#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

vector< vector<int> > arr;
int N, M, C;
int GetHouney(vector<int>& input);
int solve(int, int);
int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		scanf("%d %d %d", &N, &M, &C);
		arr = vector< vector<int> >(N + 1, vector<int>(N + 1));
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				int tmp;
				scanf("%d", &tmp);
				arr[i][j] = tmp;
			}
		}

		int ans = 0;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				ans = max(ans, solve(i, j));
			}
		}

		printf("#%d %d\n", t, ans);
	}

	return 0;
}

int GetHouney(vector<int>& input)
{
	int ans = 0;
	for (int i = 1; i < (1 << input.size()); i++)
	{
		int tmp = 0;
		int tmp_ans = 0;
		for (int k = 0; k < input.size(); k++)
		{
			if ((i & (1 << k)) >> k == 1)
			{
				tmp += input[k];
				tmp_ans += input[k] * input[k];
			}
		}
		if (tmp > C)
			continue;
		else
		{
			ans = max(ans, tmp_ans);
		}
	}
	return ans;
}

// solve -> (i,j)에서 M만큼 선택함.
int solve(int row, int col)
{
	if (row<1 || row>N || col < 1 || col > N)
		return 0;

	if (col + M - 1> N)
		return 0;

	int ans = 0;

	//printf("go %d, %d\n", row, col);
	//first
	vector<int> buck;
	for (int i = 0; i < M; i++)
	{
		buck.push_back(arr[row][col + i]);
	}
	ans = GetHouney(buck);

	//second
	int second_ans = 0;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c + M - 1 <= N; c += 1)
		{
			if ((r < row) || (r == row && c<col + M))
				continue;
			vector<int> buck;
			//printf("next\n");
			for (int i = 0; i < M; i++)
			{
				buck.push_back(arr[r][c + i]);
				//printf("visit %d, %d\n", r, c+i);
			}
			second_ans = max(second_ans, GetHouney(buck));
		}
	}
	return ans + second_ans;
}