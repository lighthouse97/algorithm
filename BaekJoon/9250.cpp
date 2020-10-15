// 9250.cpp
// ���ڿ� ���� �Ǻ�
// ���ݵ��� �ַ� �ٷ���� ���ڿ� �˻� ����� �ϳ��� ���ڿ��� Ư�� ���ڿ��� �˻��ϴ� ���ε�,
// �̹��� �ٷ�� ���� M���� ���ڿ� ���տ� N���� ���ڿ� ������ ���ԵǾ� �ִ����� �˻��ϴ� ���̴�.
// ���� ��� ���ڿ� ���� M�� {w1, w2, ... wl}�̰� M���� ���ڿ� ���� N�� ���ԵǾ� �ִ��� �˻��ϴ� ���̴�.
// ���� M�� �� �ܾ��� ���� ������ m1, m2, ... mk��� �ϸ� �ܼ� �����ϰ� Ž���ؼ� ã�ư��� �ð� ���⵵��
// O(N(m1+m2+...+mk))�� �ȴ�.
// �ð� ���⵵�� ���̱� ���� ������ �˰����� ����ϸ� �ð� ���⵵�� O(N+m1+m2+...+mk)�� �پ���.
// �� ������ �˰����� ��ȣ-�ڶ��(aho-corasick) �˰����̶�� �ϸ�,
// 9250 ������ �� �˰����� ���뵵 ���� �ʰ� ���������� �ٷ� ����ϴ� �����̴�.
// ������ ���ؼ��� Trie�� Ȱ���ϴµ� Trie �� ��忡�� 1) go 2) output 3) failure
// �� 3������ �ٽ������� �����Ǿ����� �Ѵ�.
// ���ѽð� 2�� �� 132ms(22,844KB)�� �ҿ�Ǿ���.
// ������� 45/380�� ���� 11.84%�� rank�Ǿ���.

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
	root->failure = root; // root�� fail�� root �ڽ��̴�!
	myq.push(root);

	while (!myq.empty()) {
		current = myq.front();
		myq.pop();
		for (int i = 0; i < 26; i++) {
			next = current->go[i];
			if (next == NULL) continue;
			if (current == root) next->failure = root; // root �ٷ� ���� node�� failure�� root�̴�.
			else {
				Trie* dest = current->failure;
				while (dest != root && dest->go[i] == NULL) dest = dest->failure; // fail���� ���� node ã�� ���ϸ� �ֻ�� fail(root)���� ����.
				if (dest->go[i]) dest = dest->go[i]; // fail���� ���� node�� ������ �� node�� current->next�� fail�̴�.(�� �������� �Ѵ�)
				next->failure = dest;
			}
			if (next->failure->output) next->output = true; // �ҽ� �״�δ�. �� �������� �´�!
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
			while (current != root && !(current->go[next])) current = current->failure; // current ���� nodeã�� ���Ͽ� fail�� ���� fail�� �ֻ�ܱ��� ����
			if (current->go[next]) current = current->go[next]; // ���� ��������� current �̵�
			if (current->output) { // current�� output�� �����ϸ� �־��� ���ڿ����� key word�� ã�� ���̴�!
				result = true;
				break;
			}
		}
		cout << (result ? "YES" : "NO") << "\n";
	}
	// delete root; // OS can do it!
}