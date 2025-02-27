#include <iostream>
#include <cstring>
#include <vector>
using namespace std;


int N = 0, K = 0;

int visit[101][1001] = {}; // 배열 visit[i][volume] i: 1~i까지의 물건을 가방에 담음 volume: 가방의 크기 => 크기가 volume인 가방에 1 ~ i의 물건을 담는 문제의 답

 struct things { //물건들의 부피와 가치 저장
	int value;
	int volume;
	
};

things arr[101]; //물건들의 정보

void init() {
	memset(visit, 0, sizeof(visit));
	memset(arr, 0, sizeof(arr));

	cin >> N >> K;

	for (int i = 0; i < N; i++) { //초기화 및 입력받기
		int a, b;
		cin >> a >> b;
		arr[i+ 1].volume = a, arr[i + 1].value = b;
	}
}

int calc() {
	for (int i = 1; i <= N; i++) {
		for (int v = 1; v <= K; v++) {
			if (arr[i].volume <= v) {//만약 i 번째 물건의 가치 k가 가방의 크기보다 크다면, 기존에 알던 visit[i - 1][volume - k]에 이 물건을 담는 것과 그냥 담지 않고 1 ~ i -1까지의 물건을 최대 가치로 담는 방법 사이에서 고민하면 된다.
				visit[i][v] = max(visit[i - 1][v], arr[i].value + visit[i - 1][v - arr[i].volume]);
			}
			else {
				visit[i][v] = visit[i - 1][v]; //i번째 물건을 담을 수 없다면 이 물건은 고려할 필요 없어 1 ~ i -1까지의 물건을 최대 가치로 담는 방법과 같이 담으면 된다.
			}
		}
	}
	return visit[N][K];
}

int main() {
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		init();
		cout << '#' << t << ' ' << calc() << '\n';
	}
	return 0;
}
