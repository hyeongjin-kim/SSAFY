#include <cstring>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;
const int MAX_MAKE_LIST = 10;
const int MAX_LENGTH = 200000;
const int MAX_ADDRESS = 6000;
const int MAX_CHANGE = 110000;

int initNumber;  // 만들어진 배열의 개수
int initValue[MAX_MAKE_LIST + 1][MAX_LENGTH + 1];  // 초기 배열 정보

int addressNumber;  // 존재하는 배열의 개수
unordered_map<string, int> address;  // key: 배열 이름, value: 원본 배열의 번호

int changeNumber;  // 변화 개수
pair<int, int> changeLog[MAX_CHANGE + 1];  // 모든 변화 기록을 담는 배열
	// makeList         : (-1, 원본 배열 번호)
	// copyList         : (-1, -1) 정보 추가하기. (deepcopy를 의미함)
	// updateElement    : (인덱스, 값) ; 인덱스의 값을 변경했다.

int lastChange[MAX_ADDRESS + 1]; // lastChange[i] := i번 원본 배열의 마지막 변화 event 번호
int prevChange[MAX_CHANGE + 1];  // prevChange[i] := i번 변화의 직전 변화 event 번호

void init()
{
	addressNumber = 0;
	changeNumber = 0;
	address.clear();
	initNumber = 0;
}

void makeList(char mName[], int mLength, int mListValue[])
{
	memcpy(initValue[initNumber], mListValue, mLength * sizeof(int)); //데이터 복사

    address[string(mName)] = addressNumber; //자기 자신이 원본
    addressNumber++;

    changeLog[changeNumber] = {-1, initNumber}; //신규 생성을 의미하는 log
    prevChange[changeNumber] = -1; //이전 변화는 없음
    lastChange[address[string(mName)]] = changeNumber; //새로운 변화 기록
    changeNumber++;

    initNumber++;
}

void copyList(char mDest[], char mSrc[], bool mCopy)
{
	if (mCopy) {
		address[mDest] = addressNumber++; //자기 자신이 새로운 원본이 됨
		changeLog[changeNumber] = { -1, -1 }; //deep copy를 의미
		prevChange[changeNumber] = lastChange[address[mSrc]]; //지금까지 있던 원본배열의 변화중 마지막 위치를 가리킴
		lastChange[address[mDest]] = changeNumber; //새로운 변화 기록
		changeNumber++;
	}
	else {
		address[mDest] = address[mSrc]; //원본 배열과 똑같은 취급
	}

}

void updateElement(char mName[], int mIndex, int mValue)
{
	changeLog[changeNumber] = { mIndex, mValue }; //어떤 위치에 어떤 값을 삽입했다는 것을 기록
	prevChange[changeNumber] = lastChange[address[mName]]; //이 전 변화 갱신
	lastChange[address[mName]] = changeNumber; //새로운 변화 기록
	changeNumber++;

}

int element(char mName[], int mIndex)
{
	int c = lastChange[address[mName]];
	while (true) {
		if (prevChange[c] == -1) { //더 이상 변화가 없음 == 최초의 생성
			return initValue[changeLog[c].second][mIndex];
		}
		else if (changeLog[c].first == mIndex) //해당 인덱스가 직접 변한 적이 있음
			return changeLog[c].second;
		else c = prevChange[c];
	}
}
