// 5670.cpp
// 휴대폰 자판
// Trie(트라이)를 사용하는 문제인데, 일단 먼저 풀어보고 정리해 보자!
// Trie 구조 만들어 놓고, 사전의 단어 모두 입력 후
// 사전의 단어 차례로 검색시, 처음시작할 때 +1, child가 2개 이상 있을 때 +1, 중간에 termnal일때 +1
// 이 원칙으로 각 단어마다 counting해서 더하면 모든 단어 입력 시 버튼을 눌러야 하는 총 횟수가 나온다.
// 접근 방법이 좀 지저분해서 구현 자체에(디버깅 포함) 거의 하루가 꼬박 걸렸다.
// 디버깅이 어려워서 직접 ICPC의 채점용 샘플을 구해서 하나하나 대입해 보면서 버그를 찾았다!!!
// ICPC > Regionals > Latin America > Latin America Regional Contests 2012 C번
// 제한시간 1초 중 384ms(21,924KB)가 소요되었다.
// 맞은사람 84/581로 상위 14.45%에 rank되었다.

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
	trie() : alphabet(0), is_terminal(false), count(0) { }
	trie(const char& a, int cnt) : alphabet(a), is_terminal(false), count(cnt) {}
	~trie() {
		child.clear();
	}
	void insert(string::iterator it, string::iterator end);
	int find_name(string::iterator it, string::iterator end);
	void update_count();

private:
	char alphabet;
	vector<trie> child;
	bool is_terminal;
	int count;
	int find_alpha(const char& a);
};

void trie::insert(string::iterator it, string::iterator end)
{	
	if (it == end) {
		is_terminal = true;		
		if (child.size() > 0)			
			update_count();
	}
	else {
		int index = find_alpha(*it);
		if (index > -1) child[index].insert(it + 1, end);
		else {			
			child.push_back(trie(*it, (alphabet != NULL ? count : 1)));	// alphabet이 NULL 이면 root 이다.
			if(alphabet != NULL && (child.size() > 1 || is_terminal)) update_count(); // 이미 앞에서 끝난 단어에 추가로 붙여도 카운트한다.
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

void trie::update_count()
{
	for (trie& a : child) {
		if (count >= a.count) { // child count가 이미 update된 것은 update하지 않는다.
			a.count++; 
			a.update_count();
		}
	}
}

int trie::find_name(string::iterator it, string::iterator end)
{	
	if (it == end) {
		if (is_terminal) return count;
		else return 0;
	}	

	int index = find_alpha(*it);
	if (index < 0)
		return 0;
	else {
		return child[index].find_name(it + 1, end);
	}
}

trie* root;

void do_test(int num)
{
	vector<string> words;
	int sum = 0;	
	root = new trie();
	words.resize(num);

	// insert words
	for (int i = 0; i < num; i++) {
		cin >> words[i];
		root->insert(words[i].begin(), words[i].end());
	}
	// calculate input count
	for (string s : words) {
		sum += root->find_name(s.begin(), s.end());		
	}	
	cout << fixed;
	cout.precision(2);
	cout << (double)sum / num << "\n";
}

int main()
{
	FAST;

	int N;
	while(cin >> N) {
		do_test(N);
		delete root;
	}
}