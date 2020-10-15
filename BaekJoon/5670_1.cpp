// 5670_1.cpp
// 휴대용 자판
// 문제는 풀었지만, 코드가 일반적이지 못하고 지저분해서
// 보편적이고 일반적인 방법으로 다시 풀어보았다.
// 그런데 이 방법으로 푸니 시간이 더 많이 나왔다.(384ms -> 804ms)

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

char word[100000][81] = { {0, }, };

class trie
{
public:
	trie() : is_terminal(false), child_cnt(0) {
		child.resize(26, 0);
	}	
	~trie() {
		for (trie* x : child) if(x != NULL) delete x;
		child.clear();
	}
	void insert(char* c);
	void find_name(char* c, int& count);

	static bool is_initial;
private:	
	vector<trie*> child;
	bool is_terminal;
	int child_cnt;	
};

bool trie::is_initial = true;

void trie::insert(char* c)
{
	if (*c == '\0') {
		is_terminal = true;
	}
	else {
		int index = *c - 'a';		
		if (child[index] != NULL) child[index]->insert(c + 1);
		else {
			child[index] = new trie();
			child[index]->insert(c + 1);
			child_cnt++;
		}
	}
}

void trie::find_name(char* c, int& count)
{
	if (*c == '\0')
		return;
	if (is_initial) { // 처음일때 +1
		count++;
		is_initial = false;
	}
	else {
		if (is_terminal) count++; // 중간에 어떤 단어의 terminal일 때
		else if (child_cnt > 1) count++; // child가 2개 이상일 때 (2 조건이 겹치면 하나만 count한다)
	}
	int index = *c - 'a';
	child[index]->find_name(c + 1, count);
}

void do_test(int num)
{
	trie* root = new trie();	
	int count = 0, sum = 0;

	for (int i = 0; i < num; i++) {
		cin >> word[i];
		root->insert(word[i]);
	}
	for (int i = 0; i < num; i++) {
		trie::is_initial = true;
		count = 0;
		root->find_name(word[i], count);	
		sum += count;
	}
	cout << fixed;
	cout.precision(2);
	cout << (double)sum / num << "\n";
	delete root;
}

int main()
{
	FAST;

	int N;
	while (cin >> N) {
		do_test(N);
	}
}