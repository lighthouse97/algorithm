// 2809_1.cpp
// 아스키 거리
// 이것도 접미사 배열(Suffix Array)나 아호-코라식 알고리즘을 사용하면
// 풀 수 있는 문제인데, 나는 아호-코라식 알고리즘을 사용하기로 한다.
// 타일 묶음을 트라이로 구성하고 거리의 알파벳을 순차 탐색하면서 일치하면 +1
// root로 돌아가면 0으로 돌아가서 다시 카운트 시작
// 순차 탐색 알파벳이 트라이의 완전한 단어(output == true)에 도달하면
// 지금까지 카운트를 누적한다.
// 거리의 알파벳 탐색이 모두 끝나고 거리의 알파벳 전체 문자수에서 카운트를 빼면
// 정답이 된다.
// 기존 방법대로 푸니 메모리 초과 발생해서 Trie 각 노드에 26개 Trie go 만들지 않고 unordered_map으로 관리한다.
// unordered_map이 map에 비해 tree balancing을 하지 않기 때문에 속도는 빠르다.
// Contest > Croatian Open Competition in Informatics > COCI 2011/2012 > Contest #5 6번
// 이 방법은 메모리 초과 발생하고 검색 알고리즘도 틀렸다. Forget It!!!

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
//#include <vector>
//#include <algorithm> // sort, max, min, copy, reverse
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct Trie;
typedef unordered_map<char, Trie*> mymap;

struct Trie {
	Trie() : output(false), terminal(false) {}

	~Trie() {
		for (auto& x : go) delete x.second;
		go.clear();
	}

	void insert(const string& str) {
		int n = (int)str.length();
		Trie* current = this; // root
		mymap::const_iterator it;
		for (int i = 0; i < n; i++) {
			it = (current->go).find(str[i]);
			if (it == (current->go).end()) {
				(current->go).insert({ str[i] , new Trie });
				it = (current->go).find(str[i]);
			}
			current = it->second;			
		}
		current->output = true;
		current->terminal = true;
	}

	unordered_map<char, Trie*> go; // child node
	bool output; // decide word complete
	bool terminal; // leaf node or not
	Trie* failure; // fail pointer
};

void makeFailure(Trie* root) // using BFS
{
	Trie *current, *next;
	queue<Trie*> myq;
	mymap::const_iterator it;
	root->failure = root;
	myq.push(root);

	while (!myq.empty()) {
		current = myq.front();
		myq.pop();
		for (auto& x : current->go) {
			next = x.second;			
			if (current == root) next->failure = root;
			else {
				Trie* dest = current->failure;
				it = (dest->go).find(x.first);
				while (dest != root && it == (dest->go).end()) {
					dest = dest->failure;
					it = (dest->go).find(x.first);
				}
				if (it != (dest->go).end()) dest = it->second;
				next->failure = dest;
			}
			if (next->failure->output) next->output = true;
			myq.push(next);
		} // for		
	} // while			
}

int count_matched(int N, const string& street, Trie* root)
{
	int fcnt = 0, ccnt = 0, answer = 0; // fcnt : fail node count, ccnt : current node count
	mymap::const_iterator it;
	Trie* current = root;
	for (int i = 0; i < N; i++) {
		it = (current->go).find(street[i]);
		while (current != root && it == (current->go).end()) {
			current = current->failure;
			it = (current->go).find(street[i]);
		}
		if (current == root) { // main line에서 일치하는게 없으면 fail line에서의 count를 적용한다.
			answer += fcnt;
			fcnt = ccnt = 0;
		}
		if (it != (current->go).end()) {
			current = it->second;
			ccnt++; // 일단 다음으로 진행하면 main line count 증가
			if (current->failure != root) fcnt++; // main line에 fail이 있으면 fcnt 증가
			// printf("char = %c, fcnt = %d, ccnt = %d, terminal = %d\n", street[i], fcnt, ccnt, current->terminal); /////
			if (current->output) {
				if (current->terminal) { // main line에서 일치하는게 있으면 main line의 count적용(굳이 max(fcnt, ccnt)는 안해도 될거 같음)					
					answer += ccnt;
					fcnt = ccnt = 0;
				}				
			}
		}		
	} // for
	return answer;
}

int main()
{
	FAST;

	int N, M;
	string street, tile;
	Trie* root = new Trie;
	cin >> N >> street;
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> tile;
		root->insert(tile);
	}	
	makeFailure(root);	

	int answer = count_matched(N, street, root);
	cout << N - answer << "\n";
}