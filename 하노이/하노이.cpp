#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

struct action {
	int target;
	int from;
	int to;
	action(int tar, int from, int to): target(tar), from(from), to(to) {}
};

stack<action> s;

int M;
int arr[3][1001] = {};
int cnt[3] = {};
int destination[4] = { 0, 2, 1, 0};
int K, top[3];

void init() {
	while (!s.empty()) s.pop();
	memset(arr, 0, sizeof(arr));
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < 3; i++) {
		cin >> cnt[i];
		arr[i][0] = INT_MAX;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = cnt[i]; j > 0; j--) {
			cin >> arr[i][j];
		}
	}
	
	int cur = 1;
	int pos = arr[0][0] > arr[1][0] ? 0 : 1;
	int dest = 2;
	s.push(action(cur, pos, dest));

}

void go() {
	int k, move = 0;
	cin >> k;
	int ans[3];
	cin >> ans[0] >> ans[1] >> ans[2];

	while (move < k) {
		int cur = s.top().target, depart = s.top().from, dest = s.top().to;
		if ((cur == cnt[depart]) and (cnt[dest] == 0 or arr[depart][cur] < arr[dest][cnt[dest]])) {
			s.pop();
			cnt[dest]++;
			arr[dest][cnt[dest]] = arr[depart][cur];
			arr[depart][cur] = 0;
			cnt[depart]--;
			move++;
		}
		else {
			
			if (cnt[dest] != 0) {
				int i;

				for (i = cnt[dest]; i >= 0; i--) {
					if (arr[depart][cur] < arr[dest][i]) {
						break;
					}
				}
				s.push(action(i + 1, dest, destination[dest + depart]));
				int a = 0;
			}
			else {
				int num = cnt[depart];
				for (int i = cur + 1; i <= num; i++)
				{
					s.push(action(i, depart, destination[depart + dest]));
					dest = destination[depart + dest];
					int a = 0;
				}
				
			}
			
		}

	}
	int flag = 1;

	for (int i = 0; i < 3; i++) {
		if (arr[i][cnt[i]] != ans[i])flag = 0;
	}
	cout << flag * 100 << '\n';
}

int main() {

	int T = 1;
	//cin >> T;

	for (int t = 1; t <= T; t++) {
		cin >> M;

		for (int m = 0; m < M; m++) {
			int cmd;
			cin >> cmd;
			switch (cmd) {
			case 100:
				init();
				break;
			case 300:
				go();
				break;
			}
		}

		
	}
	return 0;
}
