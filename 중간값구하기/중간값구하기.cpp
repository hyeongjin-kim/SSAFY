#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;

int N;


int main() {
	int T;
	cin >> T;
	

	for (int t = 1; t <= T; t++) {
    //pq는 clear가 없기 때문에 매번 새로 선언했다. 모든 원소를 제거하는 쪽이 오히려 시간이 더 걸릴 것 같다.
		priority_queue<int, vector<int>, greater<>> minheap;
		priority_queue<int, vector<int>, less<>> maxheap;
		int mid, sum = 0, K = 20171109, a, b ;
		cin >> N >> mid;
		
		for (int i = 0; i < N; i++) {
			cin >> a >> b;
			if (a >= mid) minheap.push(a); //크면 minheap에 넣기
			else maxheap.push(a); //작으면 maxheap에 넣기
			if (b >= mid)minheap.push(b); //크면 minheap에 넣기
			else maxheap.push(b); //작으면 maxheap에 넣기

			if (minheap.size() > maxheap.size()) { //둘 다 minheap에 넣은 경우
				maxheap.push(mid); //mid를 maxheap에
				mid = minheap.top(); //minheap의 top이 새로운 mid
				minheap.pop();
			}
			else if (minheap.size() < maxheap.size()) {//둘 다 maxheap에 넣은 경우
				minheap.push(mid); //mid를 minheap에
				mid = maxheap.top();//maxheap의 top이 새로운 mid
				maxheap.pop();
			}
			
			sum += mid;
			sum %= K;
		}
		cout << '#' << t << ' ' << sum << '\n';
	}
	return 0;
}
