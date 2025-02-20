#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include <queue>
using namespace std;

int ans, N, M;

vector<int> vleaf[501]; //leaf - > root Ž���� �� ����� ���Ḯ��Ʈ
vector<int> vroot[501]; //root - > leaf Ž���� �� ����� ���Ḯ��Ʈ

set<int> root, leaf; //Ž���� ������ �� �ʿ��� root��� leaf���� ���� set

int visit[501]; //root -> leaf Ž���� �� ������ ������ ���� ������ �迭
int visit2[501]; //leaf -> root Ž���� �� ������ ������ ���� ������ �迭


//�� �л��� �ǹ��ϴ� ����ü �ִ� 500���� bit�� �ʿ�� �ϴµ� 64 * 8 = 512�̹Ƿ� 8���� 64��Ʈ  int�� ����
struct student { 
	uint64_t arr[8]; //i��° �л��� arr[i/64]�� i %64��° ��Ʈ�� ����
};

student compare; //������ �� �� �ִ��� Ȯ���ϱ� ���� �񱳴��

uint64_t one = 1; //shift���궧 ����� 1

student rootcheck[501]; //root -> leaf Ž���� �� �� �ڱ⺸�� ���� �л����� �����  bit��
student leafcheck[501]; //leaf -> root Ž���� �� �� �ڱ⺸�� ū �л����� �����  bit��

void init() { //�� �׽�Ʈ ���̽����� �ʱ�ȭ�� �Է��� �޾ƿ��� ���� �Լ�
	ans = 0;
	cin >> N >> M;
	int a, b;
	//�ʱ�ȭ
	root.clear();
	leaf.clear();

	memset(rootcheck, 0, sizeof(rootcheck));
	memset(leafcheck, 0, sizeof(leafcheck));
	memset(&compare, 0, sizeof(student));

	memset(visit, 0, sizeof(visit));
	memset(visit2, 0, sizeof(visit2));
	for (int i = 0; i <= N; i++) {
		vleaf[i].clear();
		vroot[i].clear();
		compare.arr[i / 64] |= one << (i % 64);//�� ����� ����� �۾�. N���� ��� bit�� 1�� ����
	}
	//leaf�� root�� ã�� ���� ��� ��带 ����
	for (int i = 0; i < N; i++) {
		leaf.insert(i + 1);
		root.insert(i + 1);
	}
	//�� ����� 0��° bit�� 0�̾�� �� �׷��� ������ ���� shift�� �ѹ��� ��
	compare.arr[0] = compare.arr[0] >> 1;
	compare.arr[0] = compare.arr[0] << 1;

	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		vleaf[b].push_back(a); //leaf -> root�� ���� ���� ����Ʈ
		vroot[a].push_back(b); //root -> leaf�� ���� ���Ḯ��Ʈ
		leaf.erase(a); //�ڱ⺸�� ū ��尡 ������ leaf�� �ƴ�
		root.erase(b); //�ڱ⺸�� ���� ��尡 ������ root�� �ƴ�
	}

}

void search() {
	queue<int> q;
	//root���� ��� ��� �߰� root���� �ڱ⺸�� ���� ��尡 ���� ������ Ž���� ���� �ʿ��� ������ ����
	for (int node : root) {
		q.push(node);
		visit[node] = 1;
	}
	while (!q.empty()) {
		int cur = q.front();

		q.pop();
		
		//cur ���� ����� ��� ��� Ȯ��
		for (int node : vroot[cur]) {
			visit[node] += 1; //Ȯ���� Ƚ�� ����
			if (visit[node] == vleaf[node].size()) { // vleaf[node].size() = node�� ����� ����� �� 
				q.push(node); //�ڱ�� ����� ��忡�� ��� �� ��带 Ȯ�������� q�� push
			}

			rootcheck[node].arr[cur / 64] |= one << (cur % 64); //cur�� node���� ������ ǥ��

			//cur�� node���� �����Ƿ� cur���� ���� ���� node���� ����
			for (int i = 0; i < 8; i++) {
				rootcheck[node].arr[i] |= rootcheck[cur].arr[i]; //cur�� �ִ� ������ node�� ǥ��
			}
		}

	}

}

void search2() {
	queue<int> qq;
	//leaf���� ��� ��� �߰� leaf���� �ڱ⺸�� ū ��尡 ���� ������ Ž���� ���� �ʿ��� ������ ����
	for (int node : leaf) {
		qq.push(node);
		visit2[node] = 1;
	}
	while (!qq.empty()) {
		int cur = qq.front();
		qq.pop();

		//cur ���� ����� ��� ��� Ȯ��
		for (int node : vleaf[cur]) {
			visit2[node] += 1; //Ȯ���� Ƚ�� ����
			if (visit2[node] == vroot[node].size()) { // vroot[node].size() = node���� ū ����� �� 
				qq.push(node); //�ڱ�� ����� ��忡�� ��� �� ��带 Ȯ�������� qq�� push

			}

			leafcheck[node].arr[cur / 64] |= one << (cur % 64); //cur�� node���� ŭ�� ǥ��

			//cur�� node���� ũ�Ƿ� cur���� ū ���� node���� ŭ
			for (int i = 0; i < 8; i++) {
				leafcheck[node].arr[i] |= leafcheck[cur].arr[i]; //cur�� �ִ� ������ node�� ǥ��
			}
		}

	}
}

int main() {

	init();
	search();
	search2();

	//������ �� �� �ִ��� Ȯ���ϱ�
	for (int i = 1; i <= N; i++) {
		rootcheck[i].arr[i / 64] |= one << (i % 64); //�ڱ� �ڽſ� �ش��ϴ� bit ä���
		int flag = 1; //������ �� �� �ִ��� Ȯ���ϴ� flag

		for (int j = 0; j < 8; j++) {
			if (((rootcheck[i].arr[j] | leafcheck[i].arr[j])) == compare.arr[j]) continue; //rootcheck�� leafcheck�� or���� �� �� ���� ������ ���� ��ȿ
			//�񱳴��� �ٸ��� ������ �� �� ���� ��
			flag = 0;
			break;
		}
		if (flag) ans++;
	}
	cout << ans << '\n';

	return 0;
}