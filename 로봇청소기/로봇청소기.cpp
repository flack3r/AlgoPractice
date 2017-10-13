#include <iostream>
#include <vector>
#include <algorithm>

#define North 0
#define East 1
#define South 2
#define West 3

using namespace std;
int N, M;
vector< vector<int> > arr;
class Turtle
{
private:
	vector< vector<bool> > visit;
	int cleanCount{ 0 };
	int CheckLeft{ 0 };
	int direction;
public:
	Turtle(int _direction) : direction(_direction)
	{
		visit = vector< vector<bool> >(N, vector<bool>(M, false));
	};
	void move(int r, int c);
	int GetAns(){ return this->cleanCount; };
};

int main()
{
	scanf("%d %d", &N, &M);
	int row, col, direction;
	scanf("%d %d %d", &row, &col, &direction);

	arr = vector< vector<int> >(N, vector<int>(M));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			scanf("%d", &arr[i][j]);
		}
	}

	Turtle t(direction);
	t.move(row, col);
	int ans = t.GetAns();
	printf("%d\n", ans);
}

void Turtle::move(int r, int c)
{
	if (arr[r][c] == 0 && !this->visit[r][c])
	{
		this->cleanCount += 1;
		this->visit[r][c] = true;
	}
	//printf("(%d,%d) direction: %d \n", r, c, direction);
	
	int next_direction = -1;
	int next_r = -1, next_c = -1;
	int back_r = -1, back_c = -1;
	switch (direction)
	{
	case North:
		next_direction = West;
		next_r = r; next_c = c - 1;
		back_r = r + 1; back_c = c;
		break;
	case East:
		next_direction = North;
		next_r = r - 1, next_c = c;
		back_r = r, back_c = c - 1;
		break;
	case West:
		next_direction = South;
		next_r = r + 1, next_c = c;
		back_r = r, back_c = c + 1;
		break;
	case South:
		next_direction = East;
		next_r = r, next_c = c + 1;
		back_r = r - 1, back_c = c;
		break;
	}

	if (next_r < 0 || next_r >= N || next_c < 0 || next_c >= M)
	{
		direction = next_direction;
		this->CheckLeft += 1;
		move(r, c);
	}


	if (this->CheckLeft == 4)
	{
		//case 2-4
		//뒤가 벽인경우
		if (back_r < 0 || back_r >= N || back_c < 0 || back_c >=M)
			return;

		if (arr[back_r][back_c] == 1)
		{
			return;
		}
		//case 2-3
		else
		{
			r = back_r;
			c = back_c;
			this->CheckLeft = 0;
			move(r, c);
		}
	}
	else
	{
		//case 2-1
		if (arr[next_r][next_c] == 0 && !visit[next_r][next_c])
		{
			direction = next_direction;
			r = next_r;
			c = next_c;
			this->CheckLeft = 0;
			move(r, c);
		}
		//case 2-2
		else
		{
			direction = next_direction;
			this->CheckLeft += 1;
			move(r, c);
		}
	}
}