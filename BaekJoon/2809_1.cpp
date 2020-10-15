// 2809_1.cpp
// �ƽ�Ű �Ÿ�
// �̰͵� ���̻� �迭(Suffix Array)�� ��ȣ-�ڶ�� �˰����� ����ϸ�
// Ǯ �� �ִ� �����ε�, ���� ��ȣ-�ڶ�� �˰����� ����ϱ�� �Ѵ�.
// Ÿ�� ������ Ʈ���̷� �����ϰ� �Ÿ��� ���ĺ��� ���� Ž���ϸ鼭 ��ġ�ϸ� +1
// root�� ���ư��� 0���� ���ư��� �ٽ� ī��Ʈ ����
// ���� Ž�� ���ĺ��� Ʈ������ ������ �ܾ�(output == true)�� �����ϸ�
// ���ݱ��� ī��Ʈ�� �����Ѵ�.
// �Ÿ��� ���ĺ� Ž���� ��� ������ �Ÿ��� ���ĺ� ��ü ���ڼ����� ī��Ʈ�� ����
// ������ �ȴ�.
// ���� ������ Ǫ�� �޸� �ʰ� �߻��ؼ� Trie �� ��忡 26�� Trie go ������ �ʰ� unordered_map���� �����Ѵ�.
// unordered_map�� map�� ���� tree balancing�� ���� �ʱ� ������ �ӵ��� ������.
// Contest > Croatian Open Competition in Informatics > COCI 2011/2012 > Contest #5 6��
// �� ����� �޸� �ʰ� �߻��ϰ� �˻� �˰��� Ʋ�ȴ�. Forget It!!!

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
		if (current == root) { // main line���� ��ġ�ϴ°� ������ fail line������ count�� �����Ѵ�.
			answer += fcnt;
			fcnt = ccnt = 0;
		}
		if (it != (current->go).end()) {
			current = it->second;
			ccnt++; // �ϴ� �������� �����ϸ� main line count ����
			if (current->failure != root) fcnt++; // main line�� fail�� ������ fcnt ����
			// printf("char = %c, fcnt = %d, ccnt = %d, terminal = %d\n", street[i], fcnt, ccnt, current->terminal); /////
			if (current->output) {
				if (current->terminal) { // main line���� ��ġ�ϴ°� ������ main line�� count����(���� max(fcnt, ccnt)�� ���ص� �ɰ� ����)					
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