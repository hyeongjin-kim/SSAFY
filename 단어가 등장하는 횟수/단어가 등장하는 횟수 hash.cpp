#include <iostream>
#include <string>
#include <cstring>

using namespace std;

string book; //책 내용을 담는 string
string word; //찾을 단어를 담는 string
int ans = 0;
long long int wordhash; //단어를 hasing한 값
long long int bookhash; //책의 현재 보고 있는 부분을 hashing한 값
int key = 67; //62개의 문자가 겹치지 않도록 겹치지 않도록 더 큰 소수를 찾아 사용함


int char_to_code(char c) { //책에 포함되는 문자를 0~61의 숫자에 mapping함
	if ('0' <= c and c <= '9') return c - '0';
	if ('a' <= c and c <= 'z') return c - 'a' + 11;
	if ('A' <= c and c <= 'Z') return c - 'A' + 37;
	return -1; //error;
}

void init_bookhashing() { //책의 맨 앞부분을 hashing함
	bookhash = 0;
	for (int i = 0; i < word.size(); i++) {
		bookhash = bookhash * key + char_to_code(book[i]);
	}
}

void hashing_word() { //단어를 hashing함
	wordhash = 0;
	for (int i = 0; i < word.size(); i++) {
		wordhash = wordhash * key + char_to_code(word[i]);
	}
}

int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		cin >> book >> word;
		ans = 0;
		init_bookhashing();
		hashing_word();
		long long int off = 1;
		for(int i = 0; i < word.size() - 1; i++)  off *= key; //계속 제거해나갈 hash값의 가장 앞자리를 찾아주는 배수
		for (int i = 0; i < book.size() - word.size(); i++) {
			if (wordhash == bookhash) ans++; //hash 값이 같으면 같은 단어가 있음
			bookhash = (bookhash - off * char_to_code(book[i])) * key + char_to_code(book[i + word.size()]);//가장 앞자리의 hash를 제거하고, 한자리씩 앞으로 민 다음에 가장 낮은 자리에 새 값을 추가함
		}
		if (wordhash == bookhash) ans++; //마지막 hashing을 한 뒤에 한번 더 확인해야 함
		cout << '#' << t << ' ' << ans << '\n';
	}

	return 0;
}
