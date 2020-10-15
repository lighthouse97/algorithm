// 10256.cpp
// 돌연변이
// 앞(9250)에서 풀었던 아호-코라식 알고리즘 이용하는 문제이다.
// 약간의 차이가 있다면 검색할 문자열(trie로 만들 문자열)이 미리
// 주어지는 것이 아니라 마커 문자열로부터 조합해서 만드는 점이
// 약간 다르다. 기타 나머지는 앞과 동일하다.
// dna의 최대 길이가 1,000,000이라 dna로 트라이 만들면 당연히 메모리 초과 발생하고
// 최대 길이 100인 마커로부터 트라이 만들고 dna로 검색하는 방법을 연구해야 한다.
// >>> 근본 문제는 문제를 제대로 이해하지 못했다.
// 1) marker로 부터 나올수 있는 돌연변이 문자열은 문자열을 1,2,3 세 부분으로 나누고 2에서 문자열 거꾸로 하는 건데 이를 이해못했다.
// 2) DNA 문자열에서 동일한 돌연변이 문자열이라도 위치가 다르면 중복 카운트하는데 이를 이해하지 못했다.
// 3) A, G, C, T 4가지 종류 밖에 없어서 각 트라이 노드에서 알파벳 26개 있을 필요없이 4개만 만들고 적절하게 conversion 해 주면 된다.
//    26개 다 사용하니 시간 초과가 발생하였다.
// 4) insert 함수를 재귀함수로 하면 느리므로 string으로 인자를 받아서 iteration 방법으로 처리하였다.
// >> 중복 돌연변이 제거하고 insert갯수 줄여서 해 보니 사전 작업 때문인지 최적화가 먹히지 않고 시간이 더 많이 걸렸다(1288ms -> 1332ms)
// ICPC > Regionals > Asia Pacific > Korea > Nationwide Internet Competition > Daejeon Nationalwide Internet Competition 2014 G번
// 제한시간 2초 중 1,288ms(16,256KB)가 소요되었다.
// 맞은사람 179/271로 상위 66.05%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy, reverse
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int s2n(const char c);

struct Trie {
	Trie() : output(false) {
		for (int i = 0; i < 4; i++) go[i] = NULL;
	}

	~Trie() {
		for (int i = 0; i < 4; i++) if (go[i]) delete go[i];
	}
	
	void insert(const string& str) {
		int n = (int)str.length();
		Trie* current = this;
		int next;
		for (int i = 0; i < n; i++) {			
			next = s2n(str[i]);
			if (!(current->go[next])) current->go[next] = new Trie;
			current = current->go[next];
		}
		current->output = true;
	}

	Trie* go[4]; // child node
	bool output; // decide word complete               
	Trie* failure; // fail pointer
};

int s2n(const char c) // A, C, G, T to number
{
	if (c == 'A') return 0;
	else if (c == 'C') return 1;
	else if (c == 'G') return 2;
	else return 3;
}

void makeFailure(Trie* root) // using BFS
{
	Trie *current, *next;
	queue<Trie*> myq;
	root->failure = root; // root의 fail은 root 자신이다!
	myq.push(root);

	while (!myq.empty()) {
		current = myq.front();
		myq.pop();
		for (int i = 0; i < 4; i++) {
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

void do_test()
{
	int n, m;
	string dna, marker;
	Trie* root = new Trie;
	cin >> n >> m;	
	cin >> dna >> marker;
	// make marker trie(not dna!)
	string sc;
	///vector<string> keys;
	for (int i = 0; i < m; i++) { // 1st 글자수
		for (int j = 1; j <= m - i; j++) { // 2nd 글자수
			sc = marker;
			reverse(sc.begin() + i, sc.begin() + i + j); // 2nd 글자부분만 뒤집는다.			
			root->insert(sc);
			///keys.push_back(sc); // 중복된 string 제거해서 insert 위함. 최적화. 꼭 안해도 됨.
		}
	}
	// 최적화 위해 중복된 string 제거하고 insert
	///sort(keys.begin(), keys.end()); // 정렬
	///keys.erase(unique(keys.begin(), keys.end()), keys.end()); // 연속된 중복 제거 및 빈칸 삭제
	///for (int i = 0; i < keys.size(); i++)
	///	root->insert(keys[i]);

	makeFailure(root);

	int pos = 0;
	Trie* current = root;
	int next, count = 0;
	while (pos < n) { // search from dna				
		next = s2n(dna[pos]);
		while (current != root && !(current->go[next])) current = current->failure;
		if (current->go[next]) current = current->go[next];
		if (current->output) count++;
		pos++;
	}
	cout << count << "\n";
	delete root;
}

int main()
{
	FAST;

	int T;
	cin >> T;
	for (int i = 0; i < T; i++) do_test();
}