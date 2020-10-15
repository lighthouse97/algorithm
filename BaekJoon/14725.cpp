// 14725.cpp
// 개미굴
// 트라이에 대한 감을 잡는 문제라고 하는데 아직 트라이는 아직 모르고
// 일반적인 트리구조에 KMP 문자 검색을 이용하면 될 것 같다.
// 참고로 std::sort는 스트링 벡터에도 적용이 되었다!!!
// 자료 참고해서 아예 trie를 구현해 버렸다!
// University > 충남대학교 > 생각하는 프로그래밍 대회 J번
// 제한시간 1초 중 4ms(2400KB)가 소요되었다.
// 맞은사람 47/101로 상위 46.53%에 rank되었다.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

class trie
{
public:
	trie() { }
	trie(string name) : name(name) {}
	~trie() {
		next.clear();
	}
	void insert(vector<string>::iterator key);
	void traverse() { traverse(0); }
	bool operator < (trie& comp) {
		return (name < comp.name);
	}
private:
	string name;
	vector<trie> next;
	int find_name(const string& str);
	void traverse(int level);
};

void trie::insert(vector<string>::iterator key)
{
	int index;
	if (*key == "") return;
	index = find_name(*key);
	if (index == -1) { // next 배열에서 없으면 새로 추가하고 다음 스트링 insert
		next.push_back(trie(*key));
		next.back().insert(key + 1);
	}
	else
		next[index].insert(key + 1); // 있으면 그기에서 다음 스트링 insert
}

int trie::find_name(const string& str)
{
	for (int i = 0; i < (int)next.size(); i++) {
		if (str == next[i].name) return i;
	}
	return -1;
}

void trie::traverse(int level)
{
	int cnt = (level - 1)*2;
	if (level) {
		for (int i = 0; i < cnt; i++) cout << "-";
		cout << name << "\n";
	}
	if (next.size() > 0) {
		sort(next.begin(), next.end()); // next에 trie 객체가 여러개면 오름차순 정렬
		for (trie t : next) {
			t.traverse(level + 1);
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	string food;
	vector<string> floor;
	trie cave;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> K;
		for (int j = 0; j < K; j++) {
			cin >> food;
			floor.push_back(food);
		}
		floor.push_back(""); // 각 층의 마지막 표시
		cave.insert(floor.begin()); // trie에 삽입
		floor.clear();
	}
	cave.traverse();
}
