#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <cmath>

using namespace std;
int n, m, ans, rx, ry, bx, by;
bool visit[11][11][11][11];
char arr[22][22];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };

int bfs() {
	queue<pair<pair<int, int>, pair<int, int>>> q;
	q.push({ { ry,rx },{ by,bx } });
	visit[ry][rx][by][bx] = true;

	int cnt = 0;

	while (!q.empty()) {
		int qSize = q.size();
		while (qSize--) {
			int rry = q.front().first.first;
			int rrx = q.front().first.second;
			int bby = q.front().second.first;
			int bbx = q.front().second.second;
			q.pop();

			if (arr[rry][rrx] == 'O' && (arr[rry][rrx] != arr[bby][bbx])) {  //도착했을떄
				return cnt;
			}
			for (int i = 0; i<4; i++) {
				int t1, t2, t3, t4;
				t1 = rry;
				t2 = rrx;
				t3 = bby;
				t4 = bbx;

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
						continue;
					if (abs(t1 - rry) + abs(t2 - rrx) < abs(t3 - bby) + abs(t4 - bbx)) {
						t3 -= dy[i];                        //이동을 덜한 부분처리
						t4 -= dx[i];
					}
					else {
						t1 -= dy[i];
						t2 -= dx[i];
					}
				}

				if (visit[t1][t2][t3][t4]) {
					continue;
				}
				q.push({ { t1,t2 } ,{ t3,t4 } });
				visit[t1][t2][t3][t4] = true;

			}
		}
		if (cnt >= 10) {
			return -1;
		}
		cnt++;
	}
	return -1;
}

int main() {
	scanf("%d%d", &n, &m);
	memset(visit, false, sizeof(visit));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf(" %c", &arr[i][j]);
			if (arr[i][j] == 'B') {
				by = i;
				bx = j;
			}
			else if (arr[i][j] == 'R') {
				ry = i;
				rx = j;
			}
		}
	}

	printf("%d\n", bfs());

	return 0;
}