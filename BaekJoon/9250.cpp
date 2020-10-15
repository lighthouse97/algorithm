// 9250.cpp
// 문자열 집합 판별
// 지금따지 주로 다루었던 문자열 검색 방법은 하나의 문자열에 특정 문자열을 검색하는 것인데,
// 이번에 다루는 것은 M개의 문자열 집합에 N개의 문자열 집합이 포함되어 있는지를 검색하는 것이다.
// 예를 들어 문자열 집합 M은 {w1, w2, ... wl}이고 M에서 문자열 집합 N이 포함되어 있는지 검색하는 것이다.
// 집합 M의 각 단어의 문자 갯수를 m1, m2, ... mk라고 하면 단순 무식하게 탐색해서 찾아가면 시간 복잡도가
// O(N(m1+m2+...+mk))가 된다.
// 시간 복잡도를 줄이기 위해 개선된 알고리즘을 사용하면 시간 복잡도가 O(N+m1+m2+...+mk)로 줄어든다.
// 이 개선된 알고리즘이 아호-코라식(aho-corasick) 알고리즘이라고 하며,
// 9250 문제는 이 알고리즘을 응용도 하지 않고 직접적으로 바로 사용하는 문제이다.
// 구현을 위해서는 Trie를 활용하는데 Trie 각 노드에서 1) go 2) output 3) failure
// 이 3가지가 핵심적으로 구현되어져야 한다.
// 제한시간 2초 중 132ms(22,844KB)가 소요되었다.
// 맞은사람 45/380로 상위 11.84%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
//#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct Trie {
	Trie() : output(false) {
		for (int i = 0; i < 26; i++) go[i] = NULL;		
	}

	~Trie() {
		for (int i = 0; i < 26; i++) if (go[i]) delete go[i];
	}

	void insert(const char* c) {		
		if (*c == '\0') {
			output = true;
			return;
		}
		int next = *c - 'a';
		if (!go[next]) go[next] = new Trie;
		go[next]->insert(c + 1);		
	}

	Trie* go[26]; // child node
	bool output; // decide word complete               
	Trie* failure; // fail pointer
};

void makeFailure(Trie* root) // using BFS
{
	Trie *current, *next;
	queue<Trie*> myq;
	root->failure = root; // root의 fail은 root 자신이다!
	myq.push(root);

	while (!myq.empty()) {
		current = myq.front();
		myq.pop();
		for (int i = 0; i < 26; i++) {
			next = current->go[i];
			if (next == NULL) continue;
			if (current == root) next->failure = root; // root 바로 다음 node의 failure도 root이다.
			else {
				Trie* dest = current->failure;
				while (dest != root && dest->go[i] == NULL) dest = dest->failure; // fail에서 다음 node 찾지 못하면 최상단 fail(root)까지 간다.
				if (dest->go[i]) dest = dest->go[i]; // fail에서 다음 node가 있으면 그 node가 current->next의 fail이다.(잘 따져봐야 한다)
				next->failure = dest;
			}
			if (next->failure->output) next->output = true; // 소스 그대로다. 잘 따져보면 맞다!
			myq.push(next);
		} // for
	} // while			
}

int main()
{
	FAST;

	int N, Q;
	string str;
	Trie* root = new Trie;
	
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> str;
		root->insert(str.c_str());
	}
	makeFailure(root);
	cin >> Q;
	Trie* current = root;
	int next;
	bool result;
	for (int i = 0; i < Q; i++) {
		cin >> str;
		current = root;
		result = false;
		for (int j = 0; j < str.length(); j++) {
			next = str[j] - 'a';
			while (current != root && !(current->go[next])) current = current->failure; // current 다음 node찾지 못하여 fail로 가면 fail의 최상단까지 간다
			if (current->go[next]) current = current->go[next]; // 다음 노드있으면 current 이동
			if (current->output) { // current가 output에 도덜하면 주어진 문자열에서 key word를 찾은 것이다!
				result = true;
				break;
			}
		}
		cout << (result ? "YES" : "NO") << "\n";
	}
	// delete root; // OS can do it!
}