#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define INF 2e8
using namespace std;
int D, W, K;
int CheckArr[21];
bool Check();
int Count[1 << 13];
int solve(int row);
int main()
{
	int T;
	scanf("%d", &T);

	//bit counting
	for (int i = 0; i < (1 << 13); i++)
	{
		int z = i;
		int maxS = 0;
		int sum = 0;
		while (z != 0)
		{
			if ((z & 1) == 1)
			{
				sum += 1;
			}
			else
			{
				maxS = max(maxS, sum);
				sum = 0;
			}
			z /= 2;
		}
		maxS = max(maxS, sum);
		Count[i] = maxS;
	}

	for (int t = 1; t <= T; t++)
	{
		int ans = 0;
		memset(CheckArr, 0, sizeof(int) * 21);
		scanf("%d %d %d", &D, &W, &K);
		for (int i = 1; i <= D; i++)
		{
			for (int j = 1; j <= W; j++)
			{
				int tmp;
				scanf("%d", &tmp);
				if(tmp != 0)
					CheckArr[i] |= (1<<(W-j));
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
	int origin = CheckArr[row];
	CheckArr[row] = 0;
	ans = min(ans, solve(row + 1) + 1);
	CheckArr[row] = origin;

	//case2 B로 바꾸는 경우
	CheckArr[row] |= ((1 << W)-1);
	ans = min(ans, solve(row + 1) + 1);
	CheckArr[row] = origin;
	
	return ans;
}

bool Check()
{
	bool check = true;
	bool checkA = true;
	bool checkB = true;
	for (int k = 1; k <= W; k++)
	{
		int tmp = 0;
		checkA = true;
		checkB = true;
		for (int r = 1; r <= D; r++)
		{
			int current = (CheckArr[r] >> (k - 1)) & 1;
			tmp |= (current << (r-1));
		}
		
		if (Count[tmp] < K)
			checkA = false;
		
		int tmp2 = (~tmp) & ((1 << D) - 1);
		if (Count[tmp2] < K)
			checkB = false;

		if (!checkA && !checkB)
		{
			check = false;
			break;
		}
	}
	
	return check;
}