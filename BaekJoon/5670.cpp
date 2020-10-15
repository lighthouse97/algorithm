// 5670.cpp
// �޴��� ����
// Trie(Ʈ����)�� ����ϴ� �����ε�, �ϴ� ���� Ǯ��� ������ ����!
// Trie ���� ����� ����, ������ �ܾ� ��� �Է� ��
// ������ �ܾ� ���ʷ� �˻���, ó�������� �� +1, child�� 2�� �̻� ���� �� +1, �߰��� termnal�϶� +1
// �� ��Ģ���� �� �ܾ�� counting�ؼ� ���ϸ� ��� �ܾ� �Է� �� ��ư�� ������ �ϴ� �� Ƚ���� ���´�.
// ���� ����� �� �������ؼ� ���� ��ü��(����� ����) ���� �Ϸ簡 ���� �ɷȴ�.
// ������� ������� ���� ICPC�� ä���� ������ ���ؼ� �ϳ��ϳ� ������ ���鼭 ���׸� ã�Ҵ�!!!
// ICPC > Regionals > Latin America > Latin America Regional Contests 2012 C��
// ���ѽð� 1�� �� 384ms(21,924KB)�� �ҿ�Ǿ���.
// ������� 84/581�� ���� 14.45%�� rank�Ǿ���.

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
			child.push_back(trie(*it, (alphabet != NULL ? count : 1)));	// alphabet�� NULL �̸� root �̴�.
			if(alphabet != NULL && (child.size() > 1 || is_terminal)) update_count(); // �̹� �տ��� ���� �ܾ �߰��� �ٿ��� ī��Ʈ�Ѵ�.
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
		if (count >= a.count) { // child count�� �̹� update�� ���� update���� �ʴ´�.
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