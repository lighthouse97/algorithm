// 14425.cpp
// Trie 그 자체를 이용하는 문제이다.
// 참고로 string에서 string.end()의 값을 참조하면 visual c++에서 assert가 발생한다.
// 이점 명시해 주자!!!
// 다른 빠른 방법(대표적으로 std::unordered_set의 count를 이용한다)도 많지만 출제자 의도대로 trie를 사용해서 풀었다.
// 제한시간 2초 중 796ms(235,760KB)가 소요되었다.
// 맞은사람 434/759로 상위 57.18%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

class trie
{
public:
	trie() : alphabet(0), is_terminal(false) { }
	trie(const char& a) : alphabet(a), is_terminal(false) {}
	~trie() {
		child.clear();
	}
	void insert(string::iterator it, string::iterator end);
	bool find_name(string::iterator it, string::iterator end);
	
private:
	char alphabet;
	vector<trie> child;
	bool is_terminal;
	int find_alpha(const char& a);
};

void trie::insert(string::iterator it, string::iterator end)
{
	if (it == end) {
		is_terminal = true;		
	}
	else {
		int index = find_alpha(*it);
		if (index > -1) child[index].insert(it + 1, end);
		else {			
			child.push_back(trie(*it));
			child.back().insert(it + 1, end);
		}
	}
}

int trie::find_alpha(const char& a)
{
	for (int i = 0; i < child.size(); i++) {
		if (a == child[i].alphabet)
			return i;
	}
	return -1;
}

bool trie::find_name(string::iterator it, string::iterator end)
{
	if (it == end) {
		if (is_terminal) return true;
		else return false;
	}
		
	int index = find_alpha(*it);
	if (index < 0) 
		return false;
	else {
		return child[index].find_name(it + 1, end);
	}
}

int main()
{
	FAST;

	trie* root = new trie;
	int N, M;
	int count = 0;
	string str;
	cin >> N >> M;

	// input string
	for (int i = 0; i < N; i++) {
		cin >> str;
		root->insert(str.begin(), str.end());
	}

	// find string
	for (int i = 0; i < M; i++) {
		cin >> str;
		if (root->find_name(str.begin(), str.end())) count++;
	}
	cout << count << "\n";
}