#include <iostream>
#include <algorithm>
#include <vector>

#define East 1
#define West 2
#define North 3
#define South 4

using namespace std;
class Dice
{
private:
	int row, col;
	int arr[7];
public:
	Dice(int _row, int _col) : row(_row), col(_col) {
		for (int i = 0; i <= 6; i++)
			arr[i] = 0;
	};
	//만약 지도 out이면 -1 그렇지 않으면 top
	int Move(int direction);
};

int N, M;
vector< vector<int> > MapArr;
int main()
{
	int K;
	int r, c;
	scanf("%d %d %d %d %d", &N, &M, &r, &c, &K);
	Dice d(r, c);

	MapArr = vector< vector<int> >(N, vector<int>(M));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			scanf("%d", &MapArr[i][j]);
		}
	}

	for (int i = 1; i <= K; i++)
	{
		int cmd;
		scanf("%d", &cmd);
		int ans = d.Move(cmd);
		if (ans != -1)
		{
			printf("%d\n", ans);
		}
	}
	return 0;
}

int Dice::Move(int direction)
{
	int dRow[5] = { 0,0,0,-1,1 };
	int dCol[5] = { 0,1,-1,0,0 };

	int next_row = this->row + dRow[direction];
	int next_col = this->col + dCol[direction];

	if (next_row < 0 || next_row >= N || next_col < 0 || next_col >= M)
		return -1;

	int n1 = arr[1];
	int n2 = arr[2];
	int n3 = arr[3];
	int n4 = arr[4];
	int n5 = arr[5];
	int n6 = arr[6];

	switch (direction)
	{
	case North:
		arr[1] = n2;
		arr[2] = n6;
		arr[5] = n1;
		arr[6] = n5;
		break;
	case East:
		arr[1] = n3;
		arr[3] = n6;
		arr[4] = n1;
		arr[6] = n4;
		break;
	case West:
		arr[1] = n4;
		arr[3] = n1;
		arr[4] = n6;
		arr[6] = n3;
		break;
	case South:
		arr[1] = n5;
		arr[2] = n1;
		arr[5] = n6;
		arr[6] = n2;
		break;
	}

	if (MapArr[next_row][next_col] == 0)
		MapArr[next_row][next_col] = arr[1];
	else
	{
		arr[1] = MapArr[next_row][next_col];
		MapArr[next_row][next_col] = 0;
	}
	this->row = next_row;
	this->col = next_col;
		
	return this->arr[6];
}