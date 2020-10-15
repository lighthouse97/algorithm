// 2809.cpp
// �ƽ�Ű �Ÿ�
// Contest > Croatian Open Competition in Informatics > COCI 2011/2012 > Contest #5 6��
// Suffix Array�� Aho-Corasick �� ������� Ǯ �� �ִµ� ������ Aho-Corasick algorithm�� �̿��Ͽ� Ǯ����.
// �޸� �ʰ��� �߻��ؼ� trie �� ��帶�� 26���� ���ĺ� �迭�� ��� ���� �ʰ� unordered_map���� ��Ҵµ�,
// �׷��� �޸� �ʰ��� �߻��ߴ�. map�� �޸𸮸� ���� �Ա�� �Ѵ�.
// �׷��� ���Ϳ� bitset(bit masking)�� ����ؼ� �޸� ��뷮�� �� �ٿ������ ����.
// bit masking�� ������ �ε����� ���߾� �� �� ������ ã�ư� �� �ֵ��� �Ͽ���.
// ���ڿ� ó������ �˻��ϸ� ������ ���� �ȳ��´�. (�̰� ������ ��ĥ�� ������.)
// �� �ϴ� ����� Ǭ ���� �����Ͽ� ��Ʈ�� ����µ�, ���ڿ� ������ �˻��ؾ� �Ѵ�.
// ���� ���̽� ��찡 ���� ������ �� �������� �Ѵ�. ���� ���̽� ���� ������ ���� �߱⿡ �ð��� ���� �ɷȴ�.
// ����� ���� �ð��� 1�� �̳��� ������ Ǭ ������� ��� Suffix Array�� �̿��ؼ� Ǭ ���̴�.
// ���ѽð� 4�� �� 1,416ms(378,412KB)�� �ҿ�Ǿ���.
// ������� 24/66�� ���� 36.36%�� rank�Ǿ���.

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

	bitset<26> alpha; // ���ĺ� ������� bitmasking(MSB)
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
				// go[i]�� ���ĺ��� �˰�, �� ���ĺ��� dest���� �ִ��� üũ�Ѵ�
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
	int pos, answer = 0; // answer : ��ġ���� �ʴ� ���ڼ�
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
	int index = N - 1; // �Ųٷκ��� Ž���Ѵ�. �̰��� �ٽ��̴�! �տ��� ���� �˻��ϸ� �ð� ���� �� ���̴�!!!
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