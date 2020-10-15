// 1021.cpp
// ��(dequeue)
// ���� �⺻ ������ �̿��� �����̴�.
// ���� ���� �������� �ʰ� STL�� deque�� �̿��Ͽ���.
// �������� ���ų� ���������� ���ų��� �Ǵ��� index, deque_size-index
// �� ���� ���� ���� ���� ������ �����ϱ�� �Ѵ�. 

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // getline, string, stoi
//#include <utility> // pair
//#include <map> // map
//#include <stack>
#include <deque>

using namespace std;

deque <int> mydq;
 
int rotate(int num)
{
	int rcnt = 0, lindex, rindex;
	for (unsigned int i = 0; i < mydq.size(); i++) {
		if (num == mydq[i]) {
			lindex = i;
			rindex = mydq.size() - i - 1;
			break;
		}
	}
	while (true) {
		if (num == mydq.front()) {
			mydq.pop_front();
			break;
		}
		else {
			if (lindex <= rindex) { // �������� ��ȯ
				mydq.push_back(mydq.front());
				mydq.pop_front();
				rcnt++;
			}
			else { // ���������� ��ȯ
				mydq.push_front(mydq.back());
				mydq.pop_back();
				rcnt++;
			}
		}
	}
	return rcnt;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M, num, sum = 0;
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		mydq.push_back(i);
	}
	for (int i = 0; i < M; i++) {
		cin >> num;
		sum += rotate(num);
	}
	cout << sum << "\n";
}