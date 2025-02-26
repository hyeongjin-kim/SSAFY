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
int visit[300] = {}; //방문여부 저장하는 배열 방문하면 그 도시까지 가는 최소 비용이 저장된다.
int lowcost[300] = {}; //그 도시까지 갈 동안 만났던 최소 충전 비용을 저장한다.

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

void init() { //필요한 자료구조들 초기화, 기본 정보 입력
	map.clear();
	memset(arr, 0, sizeof(arr));
	memset(price, 0, sizeof(price));
	
	int id, a, b, l;

	for (int i = 0; i < N; i++) { //각 도시의 충전 비용 저장
		cin >> price[i];
	}

	for (int i = 0; i < M; i++) { //도로의 정보 저장
		cin >> id >> a >> b >> l;
		map[id] = { a, b };
		arr[a][b] = l;
	}
}

void Add(int ID, int start, int end, int length) { //이미 존재하는 도로는 들어오지 않으므로 유무 검사는 필요 없다. 따라서 그냥 map과 arr에 좌표와 거리를 각각 저장
	map[ID] = { start, end };
	arr[start][end] = length;
}

void Remove(int ID) { //존재하지 않는 도로는 들어오지 않으므로 유무검사는 필요없다. 그냥 arr에서 거리 정보를 지우고 map에서 지운다.
	auto elem = map[ID];
	arr[elem.first][elem.second] = 0;
	map.erase(ID);
}

int Cost(int start, int end) {
	priority_queue<Node, vector<Node>, cmp> q; //탐색에 사용할 pq
	//방문 배열과 최소 충전비용 배열 초기화
	memset(visit, 0, sizeof(visit));
	memset(lowcost, 0, sizeof(lowcost));
	//시작도시 설정
	lowcost[start] = price[start]; 
	q.push(Node(0, -price[start], start));
	
	while (!q.empty()) {
		auto cur = q.top(); //q에 있는 노드중 가장 비용이 저렴한 경우
		q.pop();
		long long int cost = -cur.cost;
		int low = -cur.low;
		int pos = cur.pos;

		if (pos == end) { //도착했다면 이거보다 더 싸게 갈 방법은 없음 따라서 리턴
			return cost;
		}
		if (visit[pos] > 0 and visit[pos] >= cost and lowcost[pos] >= low) continue; //만약 이미 방문한 도시인데 누적 비용도, 지금까지의 최소 충전비용도 기존보다 크면 볼 필요 없음
		if (visit[pos] == 0 or lowcost[pos] > low) { 
			visit[pos] = cost; //최소 누적비용 갱신 
			lowcost[pos] = low; //최소 탐색 비용 갱신
			if (low > price[pos]) low = price[pos]; //현재 도시에서 충전할지, 이전에 방문했던 최소 비용도시에서 충전할지 결정
			for (int i = 0; i < N; i++) {
				if (arr[pos][i] == 0) continue; //못가는 도시는 넘어감
				if (visit[i] == 0 or lowcost[i] > low) { //방문한적이 없거나, 최소 충전비용보다 싼 루트면 q에 저장
					q.push(Node(-(cost + arr[pos][i] * low), -low, i));
				}				
			}
		}
		
	}
	return -1;
}

int main() {
	
	freopen("input.txt", "r", stdin); //테스트 케이스를 파일에서 불러옴
	clock_t s, f; //실행 시간을 측정하기 위함
	s = clock();
	int T;
	cin >> T;
	int cmd, num, id, start, end, length, ans;
	for (int t = 1; t <= T; t++) {
		//cout << '#' << t << '\n';
		cin >> N >> M;
		init(); //각 테스트 케이스마다 시작되는 초기화
		cin >> num;
		for (int i = 0; i < num; i++) {
			cin >> cmd; //명령어
			switch (cmd)
			{
			case 100: //ADD
				cin >> id >> start >> end >> length;
				Add(id, start, end, length);
				break;
			case 200: //REMOVE
				cin >> id;
				Remove(id);
				break;
			case 300: //COST
				cin >> start >> end;
				//cout << "내 답: " << Cost(start, end) << '\n';
				break;
			default:
				break;
			}
		}
	}
	f = clock();
	cout << (double)(f - s) / CLOCKS_PER_SEC; //소요 시간 출력
	return 0;
}
