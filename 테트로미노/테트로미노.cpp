#include <iostream>
#include <stdio.h>
#include <algorithm>

#define Check(x,y) (x <1 || x>N || y<1 || y>M)

using namespace std;
int arr[501][501] = { 0, };
int N, M;
int solve(int row, int col);
int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			scanf("%d", &arr[i][j]);
		}
	}

	int ans = 0;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			ans = max(ans, solve(i, j));
		}
	}

	printf("%d\n", ans);
	return 0;
}

int solve(int row, int col)
{
	int ans = 0;
	bool flag = true;
	int tmp = 0;
	
	//1) ----
	for (int k = 3; k >= 0; k--)
	{
		tmp = 0;
		flag = true;
		for (int i = 0; i <= 3; i++)
		{
			if (row + i -k>= 1 && row + i -k<= N)
			{
				tmp += arr[row + i-k][col];
			}
			else
			{
				flag = false;
				break;
			}
		}
		if (flag)
			ans = max(ans, tmp);
	}
	
	//2) ¤±
	tmp = 0;
	int n1_r = row, n1_c = col, n2_r = row + 1, n2_c = col, n3_r = row, n3_c = col + 1, n4_r = row + 1, n4_c = col + 1;
	if (!Check(n1_r, n1_c) && !Check(n2_r, n2_c) && !Check(n3_r, n3_c) && !Check(n4_r, n4_c))
	{
		tmp = arr[n1_r][n1_c] + arr[n2_r][n2_c] + arr[n3_r][n3_c] + arr[n4_r][n4_c];
	}
	ans = max(ans, tmp);

	n1_r = row-1, n1_c = col, n2_r = row, n2_c = col, n3_r = row-1, n3_c = col + 1, n4_r = row, n4_c = col + 1;
	if (!Check(n1_r, n1_c) && !Check(n2_r, n2_c) && !Check(n3_r, n3_c) && !Check(n4_r, n4_c))
	{
		tmp = arr[n1_r][n1_c] + arr[n2_r][n2_c] + arr[n3_r][n3_c] + arr[n4_r][n4_c];
	}
	ans = max(ans, tmp);

	n1_r = row, n1_c = col-1, n2_r = row + 1, n2_c = col-1, n3_r = row, n3_c = col, n4_r = row + 1, n4_c = col;
	if (!Check(n1_r, n1_c) && !Check(n2_r, n2_c) && !Check(n3_r, n3_c) && !Check(n4_r, n4_c))
	{
		tmp = arr[n1_r][n1_c] + arr[n2_r][n2_c] + arr[n3_r][n3_c] + arr[n4_r][n4_c];
	}
	ans = max(ans, tmp);

	n1_r = row-1, n1_c = col-1, n2_r = row, n2_c = col-1, n3_r = row-1, n3_c = col, n4_r = row, n4_c = col;
	if (!Check(n1_r, n1_c) && !Check(n2_r, n2_c) && !Check(n3_r, n3_c) && !Check(n4_r, n4_c))
	{
		tmp = arr[n1_r][n1_c] + arr[n2_r][n2_c] + arr[n3_r][n3_c] + arr[n4_r][n4_c];
	}
	ans = max(ans, tmp);
	
	//3) ¤¤
	tmp = 0;
	n1_r = row, n1_c = col, n2_r = row + 1, n2_c = col, n3_r = row+1, n3_c = col + 1, n4_r = row + 1, n4_c = col + 2;
	if (!Check(n1_r, n1_c) && !Check(n2_r, n2_c) && !Check(n3_r, n3_c) && !Check(n4_r, n4_c))
	{
		tmp = arr[n1_r][n1_c] + arr[n2_r][n2_c] + arr[n3_r][n3_c] + arr[n4_r][n4_c];
	}
	ans = max(ans, tmp);

	n1_r = row-1, n1_c = col, n2_r = row, n2_c = col, n3_r = row, n3_c = col + 1, n4_r = row, n4_c = col + 2;
	if (!Check(n1_r, n1_c) && !Check(n2_r, n2_c) && !Check(n3_r, n3_c) && !Check(n4_r, n4_c))
	{
		tmp = arr[n1_r][n1_c] + arr[n2_r][n2_c] + arr[n3_r][n3_c] + arr[n4_r][n4_c];
	}
	ans = max(ans, tmp);

	n1_r = row-1, n1_c = col-1, n2_r = row, n2_c = col-1, n3_r = row, n3_c = col, n4_r = row, n4_c = col + 1;
	if (!Check(n1_r, n1_c) && !Check(n2_r, n2_c) && !Check(n3_r, n3_c) && !Check(n4_r, n4_c))
	{
		tmp = arr[n1_r][n1_c] + arr[n2_r][n2_c] + arr[n3_r][n3_c] + arr[n4_r][n4_c];
	}
	ans = max(ans, tmp);

	n1_r = row-1, n1_c = col-2, n2_r = row, n2_c = col-2, n3_r = row, n3_c = col -1, n4_r = row, n4_c = col;
	if (!Check(n1_r, n1_c) && !Check(n2_r, n2_c) && !Check(n3_r, n3_c) && !Check(n4_r, n4_c))
	{
		tmp = arr[n1_r][n1_c] + arr[n2_r][n2_c] + arr[n3_r][n3_c] + arr[n4_r][n4_c];
	}
	ans = max(ans, tmp);

	//4) ¤Ç
	n1_r = row, n1_c = col, n2_r = row+1, n2_c = col - 1, n3_r = row+1, n3_c = col, n4_r = row+1, n4_c = col+1;
	if (!Check(n1_r, n1_c) && !Check(n2_r, n2_c) && !Check(n3_r, n3_c) && !Check(n4_r, n4_c))
	{
		tmp = arr[n1_r][n1_c] + arr[n2_r][n2_c] + arr[n3_r][n3_c] + arr[n4_r][n4_c];
	}
	ans = max(ans, tmp);

	n1_r = row - 1, n1_c = col + 1, n2_r = row, n2_c = col, n3_r = row, n3_c = col + 1, n4_r = row, n4_c = col+2;
	if (!Check(n1_r, n1_c) && !Check(n2_r, n2_c) && !Check(n3_r, n3_c) && !Check(n4_r, n4_c))
	{
		tmp = arr[n1_r][n1_c] + arr[n2_r][n2_c] + arr[n3_r][n3_c] + arr[n4_r][n4_c];
	}
	ans = max(ans, tmp);

	n1_r = row - 1, n1_c = col, n2_r = row, n2_c = col - 1, n3_r = row, n3_c = col, n4_r = row, n4_c = col+1;
	if (!Check(n1_r, n1_c) && !Check(n2_r, n2_c) && !Check(n3_r, n3_c) && !Check(n4_r, n4_c))
	{
		tmp = arr[n1_r][n1_c] + arr[n2_r][n2_c] + arr[n3_r][n3_c] + arr[n4_r][n4_c];
	}
	ans = max(ans, tmp);

	n1_r = row - 1, n1_c = col - 1, n2_r = row, n2_c = col - 2, n3_r = row, n3_c = col - 1, n4_r = row, n4_c = col;
	if (!Check(n1_r, n1_c) && !Check(n2_r, n2_c) && !Check(n3_r, n3_c) && !Check(n4_r, n4_c))
	{
		tmp = arr[n1_r][n1_c] + arr[n2_r][n2_c] + arr[n3_r][n3_c] + arr[n4_r][n4_c];
	}
	ans = max(ans, tmp);

	//5) z
	n1_r = row - 1, n1_c = col - 2, n2_r = row, n2_c = col - 2, n3_r = row, n3_c = col - 1, n4_r = row, n4_c = col;
	if (!Check(n1_r, n1_c) && !Check(n2_r, n2_c) && !Check(n3_r, n3_c) && !Check(n4_r, n4_c))
	{
		tmp = arr[n1_r][n1_c] + arr[n2_r][n2_c] + arr[n3_r][n3_c] + arr[n4_r][n4_c];
	}
	ans = max(ans, tmp);

	n1_r = row - 1, n1_c = col - 2, n2_r = row, n2_c = col - 2, n3_r = row, n3_c = col - 1, n4_r = row, n4_c = col;
	if (!Check(n1_r, n1_c) && !Check(n2_r, n2_c) && !Check(n3_r, n3_c) && !Check(n4_r, n4_c))
	{
		tmp = arr[n1_r][n1_c] + arr[n2_r][n2_c] + arr[n3_r][n3_c] + arr[n4_r][n4_c];
	}
	ans = max(ans, tmp);

	n1_r = row - 1, n1_c = col - 2, n2_r = row, n2_c = col - 2, n3_r = row, n3_c = col - 1, n4_r = row, n4_c = col;
	if (!Check(n1_r, n1_c) && !Check(n2_r, n2_c) && !Check(n3_r, n3_c) && !Check(n4_r, n4_c))
	{
		tmp = arr[n1_r][n1_c] + arr[n2_r][n2_c] + arr[n3_r][n3_c] + arr[n4_r][n4_c];
	}
	ans = max(ans, tmp);

	n1_r = row - 1, n1_c = col - 2, n2_r = row, n2_c = col - 2, n3_r = row, n3_c = col - 1, n4_r = row, n4_c = col;
	if (!Check(n1_r, n1_c) && !Check(n2_r, n2_c) && !Check(n3_r, n3_c) && !Check(n4_r, n4_c))
	{
		tmp = arr[n1_r][n1_c] + arr[n2_r][n2_c] + arr[n3_r][n3_c] + arr[n4_r][n4_c];
	}
	ans = max(ans, tmp);
	return ans;
}