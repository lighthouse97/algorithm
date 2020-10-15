// 2809.cpp
// 아스키 거리
// Contest > Croatian Open Competition in Informatics > COCI 2011/2012 > Contest #5 6번
// Suffix Array와 Aho-Corasick 두 방법으로 풀 수 있는데 본인은 Aho-Corasick algorithm을 이용하여 풀었다.
// 메모리 초과가 발생해서 trie 각 노드마다 26개의 알파벳 배열을 모두 잡지 않고 unordered_map으로 잡았는데,
// 그래도 메모리 초과가 발생했다. map이 메모리를 많이 먹기는 한다.
// 그래서 벡터와 bitset(bit masking)을 사용해서 메모리 사용량을 더 줄여보기로 하자.
// bit masking와 벡터의 인덱스를 맞추어 좀 더 빠르게 찾아갈 수 있도록 하였다.
// 문자열 처음부터 검색하면 도저히 답이 안나온다. (이거 때문에 며칠을 끌었다.)
// 잘 하는 사람이 푼 것을 참고하여 힌트를 얻었는데, 문자열 끝부터 검색해야 한다.
// 예외 케이스 경우가 많기 때문에 잘 따져봐야 한다. 예외 케이스 마다 일일이 대응 했기에 시간이 많이 걸렸다.
// 참고로 수행 시간이 1초 이내로 빠르게 푼 사람들은 모두 Suffix Array를 이용해서 푼 것이다.
// 제한시간 4초 중 1,416ms(378,412KB)가 소요되었다.
// 맞은사람 24/66로 상위 36.36%에 rank되었다.

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
//#include <unordered_map> // unordered_map
#include <bitset>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct Trie;

int bit2index(const bitset<26>& bits, int p)
{
	int cnt = 0;
	for (int i = 0; i < p; i++)
		if (bits.test(26 - i - 1)) cnt++;
	return cnt;
}

int index2bit(const bitset<26>& bits, int index)
{
	int cnt = 0, i;
	for (i = 0; i < 26; i++) {
		if (bits.test(26 - i - 1)) cnt++;
		if (index + 1 == cnt) break;
	}
	return i;
}

inline int conv_bit(int nth) { return (26 - nth - 1); }

struct Trie {
	Trie() : output(0) {}

	~Trie() {
		for (Trie* x : go) delete x;
		go.clear();		
	}

	void insert(const string& str) {
		int n = (int)str.length();
		int pos, index;
		Trie* current = this; // root

		for (int i = 0; i < n; i++) {
			pos = str[i] - 'a';
			index = bit2index(current->alpha, pos);
			if (!(current->alpha).test(conv_bit(pos))) {
				(current->alpha).set(conv_bit(pos));
				(current->go).insert((current->go).begin() + index, new Trie);
			}
			current = (current->go)[index];
		}
		current->output = n;		
	}

	bitset<26> alpha; // 알파벳 순서대로 bitmasking(MSB)
	vector<Trie*> go; // child node
	int output; // decide word complete	
	Trie* failure; // fail pointer
};

void makeFailure(Trie* root) // using BFS
{
	Trie *current, *next;
	int pos;
	queue<Trie*> myq;	
	root->failure = root;
	myq.push(root);

	while (!myq.empty()) {
		current = myq.front();
		myq.pop();
		for (int i = 0; i < (current->go).size(); i++) {
			next = (current->go)[i];
			if (current == root) {
				next->failure = root;				
			}
			else {
				// go[i]의 알파벳을 알고, 이 알파벳이 dest에도 있는지 체크한다
				Trie* dest = current->failure;
				pos = index2bit(current->alpha, i);
				while (dest != root && (dest->alpha).test(conv_bit(pos)) == false) dest = dest->failure;
				if ((dest->alpha).test(conv_bit(pos))) dest = (dest->go)[bit2index(dest->alpha, pos)];				
				next->failure = dest;
			}
			if (next->output < next->failure->output) next->output = next->failure->output;
			myq.push(next);
		} // for
	} // while	
}

int count_not_matched(int N, const string& street, Trie* root)
{
	int pos, answer = 0; // answer : 일치하지 않는 문자수
	vector<int> mark;	
	Trie* current = root;
	
	mark.resize(N, 0);
	for (int i = 0; i < N; i++) {
		pos = street[i] - 'a';		
		while (current != root && !(current->alpha).test(conv_bit(pos)))
			current = current->failure;
		if ((current->alpha).test(conv_bit(pos))) {
			current = (current->go)[bit2index(current->alpha, pos)];			
			if (current->output) mark[i] = max(mark[i], current->output);			
		}
	} // for
	int index = N - 1; // 거꾸로부터 탐색한다. 이것이 핵심이다! 앞에서 부터 검색하면 시간 낭비만 할 뿐이다!!!
	int check, start, temp_start;
	while (index >= 0) {
		if (mark[index] == 0) { answer++; index--; } // count not matched
		else {
			start = index - mark[index] + 1;
			check = mark[index];
			while (--check) {
				pos = check - mark[index] + index;
				if (mark[pos]) {
					temp_start = pos - mark[pos] + 1;
					if (temp_start <= start) {
						index = pos;
						break;
					}				
				}
			} // while
			if (check == 0) index = start - 1;						
		} // else
	} // while
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

	int answer = count_not_matched(N, street, root);	
	cout << answer << "\n";
}