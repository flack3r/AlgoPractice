#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue> 
#include <list>
#define INF 2e8
using namespace std;

typedef struct _Person
{
	int row;
	int col;
	int time;
	int ladderTime;
}Person;

typedef struct _Ladder
{
	int row;
	int col;
	int length;
	list<Person> person;
}Ladder;

vector<Person> p;
vector<Person> ladders[2];
Ladder ladderA;
Ladder ladderB;

int solve(int idx);
bool cmp(Person a, Person b);
bool removeLadder(Person x)
{
	return x.ladderTime == 0;
}
int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		int N;
		scanf("%d", &N);
		p.clear();
		ladders[0].clear();
		ladders[1].clear();
		int laddercount = 0;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				int tmp = 0;
				scanf("%d", &tmp);
				if (tmp == 1)
				{
					Person tmpP;
					tmpP.row = i;
					tmpP.col = j;
					tmpP.time = 0;
					p.push_back(tmpP);
				}
				else if (tmp >= 2)
				{
					if (laddercount == 0)
					{
						ladderA.row = i;
						ladderA.col = j;
						ladderA.length = tmp;
					}
					else
					{
						ladderB.row = i;
						ladderB.col = j;
						ladderB.length = tmp;
					}
					laddercount += 1;
				}
			}
		}
		
		int ans = solve(0);
		printf("#%d %d\n", t, ans);
	}
	return 0;
}

int solve(int idx)
{
	//기저조건 시뮬레이션
	if (idx >= p.size())
	{
		int time = 0;
		queue<Person> ladderAQ;
		queue<Person> ladderBQ;

		vector<Person> tmp = ladders[0];
		sort(tmp.begin(), tmp.end(), cmp);
		for (int i = 0; i < tmp.size(); i++)
		{
			ladderAQ.push(tmp[i]);
		}

		tmp = ladders[1];
		sort(tmp.begin(), tmp.end(), cmp);
		for (int i = 0; i < tmp.size(); i++)
		{
			ladderBQ.push(tmp[i]);
		}
		
		while (!ladderAQ.empty() || !ladderBQ.empty() || ladderA.person.size() != 0 || ladderB.person.size() != 0)
		{
			time += 1;
			//ladderA부터 처리
			//내리기
			for (list<Person>::iterator it = ladderA.person.begin(); it != ladderA.person.end(); it++)
			{
				Person& z = *it;
				z.ladderTime -= 1;
			}
			ladderA.person.remove_if(removeLadder);

			for (int count = 1; count <= 3 && !ladderAQ.empty(); count++)
			{
				if (ladderAQ.front().time <= time && ladderA.person.size() < 3)
				{
					Person z = ladderAQ.front();
					z.ladderTime = ladderA.length;
					ladderAQ.pop();
					ladderA.person.push_back(z);
				}
			}

			//ladderB
			//내리기
			for (list<Person>::iterator it = ladderB.person.begin(); it != ladderB.person.end(); it++)
			{
				Person& z = *it;
				z.ladderTime -= 1;
			}
			ladderB.person.remove_if(removeLadder);

			for (int count = 1; count <= 3 && !ladderBQ.empty(); count++)
			{
				if (ladderBQ.front().time <= time && ladderB.person.size() < 3)
				{
					Person z = ladderBQ.front();
					z.ladderTime = ladderB.length;
					ladderBQ.pop();
					ladderB.person.push_back(z);
				}
			}
		}
		return time;
	}
	
	int ans = INF;
	Person tmp = p[idx];
	//stage1. 첫번째 사다리로 갈 경우.
	tmp.time = abs(tmp.row - ladderA.row) + abs(tmp.col - ladderA.col) + 1;
	ladders[0].push_back(tmp);
	ans = min(ans, solve(idx + 1));
	ladders[0].pop_back();

	//stage2. 두번째 사다리로 갈 경우.
	tmp.time = abs(tmp.row - ladderB.row) + abs(tmp.col - ladderB.col) + 1;
	ladders[1].push_back(tmp);
	ans = min(ans, solve(idx + 1));
	ladders[1].pop_back();

	return ans;
}

bool cmp(Person a, Person b)
{
	return a.time < b.time;
}