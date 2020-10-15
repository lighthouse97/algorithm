// 1504.cpp
// Ư���� �ִ� ���
// ���ͽ�Ʈ�� �˰����� ����Ѵ�.
// �ִ� ��ο� Ư�� ��θ� ����϶��  ������ �ٴ´�.
/// �Ʒ��� ���� Ǯ�� Ǯ����� Ǯ������ �޸� �ʰ��� �߻��Ѵ�. �ٸ� ����� ã�ƾ� �ϴµ�
/// ���ͽ�Ʈ�� ������ �θ��� �ȴ�.
/// �������� ��ư� �����ߴ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min, find
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
#include <queue> // queue, priority_queue

using namespace std;

int N, E, A, B;

struct vertex {
	int name;
	int value;
	vector<int> path;
	vertex() {}
	vertex(int n, int v, vector<int> p) : name(n), value(v), path(p) {}
	bool check_path();
	bool isCyclic(int n);
};

bool vertex::check_path()
{
	int size = path.size();
	if (size < 2) return false;
	if (find(path.begin(), path.end(), A) == path.end() || find(path.begin(), path.end(), B) == path.end())
		return false;

	return true;
}

bool vertex::isCyclic(int n)
{
	if (find(path.begin(), path.end(), n) == path.end()) return false;
	return true;
}

struct compare {
	bool operator() (const vertex& l, const vertex& r) const
	{
		return (l.value > r.value); // greater than, ��������
	}
};

vector<vector<vertex>> graph; // ���� �Է�
priority_queue<vertex, vector<vertex>, compare> mypq; // �湮�� ������ ���� �켱���� ť
priority_queue<vertex, vector<vertex>, compare> result; // ����� ������ �켱���� ť

void dijksta(int start)
{
	int distance;
	vertex cur, tmp;
	tmp = vertex(start, 0, { start });
	mypq.push(tmp);
	while (!mypq.empty()) {
		cur = mypq.top();
		mypq.pop();
		if (cur.name == N) { 
			if(cur.check_path())// ���� ���� ���� �� ���� A, B�� ���������� üũ�Ѵ�.
				result.push(cur);
			continue;
		}
		for (vertex i : graph[cur.name]) {
			if (cur.isCyclic(i.name) == false) {
				distance = cur.value + i.value;
				tmp = vertex(i.name, distance, cur.path);
				tmp.path.push_back(i.name);
				mypq.push(tmp);
			}
		}		
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int from, to, val;
	vector<int> t;
	cin >> N >> E;
	graph.resize(N + 1);

	for (int i = 0; i < E; i++) {
		cin >> from >> to >> val;
		graph[from].push_back(vertex(to, val, t));
		graph[to].push_back(vertex(from, val, t)); // �����
	}
	cin >> A >> B;
	dijksta(1);
	if (result.empty()) cout << -1 << endl;
	else cout << result.top().value << "\n";
}