// 14425.cpp
// Trie �� ��ü�� �̿��ϴ� �����̴�.
// ����� string���� string.end()�� ���� �����ϸ� visual c++���� assert�� �߻��Ѵ�.
// ���� ����� ����!!!
// �ٸ� ���� ���(��ǥ������ std::unordered_set�� count�� �̿��Ѵ�)�� ������ ������ �ǵ���� trie�� ����ؼ� Ǯ����.
// ���ѽð� 2�� �� 796ms(235,760KB)�� �ҿ�Ǿ���.
// ������� 434/759�� ���� 57.18%�� rank�Ǿ���.

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