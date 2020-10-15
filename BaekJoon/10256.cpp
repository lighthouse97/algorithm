// 10256.cpp
// ��������
// ��(9250)���� Ǯ���� ��ȣ-�ڶ�� �˰��� �̿��ϴ� �����̴�.
// �ణ�� ���̰� �ִٸ� �˻��� ���ڿ�(trie�� ���� ���ڿ�)�� �̸�
// �־����� ���� �ƴ϶� ��Ŀ ���ڿ��κ��� �����ؼ� ����� ����
// �ణ �ٸ���. ��Ÿ �������� �հ� �����ϴ�.
// dna�� �ִ� ���̰� 1,000,000�̶� dna�� Ʈ���� ����� �翬�� �޸� �ʰ� �߻��ϰ�
// �ִ� ���� 100�� ��Ŀ�κ��� Ʈ���� ����� dna�� �˻��ϴ� ����� �����ؾ� �Ѵ�.
// >>> �ٺ� ������ ������ ����� �������� ���ߴ�.
// 1) marker�� ���� ���ü� �ִ� �������� ���ڿ��� ���ڿ��� 1,2,3 �� �κ����� ������ 2���� ���ڿ� �Ųٷ� �ϴ� �ǵ� �̸� ���ظ��ߴ�.
// 2) DNA ���ڿ����� ������ �������� ���ڿ��̶� ��ġ�� �ٸ��� �ߺ� ī��Ʈ�ϴµ� �̸� �������� ���ߴ�.
// 3) A, G, C, T 4���� ���� �ۿ� ��� �� Ʈ���� ��忡�� ���ĺ� 26�� ���� �ʿ���� 4���� ����� �����ϰ� conversion �� �ָ� �ȴ�.
//    26�� �� ����ϴ� �ð� �ʰ��� �߻��Ͽ���.
// 4) insert �Լ��� ����Լ��� �ϸ� �����Ƿ� string���� ���ڸ� �޾Ƽ� iteration ������� ó���Ͽ���.
// >> �ߺ� �������� �����ϰ� insert���� �ٿ��� �� ���� ���� �۾� �������� ����ȭ�� ������ �ʰ� �ð��� �� ���� �ɷȴ�(1288ms -> 1332ms)
// ICPC > Regionals > Asia Pacific > Korea > Nationwide Internet Competition > Daejeon Nationalwide Internet Competition 2014 G��
// ���ѽð� 2�� �� 1,288ms(16,256KB)�� �ҿ�Ǿ���.
// ������� 179/271�� ���� 66.05%�� rank�Ǿ���.

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
	root->failure = root; // root�� fail�� root �ڽ��̴�!
	myq.push(root);

	while (!myq.empty()) {
		current = myq.front();
		myq.pop();
		for (int i = 0; i < 4; i++) {
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
	for (int i = 0; i < m; i++) { // 1st ���ڼ�
		for (int j = 1; j <= m - i; j++) { // 2nd ���ڼ�
			sc = marker;
			reverse(sc.begin() + i, sc.begin() + i + j); // 2nd ���ںκи� �����´�.			
			root->insert(sc);
			///keys.push_back(sc); // �ߺ��� string �����ؼ� insert ����. ����ȭ. �� ���ص� ��.
		}
	}
	// ����ȭ ���� �ߺ��� string �����ϰ� insert
	///sort(keys.begin(), keys.end()); // ����
	///keys.erase(unique(keys.begin(), keys.end()), keys.end()); // ���ӵ� �ߺ� ���� �� ��ĭ ����
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