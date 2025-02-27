#include <iostream>
#include <cstring>
#include <vector>
using namespace std;


int N = 0, K = 0;

int visit[101][1001] = {}; // �迭 visit[i][volume] i: 1~i������ ������ ���濡 ���� volume: ������ ũ�� => ũ�Ⱑ volume�� ���濡 1 ~ i�� ������ ��� ������ ��

 struct things { //���ǵ��� ���ǿ� ��ġ ����
	int value;
	int volume;
	
};

things arr[101]; //���ǵ��� ����

void init() {
	memset(visit, 0, sizeof(visit));
	memset(arr, 0, sizeof(arr));

	cin >> N >> K;

	for (int i = 0; i < N; i++) { //�ʱ�ȭ �� �Է¹ޱ�
		int a, b;
		cin >> a >> b;
		arr[i+ 1].volume = a, arr[i + 1].value = b;
	}
}

int calc() {
	for (int i = 1; i <= N; i++) {
		for (int v = 1; v <= K; v++) {
			if (arr[i].volume <= v) {//���� i ��° ������ ��ġ k�� ������ ũ�⺸�� ũ�ٸ�, ������ �˴� visit[i - 1][volume - k]�� �� ������ ��� �Ͱ� �׳� ���� �ʰ� 1 ~ i -1������ ������ �ִ� ��ġ�� ��� ��� ���̿��� ����ϸ� �ȴ�.
				visit[i][v] = max(visit[i - 1][v], arr[i].value + visit[i - 1][v - arr[i].volume]);
			}
			else {
				visit[i][v] = visit[i - 1][v]; //i��° ������ ���� �� ���ٸ� �� ������ ����� �ʿ� ���� 1 ~ i -1������ ������ �ִ� ��ġ�� ��� ����� ���� ������ �ȴ�.
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