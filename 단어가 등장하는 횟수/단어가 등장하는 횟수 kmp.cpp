#include <iostream>
#include <string>
#include <cstring>

using namespace std;

string book;
string word;
int arr[100000];
int ans = 0;

void pi() { //word 자신과 비교하면서 지금까지 본 문자열의 prefix와 suffix같은 부분의 길이를 구함
	//예를 들어 지금까지 본 문자열이 awerasd이면 d에서 틀린 것을 확인했을 때 다음 번호부터 시작하면 되지만,
	//지금까지 본 문자열이 asdfas인 경우, 마지막의 s에서 틀렸으면 prefix와 suffix의 as가 겹치므로 세번째 문자부터 다시 확인함
	int l = word.size();
	memset(arr, 0, sizeof(arr));
	for (int i = 1, j = 0; i < l; i++) {
		while (j > 0 and word[i] != word[j]) j = arr[j - 1];
		if (word[i] == word[j]) arr[i] = ++j; //prefix와 subfix가 같은 부분 발생
	}
}

void kmp() {//pi함수에서 한 것과 거의 동일한 것을 수행함
	//단, arr을 수정하지 않고, j가 word의 길이까지 도달하면 동일한 문자열이 있는 것이므로 ans++함
	ans = 0;
	int l = word.size();
	int m = book.size();
	for (int i = 0, j = 0; i < m; i++) {
		while (j > 0 and book[i] != word[j]) j = arr[j - 1]; //다른 부분이 생기면 지금까지 같은 prefix와 suffix의 길이를 설정해 거기서부터 다시 탐색
		if (book[i] == word[j]) {
			if (j == l - 1) {
				ans++;
				j = arr[j]; //지금까지 같은 prefix와 suffix의 길이를 설정해 거기서부터 다시 탐색
			}
			else j++;
		}
	}
}

int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		cin >> book >> word;
		pi();
		kmp();
		cout << '#' << t << ' ' << ans << '\n';
	}

	return 0;
}
