#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
int N, M;
vector< vector<int> > map;
int solve(int i, int j, int k);
int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		scanf("%d %d", &N, &M);
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

		int ans = 0;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				for (int k = 0; k <= 24; k++)
				{
					ans = max(ans, solve(i, j, k));
					//printf("\n");
				}
			}
		}
		printf("#%d %d\n", t, ans);
	}
}

//집 수의 최대값
int solve(int i, int j, int k)
{
	int count = 0;
	for (int y = -k + i; y <= k + i; y++)
	{
		for (int x = -k + j; x <= k + j; x++)
		{
			if ((i + j - k <= x + y) && (x + y <= i + j + k) && (i - j - k <= y - x) && (y - x <= i - j + k))
			{
				//printf("(%d, %d) ", y, x);
				if (x >= 1 && x <= N && y >= 1 && y <= N)
				{
					if (map[y][x] == 1)
					{
						count += 1;
					}
				}
			}
		}
	}
	//printf("\n");

	k += 1;
	int cost = k*k + (k - 1)*(k - 1);
	if (cost > count*M)
		return 0;
	else
		return count;
}