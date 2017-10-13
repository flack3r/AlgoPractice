#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
vector< pair<int, int> > w;
int N;
int solve(int day);
int main()
{
	scanf("%d", &N);
	w = vector< pair<int, int> >(N + 1);
	for (int i = 1; i <= N; i++)
	{
		int T, P;
		scanf("%d %d", &T, &P);
		w[i] = make_pair(T, P);
	}

	int ans = solve(1);
	printf("%d\n", ans);
	return 0;
}

int solve(int day)
{
	if (day >= N + 1)
	{
		return 0;
	}

	int ans = 0;
	//day에 일을 할 경우.
	int next_day = day + w[day].first;
	if(next_day <= N+1)
		ans = max(ans, solve(next_day) + w[day].second);
	
	//day에 일을 하지 않을경우
	ans = max(ans, solve(day + 1));

	return ans;
}