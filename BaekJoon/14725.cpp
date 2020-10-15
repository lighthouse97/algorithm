// 14725.cpp
// ���̱�
// Ʈ���̿� ���� ���� ��� ������� �ϴµ� ���� Ʈ���̴� ���� �𸣰�
// �Ϲ����� Ʈ�������� KMP ���� �˻��� �̿��ϸ� �� �� ����.
// ����� std::sort�� ��Ʈ�� ���Ϳ��� ������ �Ǿ���!!!
// �ڷ� �����ؼ� �ƿ� trie�� ������ ���ȴ�!
// University > �泲���б� > �����ϴ� ���α׷��� ��ȸ J��
// ���ѽð� 1�� �� 4ms(2400KB)�� �ҿ�Ǿ���.
// ������� 47/101�� ���� 46.53%�� rank�Ǿ���.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

class trie
{
public:
	trie() { }
	trie(string name) : name(name) {}
	~trie() {
		next.clear();
	}
	void insert(vector<string>::iterator key);
	void traverse() { traverse(0); }
	bool operator < (trie& comp) {
		return (name < comp.name);
	}
private:
	string name;
	vector<trie> next;
	int find_name(const string& str);
	void traverse(int level);
};

void trie::insert(vector<string>::iterator key)
{
	int index;
	if (*key == "") return;
	index = find_name(*key);
	if (index == -1) { // next �迭���� ������ ���� �߰��ϰ� ���� ��Ʈ�� insert
		next.push_back(trie(*key));
		next.back().insert(key + 1);
	}
	else
		next[index].insert(key + 1); // ������ �ױ⿡�� ���� ��Ʈ�� insert
}

int trie::find_name(const string& str)
{
	for (int i = 0; i < (int)next.size(); i++) {
		if (str == next[i].name) return i;
	}
	return -1;
}

void trie::traverse(int level)
{
	int cnt = (level - 1)*2;
	if (level) {
		for (int i = 0; i < cnt; i++) cout << "-";
		cout << name << "\n";
	}
	if (next.size() > 0) {
		sort(next.begin(), next.end()); // next�� trie ��ü�� �������� �������� ����
		for (trie t : next) {
			t.traverse(level + 1);
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	string food;
	vector<string> floor;
	trie cave;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> K;
		for (int j = 0; j < K; j++) {
			cin >> food;
			floor.push_back(food);
		}
		floor.push_back(""); // �� ���� ������ ǥ��
		cave.insert(floor.begin()); // trie�� ����
		floor.clear();
	}
	cave.traverse();
}
