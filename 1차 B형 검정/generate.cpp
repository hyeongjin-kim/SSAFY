#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <random>
#include <stdio.h>
#include <set>
#include <time.h>
#include <unordered_map>

using namespace std;

int N = 300, M = 2000, T = 50, C = 500;

unordered_map<int, pair<int, int>> map;
int arr[300][300] = {};
int main() {
	
	freopen("input.txt", "w", stdout);
	srand(time(NULL));
	cout << T << '\n';
	
	for (int t = 0; t < T; t++) {
		map.clear();
		memset(arr, 0, sizeof(arr));
		cout << N << ' ' << M << '\n';
		for (int n = 0; n < N; n++) {
			cout << rand() % 2000 + 1 << '\n';
		}
		for (int m = 0; m < M; m++) {
			while (1) {
				int mid = rand() %1000000000;
				if (map[mid].first == 0 and map[mid].second == 0) {
					int s, e;
					while (1) {
						s = rand() % N;
						e = rand() % N;
						if (s != e and arr[s][e] == 0) {
							map[mid] = { s , e };
							arr[s][e] = rand() % 2000;
							cout << mid << ' ' << s << ' ' << e << ' ' << arr[s][e] << '\n';
							break;
						}
					}
					break;
				}

			}
		}
		int cmdnum = 2000;
		cout << cmdnum << '\n';
		int cnt = 0;
		for (int c = 0; c < cmdnum; c++) {
			int cmd = rand() % 3;
			if (cmd == 2) {
				if (cnt < C) {
					cnt++;
					int s, e;
					s = rand() % N;
					e = rand() % N;
					cout << 300 << ' ' << s << ' ' << e << '\n';
				}
				else {
					c--;
					continue;
				}
			}
			else if(cmd == 0) {
				int mid = rand() % 1000000000;
				if (map[mid].first != 0 and map[mid].second != 0) {
					int s, e;
					while (1) {
						s = rand() % N;
						e = rand() % N;
						if (s != e and arr[s][e] == 0) {
							map[mid] = { s , e };
							arr[s][e] = rand() % 2000;
							cout << 100 << ' ' << mid << ' ' << s << ' ' << e << ' ' << arr[s][e] << '\n';
							break;
						}
					}
				}
				else {
					c--;
					continue;
				}
			}
			else {
				int mid = rand() % 1000000000;
				if (map[mid].first == 0 and map[mid].second == 0) {
					arr[map[mid].first][map[mid].second] = 0;
					map.erase(mid);
					cout << 200 << ' ' << mid << '\n';
				}
				else {
					c--;
					continue;
				}
			}
		}
	}

	return 0;
}


