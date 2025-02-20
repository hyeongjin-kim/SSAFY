#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include <queue>
using namespace std;

int ans, N, M;

vector<int> vleaf[501]; //leaf - > root 탐색할 때 사용할 연결리스트
vector<int> vroot[501]; //root - > leaf 탐색할 때 사용할 연결리스트

set<int> root, leaf; //탐색을 시작할 때 필요한 root들과 leaf들을 담은 set

int visit[501]; //root -> leaf 탐색할 때 수집된 정보의 수를 저장할 배열
int visit2[501]; //leaf -> root 탐색할 때 수집된 정보의 수를 저장할 배열


//각 학생을 의미하는 구조체 최대 500개의 bit를 필요로 하는데 64 * 8 = 512이므로 8개의 64비트  int를 가짐
struct student { 
	uint64_t arr[8]; //i번째 학생은 arr[i/64]의 i %64번째 비트에 저장
};

student compare; //순위를 알 수 있는지 확인하기 위한 비교대상

uint64_t one = 1; //shift연산때 사용할 1

student rootcheck[501]; //root -> leaf 탐색을 할 때 자기보다 작은 학생들을 기록할  bit들
student leafcheck[501]; //leaf -> root 탐색을 할 때 자기보다 큰 학생들을 기록할  bit들

void init() { //각 테스트 케이스마다 초기화와 입력을 받아오기 위한 함수
	ans = 0;
	cin >> N >> M;
	int a, b;
	//초기화
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
		compare.arr[i / 64] |= one << (i % 64);//비교 대상을 만드는 작업. N까지 모든 bit를 1로 만듬
	}
	//leaf와 root를 찾기 위해 모든 노드를 넣음
	for (int i = 0; i < N; i++) {
		leaf.insert(i + 1);
		root.insert(i + 1);
	}
	//비교 대상의 0번째 bit는 0이어야 함 그래서 오른쪽 왼쪽 shift를 한번씩 함
	compare.arr[0] = compare.arr[0] >> 1;
	compare.arr[0] = compare.arr[0] << 1;

	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		vleaf[b].push_back(a); //leaf -> root를 위한 연결 리스트
		vroot[a].push_back(b); //root -> leaf를 위한 연결리스트
		leaf.erase(a); //자기보다 큰 노드가 있으면 leaf가 아님
		root.erase(b); //자기보다 작은 노드가 있으면 root가 아님
	}

}

void search() {
	queue<int> q;
	//root내의 모든 노드 추가 root들은 자기보다 작은 노드가 없기 때문에 탐색을 위해 필요한 정보가 없음
	for (int node : root) {
		q.push(node);
		visit[node] = 1;
	}
	while (!q.empty()) {
		int cur = q.front();

		q.pop();
		
		//cur 노드와 연결된 모든 노드 확인
		for (int node : vroot[cur]) {
			visit[node] += 1; //확인한 횟수 증가
			if (visit[node] == vleaf[node].size()) { // vleaf[node].size() = node와 연결된 노드의 수 
				q.push(node); //자기와 연결된 노드에서 모두 이 노드를 확인했으면 q에 push
			}

			rootcheck[node].arr[cur / 64] |= one << (cur % 64); //cur은 node보다 작음을 표시

			//cur이 node보다 작으므로 cur보다 작은 노드는 node보다 작음
			for (int i = 0; i < 8; i++) {
				rootcheck[node].arr[i] |= rootcheck[cur].arr[i]; //cur에 있던 정보를 node에 표시
			}
		}

	}

}

void search2() {
	queue<int> qq;
	//leaf내의 모든 노드 추가 leaf들은 자기보다 큰 노드가 없기 때문에 탐색을 위해 필요한 정보가 없음
	for (int node : leaf) {
		qq.push(node);
		visit2[node] = 1;
	}
	while (!qq.empty()) {
		int cur = qq.front();
		qq.pop();

		//cur 노드와 연결된 모든 노드 확인
		for (int node : vleaf[cur]) {
			visit2[node] += 1; //확인한 횟수 증가
			if (visit2[node] == vroot[node].size()) { // vroot[node].size() = node보다 큰 노드의 수 
				qq.push(node); //자기와 연결된 노드에서 모두 이 노드를 확인했으면 qq에 push

			}

			leafcheck[node].arr[cur / 64] |= one << (cur % 64); //cur은 node보다 큼을 표시

			//cur이 node보다 크므로 cur보다 큰 노드는 node보다 큼
			for (int i = 0; i < 8; i++) {
				leafcheck[node].arr[i] |= leafcheck[cur].arr[i]; //cur에 있던 정보를 node에 표시
			}
		}

	}
}

int main() {

	init();
	search();
	search2();

	//순위를 알 수 있는지 확인하기
	for (int i = 1; i <= N; i++) {
		rootcheck[i].arr[i / 64] |= one << (i % 64); //자기 자신에 해당하는 bit 채우기
		int flag = 1; //순위를 알 수 있는지 확인하는 flag

		for (int j = 0; j < 8; j++) {
			if (((rootcheck[i].arr[j] | leafcheck[i].arr[j])) == compare.arr[j]) continue; //rootcheck와 leafcheck를 or했을 때 비교 대상과 같으면 아직 유효
			//비교대상과 다르면 순위를 알 수 없는 거
			flag = 0;
			break;
		}
		if (flag) ans++;
	}
	cout << ans << '\n';

	return 0;
}