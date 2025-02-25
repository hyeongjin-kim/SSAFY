#include <iostream>
#include <queue>
#include <unordered_map>
#include <cstring>
#include <cmath>

using namespace std;

unordered_map<int, pair<int, int>> map; //ID�� ���θ� �����ϱ� ���� �� ID => ��ǥ ����

int arr[300][300] = {}; // �����迭 0 �̸� ���� ���� �ִٸ� �Ÿ��� �����
int N, M;
int price[300] = {};
int visit[300] = {};


struct Node {
	long long int cost; //���� ����̱� ������ Ŀ�� �� �־� ũ�� ����
	int pos;
	int low;

	Node(long long int cost, int low, int pos ) : cost(cost), pos(pos), low(low) {}

}; //Ž���� ����� ��� ����ü

struct cmp {
	bool operator()(Node a, Node b) {
		if (a.cost == b.cost) return a.low > b.low;
		else return a.cost > b.cost;
	}
}; //qriority queue�� ����� �� ����ü cost�� ���� �������� �����ϰ� cost�� ���ٸ� �ּ� ���� ��뿡 ���� ������������ ����

void init() {
	map.clear();
	memset(arr, 0, sizeof(arr));
	memset(price, 0, sizeof(price));
	
	int id, a, b, l;

	for (int i = 0; i < N; i++) {
		cin >> price[i];
	}

	for (int i = 0; i < M; i++) {
		cin >> id >> a >> b >> l;
		map[id] = { a, b };
		arr[a][b] = l;
	}
}

void Add(int ID, int start, int end, int length) {
	map[ID] = { start, end };
	arr[start][end] = length;
}

void Remove(int ID) {
	auto elem = map[ID];
	arr[elem.first][elem.second] = 0;
	map.erase(ID);
}

int Cost(int start, int end) {
	priority_queue<Node, vector<Node>, cmp> q;
	memset(visit, 0, sizeof(visit));
	q.push(Node(0, -price[start], start));
	while (!q.empty()) {
		auto cur = q.top();
		q.pop();
		long long int cost = -cur.cost;
		int low = -cur.low;
		int pos = cur.pos;


		if (visit[pos] > 0 and low >= visit[pos]) continue;

		if (pos == end) {
			return cost;
		}
		if (visit[pos] == 0) visit[pos] = low;
		else visit[pos] = min(low, visit[pos]);

		for (int i = 0; i < N; i++) {
			if (arr[pos][i] == 0) continue;
			if (visit[i] > 0 and low >= visit[i]) continue;
			int tmp = low;
			if (low > price[i]) low = price[i];
				q.push(Node( -(cost + arr[pos][i] * tmp), -low, i));
				
			}
	}
	return -1;
}

int main() {
	int T;
	cin >> T;
	int cmd, num, id, start, end, length, ans;
	for (int t = 1; t <= T; t++) {
		cin >> N >> M;
		init();
		cin >> num;
		for (int i = 0; i < num; i++) {
			cin >> cmd;
			switch (cmd)
			{
			case 100:
				cin >> id >> start >> end >> length;
				Add(id, start, end, length);
				break;
			case 200:
				cin >> id;
				Remove(id);
				break;
			case 300:
				cin >> start >> end;
				cout << "�� ��: " << Cost(start, end) << '\n';
				break;
			default:
				break;
			}
		}
	}
}