#include <vector>
#include <iostream>
#include <algorithm>

#define Red 'R'
#define Blue 'B'
#define WALL '#'
#define Holl 'O'
#define EMPTY '.'
#define INT_MAX 10000

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

typedef struct _Info
{
	int redRow;
	int redCol;
	int BlueRow;
	int BlueCol;
}Info;
using namespace std;
int N, M;
bool visit[12][12][12][12] = { false, };
vector<vector<char>> arr;
Info info;

int moveBoard(Info& moveinfo, int mode);
int solve(int count);
int main()
{
	for (int q = 0; q <= 11; q++)
	{
		for (int w = 0; w <= 11; w++)
		{
			for (int e = 0; e <= 11; e++)
			{
				for (int r = 0; r <= 11; r++)
					visit[q][w][e][r] = false;
			}
		}
	}
	scanf("%d %d", &N, &M);
	arr = vector<vector<char>>(N + 1, vector<char>(M + 1));
	for (int i = 1; i <= N; i++)
	{
		
		for (int j = 1; j <= M; j++)
		{
			char tmp;
			scanf(" %c", &tmp);
			if (tmp == Blue)
			{
				info.BlueCol = j;
				info.BlueRow = i;
			}
			else if (tmp == Red)
			{
				info.redCol = j;
				info.redRow = i;
			}
			arr[i][j] = tmp;
		}
	}

	
	/*
	printf("\n");
	moveBoard(info, RIGHT);
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			printf("%c", arr[i][j]);
		}
		printf("\n");
	}
	*/
	
	visit[info.redRow][info.redCol][info.BlueRow][info.BlueCol] = true;
	int ans = solve(1);
	if (ans > 10)
		printf("-1\n");
	else
		printf("%d\n", ans);
	
	return 0;
}

int solve(int count)
{
	if (count > 10)
		return INT_MAX;

	int ans = INT_MAX;
	int result;
	vector<vector<char>> backArr = arr;
	Info backup = info;
	for (int i = 0; i < 4; i++)
	{
		result = moveBoard(info, i);
		if (result == -1 || result == 2)
		{
			info = backup;
			arr = backArr;
			continue;
		}
		else if (result == 1)
			return count;
		else if (result == 0 && !visit[info.redRow][info.redCol][info.BlueRow][info.BlueCol])
		{
			Info backup2 = info;
			vector<vector<char>> backArr2 = arr;
			//backArr = arr;
			visit[info.redRow][info.redCol][info.BlueRow][info.BlueCol] = true;
			ans = min(ans, solve(count + 1));
			info = backup2;
			arr = backArr2;
			visit[info.redRow][info.redCol][info.BlueRow][info.BlueCol] = false;
		}
		info = backup;
		arr = backArr;
	}
	return ans;
}


// return -1: 파란색이 구멍에 빠짐, 1: 빨간색만 빠짐. 0: 그냥.. 2:변화 없음
int moveBoard(Info& moveinfo, int mode)
{
	int i = -1;
	int dx[4] = { 0,0,1,-1 };
	int dy[4] = { 1,-1,0,0 };
	switch (mode)
	{
	case UP:
		i = 1;
		break;
	case DOWN:
		i = 0;
		break;
	case LEFT:
		i = 3;
		break;
	case RIGHT:
		i = 2;
		break;
	}
	int x = moveinfo.redRow, y = moveinfo.redCol, z = moveinfo.BlueRow, w = moveinfo.BlueCol;
	int& t1 = moveinfo.redRow;
	int& t2 = moveinfo.redCol;
	int& t3 = moveinfo.BlueRow;
	int& t4 = moveinfo.BlueCol;

	while (arr[t1 + dy[i]][t2 + dx[i]] != '#' && arr[t1][t2] != 'O') {    //빨간색 이동
		t1 += dy[i];
		t2 += dx[i];
	}
	while (arr[t3 + dy[i]][t4 + dx[i]] != '#' && arr[t3][t4] != 'O') {    //파란색 이동
		t3 += dy[i];
		t4 += dx[i];
	}

	if ((t1 == t3) && (t2 == t4)) {               // 만약 같은 라인에 있었다면
		if (arr[t1][t2] == 'O')
			return -1;
		if (abs(t1 - x) + abs(t2 - y) < abs(t3 - z) + abs(t4 - w)) {
			t3 -= dy[i];                        //이동을 덜한 부분처리
			t4 -= dx[i];
		}
		else {
			t1 -= dy[i];
			t2 -= dx[i];
		}
	}

	if (arr[t1][t2] == Holl)
		return 1;
	else
		return 0;
}