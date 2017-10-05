#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
using namespace std;

typedef struct _Animal
{
	int row;
	int col;
	int direction;
	int num;
	int collision_num;
}Animal;

int dRow[4] = { -1,1,0,0 };
int dCol[4] = { 0,0,-1,1 };
map<int, Animal> animals;
// 군집 번호, 움직임 여부
vector< vector< pair<int, int> > > arr;
int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		int N, M, K;
		scanf("%d %d %d", &N, &M, &K);
		animals.clear();
		arr = vector< vector< pair<int, int> > >(N, vector< pair<int, int> >(N));
		for (int k = 1; k <= K; k++)
		{
			int row, col, num, direction;
			scanf("%d %d %d %d", &row, &col, &num, &direction);
			Animal tmp = { row,col,direction,num, num };
			animals[k] = tmp;
			arr[row][col] = make_pair(k, 0);
		}

		//time go by
		for (int m = 1; m <= M; m++)
		{
			//printf("time----------\n");
			vector<int> erase_list;
			erase_list.clear();
			for (map<int, Animal>::iterator it = animals.begin(); it != animals.end(); it++)
			{
				int tmp_num = (*it).first;
				Animal& tmp = (*it).second;
				//move animal
				int next_row = tmp.row + dRow[tmp.direction - 1];
				int next_col = tmp.col + dCol[tmp.direction - 1];
				//printf("score: %d original: %d,%d, next: %d,%d \n", tmp.num, tmp.row, tmp.col, next_row, next_col);
				//만약 약품 방향이라면
				if (next_row == 0 || next_row == N - 1 || next_col == 0 || next_col == N - 1)
				{
					//방향 반대
					if (tmp.direction == UP)
						tmp.direction = DOWN;
					else if (tmp.direction == DOWN)
						tmp.direction = UP;
					else if (tmp.direction == LEFT)
						tmp.direction = RIGHT;
					else if (tmp.direction == RIGHT)
						tmp.direction = LEFT;
					//수 감소

					int minus = tmp.num / 2;
					if (tmp.num % 2 != 0)
						minus += 1;
					tmp.num -= minus;
					tmp.collision_num -= minus;

					if (tmp.num == 0)
						erase_list.push_back(tmp_num);
					else
					{
						tmp.row = next_row;
						tmp.col = next_col;
						arr[next_row][next_col].first = tmp_num;
						arr[next_row][next_col].second = 1;
					}
				}
				else
				{
					int current = arr[next_row][next_col].first;
					int move_state = arr[next_row][next_col].second;
					//만약 충돌한다면
					if (current != 0 && move_state == 1)
					{
						Animal& origin = animals[current];
						if (origin.collision_num > tmp.num)
						{
							origin.row = next_row;
							origin.col = next_col;
							origin.collision_num = origin.num;
							origin.num += tmp.num;

							arr[next_row][next_col].first = current;
							arr[next_row][next_col].second = 1;
							erase_list.push_back(tmp_num);
						}
						else
						{
							tmp.row = next_row;
							tmp.col = next_col;
							tmp.collision_num = tmp.num;
							tmp.num += origin.num;

							arr[next_row][next_col].first = tmp_num;
							arr[next_row][next_col].second = 1;
							erase_list.push_back(current);
						}
					}
					//빈곳 이라면
					else
					{
						tmp.row = next_row;
						tmp.col = next_col;
						arr[next_row][next_col].first = tmp_num;
						arr[next_row][next_col].second = 1;
					}
				}
			}

			for (map<int, Animal>::iterator it = animals.begin(); it != animals.end(); it++)
			{
				(*it).second.collision_num = (*it).second.num;
			}

			//지워지는거 지우기
			for (int q = 0; q < erase_list.size(); q++)
			{
				animals.erase(erase_list[q]);
			}

			//움직임 초기화
			for (int x = 0; x < N; x++)
			{
				for (int y = 0; y < N; y++)
				{
					arr[x][y].second = 0;
				}
			}
		}
		int ans = 0;
		//printf("[*last]\n");
		for (map<int, Animal>::iterator it = animals.begin(); it != animals.end(); it++)
		{
			//printf("score: %d , location: %d , %d\n", (*it).second.num, (*it).second.row, (*it).second.col);
			ans += (*it).second.num;
		}
		printf("#%d %d\n", t, ans);
	}
	return 0;
}