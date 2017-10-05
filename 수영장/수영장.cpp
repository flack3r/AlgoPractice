#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define INTMAX 2e8
using namespace std;

int day, month, thirdM, year;
vector<int> w;
int solve(int i);
int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		int ans = INTMAX;
		w = vector<int>(13);
		int start = 0;
		scanf("%d %d %d %d", &day, &month, &thirdM, &year);
		for (int i = 1; i <= 12; i++)
		{
			int tmp;
			scanf("%d", &tmp);
			w[i] = tmp;
			if (tmp != 0 && start != 0)
				start = i;
		}

		
		ans = solve(start);
		printf("#%d %d\n", t, ans);
	}
	return 0;
}

int solve(int i)
{
	if (i > 12)
		return 0;
	if (w[i] == 0)
		return solve(i + 1);

	int ans = INTMAX;
	//하루치
	ans = min(ans, solve(i + 1) + w[i]*day);
	//한달치
	ans = min(ans, solve(i + 1) + month);
	//세달치
	ans = min(ans, solve(i + 3) + thirdM);
	//1년치
	ans = min(ans, year);
	
	return ans;
}