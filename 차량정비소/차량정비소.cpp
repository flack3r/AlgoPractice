#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef struct _person
{
	int num;
	int tk;
	int recepNum;
	int pairNum;
}Person;

typedef struct _Dest
{
	bool vacant;
	int remain_time;
	Person client;
}Dest;

vector<int> ai;
vector<int> bi;
int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		int N, M, K, A, B;
		scanf("%d %d %d %d %d", &N, &M, &K, &A, &B);
		vector<Dest> reception(N + 1);
		vector<Dest> repair(M + 1);
		queue<Person> watingQ;
		queue<Person> repairWatingQ;

		ai = vector<int>(N + 1);
		bi = vector<int>(M + 1);

		for (int k = 1; k <= N; k++)
		{
			int tmp;
			scanf("%d", &tmp);
			ai[k] = tmp;
			reception[k].vacant = true;
			reception[k].remain_time = tmp;

		}
		for (int k = 1; k <= M; k++)
		{
			int tmp;
			scanf("%d", &tmp);
			bi[k] = tmp;
			repair[k].vacant = true;
			repair[k].remain_time = tmp;
		}

		for (int k = 1; k <= K; k++)
		{
			int tmp;
			scanf("%d", &tmp);
			Person p;
			p.num = k;
			p.pairNum = 0;
			p.recepNum = 0;
			p.tk = tmp;
			watingQ.push(p);
		}

		int ans = 0;
		int time = 0;
		int repair_run = 0;
		int reception_run = 0;
		while (reception_run != 0 || repair_run != 0 || !watingQ.empty() || !repairWatingQ.empty())
		{
			reception_run = 0;
			repair_run = 0;
			// reception배열 순차탐색
			for (int w = 1; w <= N; w++)
			{
				Dest& tmp = reception[w];
				if (tmp.vacant != true)
				{
					tmp.remain_time -= 1;
					if (tmp.remain_time == 0)
					{
						tmp.vacant = true;
						tmp.remain_time = ai[w];
						Person x = reception[w].client;
						x.recepNum = w;
						repairWatingQ.push(x);

						if (!watingQ.empty())
						{
							Person x = watingQ.front();
							if (x.tk <= time)
							{
								watingQ.pop();
								tmp.vacant = false;
								tmp.client = x;
							}
						}
					}
				}
				else
				{
					if (!watingQ.empty())
					{
						Person x = watingQ.front();
						if (x.tk <= time)
						{
							watingQ.pop();
							tmp.vacant = false;
							tmp.client = x;
						}
					}
				}
			}

			//repair 배열 순차탐색
			for (int w = 1; w <= M; w++)
			{
				Dest& tmp = repair[w];
				if (tmp.vacant != true)
				{
					tmp.remain_time -= 1;
					if (tmp.remain_time == 0)
					{
						tmp.vacant = true;
						tmp.remain_time = bi[w];
						Person x = repair[w].client;
						x.pairNum = w;

						if (x.recepNum == A && x.pairNum == B)
							ans += x.num;

						if (!repairWatingQ.empty())
						{
							Person x = repairWatingQ.front();
							repairWatingQ.pop();
							tmp.vacant = false;
							tmp.client = x;
						}
					}
				}
				else
				{
					if (!repairWatingQ.empty())
					{
						Person x = repairWatingQ.front();
						repairWatingQ.pop();
						tmp.vacant = false;
						tmp.client = x;
					}
				}
			}
			time += 1;
			for (int w = 1; w <= N; w++)
			{
				if (reception[w].vacant != true)
					reception_run += 1;
			}

			for (int w = 1; w <= M; w++)
			{
				if (repair[w].vacant != true)
					repair_run += 1;
			}

		}
		if (ans == 0)
			ans = -1;
		printf("#%d %d\n", t, ans);
	}
}