// 11003.cpp
// �ּڰ� ã��
// �з��� ���� ��ȹ�� ����ȭ �׸� �־� ������ȹ������ Ǯ ���� ������
// �������� ���� ��� deque�� ����ؼ��� Ǯ �� �ִ�.
// �ϴ� deque�� ����ؼ� Ǯ��� ������ dynamic programming���� Ǯ���.
// deque�� Ǯ��� i �������� �ּҰ��� A(i-L+1), A(i-L)~A(i)���� ���� ���� ���ϰ�
// i + 1�������� �ּҰ��� A(i-L)~A(i)�� A(i+1)���� ���� ���� ���Ѵ�.
// �̷��� �����ν� L���� �������� �ּҰ� ���ϴ� ������ �������� ���� �� �ִ�.
// �ϴ� deque�� Ǯ�� �ð��ʰ��� ������, priority_queue�� �Ἥ �ܿ� Ǯ����.
// ���ѽð� 2.4�� �� 1,764ms(119,90KB)�� �ҿ�Ǿ���.
// ������� 512/1600�� ���� 32.00%�� rank�Ǿ���.

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
#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
//#include <deque>
#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef pair<int, int> pii;

int main()
{
	FAST;
	
	int N, L;
	vector<int> answer;
	priority_queue<pii, vector<pii>, greater<pii>> mypq;

	cin >> N >> L;
	answer.resize(N + 1, 0);

	int a;
	for (int i = 1; i < N + 1; i++) {
		cin >> a;
		mypq.push({ a, i });
		if (i - L <= 0) answer[i] = mypq.top().first;
		else {
			while (mypq.top().second <= i - L) mypq.pop();
			answer[i] = mypq.top().first;
		}
	}

	for (int i = 1; i < N + 1; i++)
		cout << answer[i] << " ";
	cout << "\n";
}