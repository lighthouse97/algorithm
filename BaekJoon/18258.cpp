// 18258.cpp
// ť(queue) 2
// ť�� �⺻ ������ �̿��� �����̴�.
// ť�� ���� �������� �ʰ� STL�� queue�� �̿��Ͽ���.
// 10845(ť)�� ������ �����̴�. �� �������� �־����� ����� ���� 2,000,000����
// 10845(ť) 10,000�� ��� 200�� �� ����.
// 10945�� ������ ������� STL�� queue�� ����ؼ� Ǯ� �ð����� Ǯ����� Ǯ����.
// �ٸ� �� �� ���� �����ϰ� ������ queue�� �迭�� �̿��ؼ� ��ü������ �����ؾ� �Ѵ�.
// ���ѽð� 1�� �� 380ms(8,380KB)�� �ҿ�Ǿ���.
// ������� 61/393�� ���� 15.52%�� rank�Ǿ���.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
#include <string> // getline, string, stoi
//#include <utility> // pair
//#include <map> // map
//#include <stack>
#include <queue>

using namespace std;

queue <int> myq;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, arg;
	string cmd;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> cmd;
		if (cmd == "push") {
			cin >> arg;
			myq.push(arg);
		}
		else if (cmd == "pop") {
			if (!myq.empty()) {
				cout << myq.front() << "\n";
				myq.pop();
			}
			else
				cout << -1 << "\n";
		}
		else if (cmd == "size") cout << myq.size() << "\n";
		else if (cmd == "empty") cout << (myq.empty() ? 1 : 0) << "\n";
		else if (cmd == "front") {
			if (!myq.empty()) cout << myq.front() << "\n";
			else cout << -1 << "\n";
		}
		else if (cmd == "back") {
			if (!myq.empty()) cout << myq.back() << "\n";
			else cout << -1 << "\n";
		}
	}
}