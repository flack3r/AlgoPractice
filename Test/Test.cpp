#include <iostream>

using namespace std;

int a[21][21];

int n;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

bool move(int direction)
{
	bool flag = false;

	if (direction == 0) { //¾Æ·¡
		for (int j = 0; j < n; j++) {
			int down = n - 1, up = n - 1;
			while (0 <= up && 0 <= down) {
				if (a[down][j] == 0) {
					while (0 <= up) {
						if (a[up][j] != 0) {
							a[down][j] = a[up][j];
							a[up][j] = 0;
							break;
						}
						up--;
					}
				}
				else {
					while (0 <= up) {
						up--;
						if (a[up][j] != 0) {
							if (a[down][j] == a[up][j]) {
								a[down][j] *= 2;
								a[up][j] = 0;
								flag = true;
							}
							down--;
							break;
						}
					}

				}
			}
		}

	}
	else if (direction == 1) { //À§
		for (int j = 0; j < n; j++) {
			int down = 0, up = 0;
			while (up<n && down<n) {
				if (a[down][j] == 0) {
					while (up<n) {
						if (a[up][j] != 0) {
							a[down][j] = a[up][j];
							a[up][j] = 0;
							break;
						}
						up++;
					}
				}
				else {
					while (up<n) {
						up++;
						if (a[up][j] != 0) {
							if (a[down][j] == a[up][j]) {
								a[down][j] *= 2;
								a[up][j] = 0;
								flag = true;
							}
							down++;
							break;
						}
					}

				}
			}
		}

	}
	else if (direction == 2) { //¿À
		for (int i = 0; i < n; i++) {
			int down = n - 1, up = n - 1;
			while (0 <= up && 0 <= down) {
				if (a[i][down] == 0) {
					while (0 <= up) {
						if (a[i][up] != 0) {
							a[i][down] = a[i][up];
							a[i][up] = 0;
							break;
						}
						up--;
					}
				}
				else {
					while (0 <= up) {
						up--;
						if (a[i][up] != 0) {
							if (a[i][down] == a[i][up]) {
								a[i][down] *= 2;
								a[i][up] = 0;
								flag = true;
							}
							down--;
							break;
						}
					}

				}
			}
		}

	}
	else if (direction == 3) { //¿Þ
		for (int i = 0; i < n; i++) {
			int down = 0, up = 0;
			while (up<n && down<n) {
				if (a[i][down] == 0) {
					while (up<n) {
						if (a[i][up] != 0) {
							a[i][down] = a[i][up];
							a[i][up] = 0;
							break;
						}
						up++;
					}
				}
				else {
					while (up<n) {
						up++;
						if (a[i][up] != 0) {
							if (a[i][down] == a[i][up]) {
								a[i][down] *= 2;
								a[i][up] = 0;
								flag = true;
							}
							down++;
							break;
						}
					}

				}
			}
		}

	}

	return flag;
}

int count() {
	int maxx = a[0][0];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			maxx = maxx > a[i][j] ? maxx : a[i][j];
		}
	}
	return maxx;
}


int dfs(int depth) {

	if (depth >= 5) return count();
	int ret = 0;
	int temp[21][21];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			temp[i][j] = a[i][j];
		}
	}

	for (int i = 0; i < 4; i++) {

		int flag = move(i);

		int t1 = dfs(depth + 1);
		ret = ret < t1 ? t1 : ret;


		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				a[i][j] = temp[i][j];
			}
		}

	}
	return ret;
}

int main()
{
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}

	cout << dfs(0) << '\n';

	return 0;
}