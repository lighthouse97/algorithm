// 1992.cpp
// ����Ʈ��
// ��ǥ���� �������� �����̰� ����Լ��� �̿��Ѵ�.
// (1,1)�� ���� (1,1) ~ (N, N)���� ���������� ���Ѵ�.
// ��� ������ (1,1)�� ���� ����ϰ� �����Ѵ�.
// �ٸ� ���� ������ ��, ���� ���ݾ� ������ ��� 4����Ͽ� ������ ���ؼ� ���Ѵ�.(4���� �Լ� ȣ���� �ȴ�.)
// 4�� ���ϱ� ���Ŀ� '(', ')'�� �����ش�.
// �ϴ� �ٸ� ���� �߰ߵǸ� 4�� �񱳿��� �ٽ� ���ϹǷ� ���ݱ����� for loop�� ��� �������´�.(break ���)

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
//#include <deque>

using namespace std;

int arr[65][65] = { {0, }, };

void quad_tree(int r1, int r2, int c1, int c2)
{
	int val = arr[r1][c1];
	int rh, ch, diff = 0;
	for (int i = r1; i <= r2; i++) {
		for (int j = c1; j <= c2; j++) {
			if (arr[i][j] != val) {
				rh = (r1 + r2) / 2;
				ch = (c1 + c2) / 2;
				cout << "(";
				quad_tree(r1, rh, c1, ch); // UP LEFT
				quad_tree(r1, rh, ch + 1, c2); // UP RIGHT
				quad_tree(rh + 1, r2, c1, ch); // DOWN LEFT
				quad_tree(rh + 1, r2, ch + 1, c2); // DOWN RIGHT
				cout << ")";
				diff = 1;
				break;
			}
		}
		if (diff) break;
	}
	if (!diff) cout << val;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	string rdata;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> rdata;
		for (unsigned int j = 0; j < rdata.length(); j++)
			arr[i][j + 1] = rdata[j] - '0';
	}
	quad_tree(1, N, 1, N);
	cout << "\n";
}