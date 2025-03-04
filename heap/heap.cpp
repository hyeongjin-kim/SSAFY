#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

vector<int> ans;
int N, cmd, num, cnt;

int arr[100001] = {};

void init() {
	ans.clear(); //출력할 내용 초기화
	cin >> N;
	memset(arr, 0, sizeof(arr)); //힙 초기화
	cnt = 1; //다음에 추가될 요소가 들어갈 위치이자 현재 보유한 요소 수 + 1
}

void push(int num) {
	arr[cnt] = num; //맨 끝에 삽입
	int idx = cnt;
	cnt++;
	while (idx > 0) {
		int p = idx / 2; //부모의 인덱스
		if (p > 0 and arr[idx] > arr[p]) { //부모 인덱스가 유효하고, idx의 요소가 더 크다면 바꾸기
			swap(arr[idx], arr[p]);
			idx = p;
		}
		else { //부모보다는 작을 때는 자식과 비교
			int l = idx * 2;
			int r = idx * 2 + 1;

			if (cnt > r) { //자식이 둘 다 있는 경우
				int tar;
				if (arr[l] > arr[r]) tar = l; //자식들 중 큰 쪽
				else tar = r;
				if (arr[tar] > arr[idx]) { //자식중 큰 쪽보다 작다면 바꾸기
					swap(arr[tar], arr[idx]);
					idx = tar;
				}
				else break; //변화가 없으면 종료
			}
			else if (cnt > l) { //자식이 왼쪽 만 있는 경우
				if (arr[idx] < arr[l]) {  //자식보다 작으면 바꾸기
					swap(arr[idx], arr[l]);
					idx = l;
				}
				else break; //변화가 없으면 종료
			}
			else break; //자식이 없는 경우는 그냥 종료
		}
	}

	return;
}

void pop() {
	if (cnt > 1) {
		ans.push_back(arr[1]); //heap의 top인 1번을 출력할 내용에 저장
		cnt--;
		arr[1] = arr[cnt]; //맨 끝의 요소를 가져옴
		int idx = 1;
		while (idx < cnt) { //자식들과만 비교하면 됨. 위에서부터 내려오므로 부모는 무조건 나보다 큼
			int l = idx * 2; 
			int r = idx * 2 + 1;

			if (cnt > r) { //자식이 둘 다 있는 경우
				int tar;
				if (arr[l] > arr[r]) tar = l;  //자식들 중 큰 쪽
				else tar = r;
				if (arr[tar] > arr[idx]) {  //자식중 큰 쪽보다 작다면 바꾸기
					swap(arr[tar], arr[idx]);
					idx = tar;
				}
				else break; //변화가 없으면 종료
			}
			else if (cnt > l) { //자식이 왼쪽 만 있는 경우
				if (arr[idx] < arr[l]) {  //자식보다 작으면 바꾸기
					swap(arr[idx], arr[l]); 
					idx = l;
				}
				else break; //변화가 없으면 종료
			}
			else break; //자식이 없는 경우는 그냥 종료
		}
	}
	else ans.push_back(-1); //힙이 빈 경우 -1을 저장

	return;
}

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		init();
		for (int i = 0; i < N; i++) {
			cin >> cmd;
			if (cmd == 1) {
				cin >> num;
				push(num);
			}
			else if (cmd == 2) {
				pop();
			}
			else cout << "error";
		}
		cout << '#' << t << ' ';
		for (auto a : ans) {
			cout << a << ' ';
		}
		cout << '\n';
	}
	return 0;
}
