#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <unordered_map>
#include <cstring>
#include <cmath>
#include <cstdio>

using namespace std;

unordered_map<int, pair<int, int>> map; //ID로 도로를 관리하기 위한 맵 ID => 좌표 맵핑

int arr[300][300] = {}; // 인접배열 0 이면 없는 도로 있다면 거리가 저장됨
int N, M;
int price[300] = {};
int visit[300] = {};
int lowcost[300] = {};

struct Node {
	long long int cost; //누적 비용이기 때문에 커질 수 있어 크게 설정
	int pos;
	int low;

	Node(long long int cost, int low, int pos ) : cost(cost), pos(pos), low(low) {}

}; //탐색에 사용할 노드 구조체

struct cmp {
	bool operator()(Node a, Node b) {
		if (a.cost == b.cost) return a.low > b.low;
		else return a.cost > b.cost;
	}
}; //qriority queue에 사용할 비교 구조체 cost에 따라 내림차순 정렬하고 cost가 같다면 최소 충전 비용에 따라 내림차순으로 정렬

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
	memset(lowcost, 0, sizeof(lowcost));
	lowcost[start] = price[start];
	q.push(Node(0, -price[start], start));
	while (!q.empty()) {
		auto cur = q.top();
		q.pop();
		long long int cost = -cur.cost;
		int low = -cur.low;
		int pos = cur.pos;

		if (pos == end) {
			return cost;
		}
		if (visit[pos] > 0 and visit[pos] >= cost and lowcost[pos] >= low) continue;
		if (visit[pos] == 0 or lowcost[pos] > low) {
			visit[pos] = cost;
			lowcost[pos] = low;
			if (low > price[pos]) low = price[pos];
			for (int i = 0; i < N; i++) {
				if (arr[pos][i] == 0) continue;
				if (visit[i] == 0 or lowcost[i] > low) {
					q.push(Node(-(cost + arr[pos][i] * low), -low, i));
				}				
			}
		}
		
	}
	return -1;
}

int main() {
	
	freopen("input.txt", "r", stdin);
	clock_t s, f;
	s = clock();
	int T;
	cin >> T;
	int cmd, num, id, start, end, length, ans;
	for (int t = 1; t <= T; t++) {
		//cout << '#' << t << '\n';
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
				//cout << "내 답: " << Cost(start, end) << '\n';
				break;
			default:
				break;
			}
		}
	}
	f = clock();
	cout << (double)(f - s) / CLOCKS_PER_SEC;
	return 0;
}