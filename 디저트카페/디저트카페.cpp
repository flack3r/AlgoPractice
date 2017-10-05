#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

#define LU 1
#define LD 3
#define RU 0
#define RD 2
using namespace std;

int N;
vector< vector<int> > map;
vector< vector<int> > visit;
vector<int> desert;

bool first = false;
int di, dj;
int dRow[4] = { 1,1,-1,-1 };
int dCol[4] = { 1,-1,1,-1 };
int solve(int i, int j, int stage);
int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		N;
		scanf("%d", &N);
		map = vector< vector<int> >(N + 1, vector<int>(N + 1));
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				int tmp;
				scanf("%d", &tmp);
				map[i][j] = tmp;
			}
		}

		int ans = -1;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				di = i;
				dj = j;
				visit = vector< vector<int> >(N + 1, vector<int>(N + 1));
				desert.clear();
				first = true;
				ans = max(ans, solve(i, j, 1));
			}
		}
		printf("#%d %d\n", t, ans);
	}
	return 0;
}

int solve(int i, int j, int stage)
{
	if (i == di && j == dj)
	{
		if (first == false)
		{
			/*
			printf("start: %d %d, route: ", di, dj);
			for (int k = 0; k < desert.size(); k++)
			{
			printf("%d ", desert[k]);
			}
			printf("\n");
			*/
			if (desert.size() == 2)
				return -1;
			else
				return desert.size();
		}
	}


	for (int k = 0; k < desert.size(); k++)
	{
		if (desert[k] == map[i][j])
			return -1;
	}

	int ans = -1;
	int next_row = 0;
	int next_col = 0;
	switch (stage)
	{
		// stage1
	case 1:
		if (first)
		{
			next_row = i + dRow[0];
			next_col = j + dCol[0];
			if (next_row < 1 || next_row > N || next_col < 1 || next_col > N)
				ans = -1;
			else
			{
				first = false;
				desert.push_back(map[i][j]);
				ans = max(ans, solve(next_row, next_col, stage));
				desert.pop_back();
			}
		}
		else
		{
			//대각선아래로 내려감
			next_row = i + dRow[0];
			next_col = j + dCol[0];
			if (!(next_row < 1 || next_row > N || next_col < 1 || next_col > N))
			{
				desert.push_back(map[i][j]);
				ans = max(ans, solve(next_row, next_col, stage));
				desert.pop_back();
			}

			//대각선 위로 올라감.
			next_row = i + dRow[2];
			next_col = j + dCol[2];
			if (!(next_row < 1 || next_row > N || next_col < 1 || next_col > N))
			{
				desert.push_back(map[i][j]);
				ans = max(ans, solve(next_row, next_col, stage + 1));
				desert.pop_back();
			}
		}
		break;
		// stage2
	case 2:
		//대각선아래로 내려감
		next_row = i + dRow[2];
		next_col = j + dCol[2];
		if (!(next_row < 1 || next_row > N || next_col < 1 || next_col > N))
		{
			desert.push_back(map[i][j]);
			ans = max(ans, solve(next_row, next_col, stage));
			desert.pop_back();
		}

		//대각선 위로 올라감.
		next_row = i + dRow[3];
		next_col = j + dCol[3];
		if (!(next_row < 1 || next_row > N || next_col < 1 || next_col > N))
		{
			desert.push_back(map[i][j]);
			ans = max(ans, solve(next_row, next_col, stage + 1));
			desert.pop_back();
		}
		break;

		//stage 3
	case 3:
		//대각선아래로 내려감
		next_row = i + dRow[3];
		next_col = j + dCol[3];
		if (!(next_row < 1 || next_row > N || next_col < 1 || next_col > N))
		{
			desert.push_back(map[i][j]);
			ans = max(ans, solve(next_row, next_col, stage));
			desert.pop_back();
		}

		//대각선 위로 올라감.
		next_row = i + dRow[1];
		next_col = j + dCol[1];
		if (!(next_row < 1 || next_row > N || next_col < 1 || next_col > N))
		{
			desert.push_back(map[i][j]);
			ans = max(ans, solve(next_row, next_col, stage + 1));
			desert.pop_back();
		}
		break;
		//stage 4
	case 4:
		//대각선아래로 내려감
		next_row = i + dRow[1];
		next_col = j + dCol[1];
		if (!(next_row < 1 || next_row > N || next_col < 1 || next_col > N))
		{
			desert.push_back(map[i][j]);
			ans = max(ans, solve(next_row, next_col, stage));
			desert.pop_back();
		}
		break;
	}
	return ans;
}