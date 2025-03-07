#include <iostream>
#include <queue>
using namespace std;

int N;
int arr[100] = {};

int main() {
    int T;
    cin >> T;
    
    
    int one, two; //최대 높이까지 1, 2만 남은 나무의 개수
    for (int t = 1; t <= T; t++) {
        cin >> N;
        one = 0;
        two = 0;
        int max = 0; //가장 큰 나무의 높이
        priority_queue<int> q; //나무들의 높이를 넣을 pq(높이를 음수로 넣어 가장 낮은 나무부터 나옴)
        for (int i = 0; i < N; i++) {
            cin >> arr[i];
            if (arr[i] > max) max = arr[i]; //max찾기
        }
        for (int i = 0; i < N; i++) {
            if (max - arr[i] == 1) one++; //최대랑 1차이인 경우 q에 넣지 않고 one증가
            else if (max - arr[i] == 2) two++; //최대랑 2차이인 경우 q에 넣지 않고 two증가
            else if (max > arr[i]) q.push(-arr[i]); //둘 다 아니면 q에 음수로 넣기 max와 같은 경우는 넣을 필요 없음
        }
        int day = 0; //오늘 날짜
        while (!q.empty()) {
            int cur = -q.top();
            if (cur == max) break; //가장 낮은 나무가 max다 == 모든 나무가 max다
            if (day % 2 == 1) { //홀수번째 날인 경우 == 물을 주면 2만큼 자라는 날(0부터 시작하므로)
                if (two > 0) { //최대에서 2만큼 모자란 나무가 있는 경우 여기에 물을 줌
                    two--; 
                    day++;
                }
                else {
                    q.pop(); //아니면 다른 가장 작은 나무에 물을 줌
                    if (max - cur == 3) { //물을 줬을 때 최대에서 1만큼 모자라지는 경우
                        one++;
                        day++;
                    }
                    else if (max - cur == 4) {//물을 줬을 때 최대에서 2만큼 모자라지는 경우
                        two++;
                        day++;
                    }
                    else {
                        q.push(-(cur + 2)); //그외 일반적인 경우
                        day++;
                    }
                }
            }
            else {//짝수번째 날인 경우 == 물을 주면 1만큼 자라는 날
                if (one > 0) { //최대에서 1만큼 모자란 나무가 있는 경우 여기에 물을 줌
                    one--;
                    day++;
                }
                else {
                    q.pop();
                    if (max - cur == 3) {//물을 줬을 때 최대에서 2만큼 모자라지는 경우
                        two++;
                        day++;
                    }
                    else {
                        q.push(-(cur + 1)); //그외 일반적인 경우
                        day++;
                    }
                }
            }

        }
        //모든 나무에 물을 줬음 남은건 1 또는 2만큼 남은 경우인데, one 또는 two 둘 중 하나는 반드시 0임
        //증명
        //1만큼 자라는 날에 2만큼 자라는 나무가 남고 끝나는 경우 -> 1만큼 남은 나무가 없어야 새로운 나무에 물을 줌 따라서 one == 0
        //1만큼 자라는 날에 1만큼 자라는 나무가 남고 끝나는 경우 -> one 이 0이어야 q에서 원소를 제거함 따라서 불가능
        //2만큼 자라는 날에 2만큼 자라는 나무가 남고 끝나는 경우 -> two가 0이어야 q에서 원소를 제거함 따라서 불가능
        //2만큼 자라는 날에 1만큼 자라는 나무가 남고 끝나는 경우 -> 2만큼 남은 나무가 없어야 새로운 나무에 물을 줌 따라서 two == 0
        if (one > two){ //1만큼 남은 나무만 남은 경우 
            day += one * 2 -(day%2 == 0); //2일에 한번 물을 줄 수 있으므로 남은 나무수 *2일이 걸림 단, 오늘이 1만큼 자라는 날이면 바로 줄 수 있으므로 -1
        }
        else if(one < two) {//2만큼 남은 나무만 남은 경우
            day += two * 2 - day % 2; //2일에 한번 물을 줄 수 있으므로 남은 나무수 *2일이 걸림 단, 오늘이 2만큼 자라는 날이면 바로 줄 수 있으므로 -1
        }
        cout << '#' << t << ' ' << day << '\n';
    }
}
