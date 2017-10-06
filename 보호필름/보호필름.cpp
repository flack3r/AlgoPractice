#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define INF 2e8
using namespace std;
int D, W, K;
vector< vector<int> > arr;
bool Check();
bool Promising();
int solve(int row);
int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		int ans = 0;
		scanf("%d %d %d", &D, &W, &K);
		arr = vector< vector<int> >(D + 1, vector<int>(W + 1));
		for (int i = 1; i <= D; i++)
		{
			for (int j = 1; j <= W; j++)
			{
				int tmp;
				scanf("%d", &tmp);
				arr[i][j] = tmp;
			}
		}
		
		ans = solve(1);
		printf("#%d %d\n", t, ans);
	}
	return 0;
}

int solve(int row)
{
	//기저조건 다 칠했을 때
	if (row == D + 1)
	{
		if (Check())
			return 0;
		else
			return INF;
	}

	//안칠하는 경우
	if (Check())
		return 0;
	int ans = INF;
	ans = min(ans, solve(row + 1));

	//case1 A로 바꾸는 경우
	vector<int> original;
	for (int c = 1; c <= W; c++)
	{
		original.push_back(arr[row][c]);
		arr[row][c] = 0;
	}
	ans = min(ans, solve(row + 1) + 1);
	for (int c = 1; c <= W; c++)
		arr[row][c] = original[c - 1];
	
	//case2 B로 바꾸는 경우
	original.clear();
	for (int c = 1; c <= W; c++)
	{
		original.push_back(arr[row][c]);
		arr[row][c] = 1;
	}
	ans = min(ans, solve(row + 1) + 1);
	for (int c = 1; c <= W; c++)
		arr[row][c] = original[c - 1];
	
	return ans;
}

bool Check()
{
	for (int c = 1; c <= W; c++)
	{
		int tmp = 0;
		int before = -1;
		for (int r = 1; r <= D; r++)
		{
			if (before == -1)
			{
				before = arr[r][c];
				tmp = 1;
			}
			else
			{
				if (arr[r][c] == before)
					tmp += 1;
				else
				{
					tmp = 1;
					before = arr[r][c];
				}
			}

			if (tmp >= K)
				break;
		}
		if (tmp < K)
			return false;
	}
	return true;
}