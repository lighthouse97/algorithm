// 2629.cpp
// ��������
// Olympiad > �ѱ������ø��ǾƵ� > KOI 2001 > �ʵ�� 2��
// ���� ���α׷��� ���� �����̴�.
// ������ ��������� Ǫ�� ����� �����ϰ� Ǭ�ٰ� �ߴµ�, �ʵ��л� ���� �����ӿ���
// �ұ��ϰ� ���� �ȿͼ� ���� ���� �������� ������.
// ����ü ���� �� �� �ִ� ������ ��ü �����ϱ�???
// ������ ������ �� �� ��Ҵ�. �ܿ� ���� ��� ������ ���� �ð��ʰ�(TLE)�� ��� �߻��Ͽ���.
// �ᱹ PS�� ���� ����� 100% �߸� ���� ���̴�!
// ���� ��� �߰� 2, 3�� ���� ��� ���� 2�� �翬�� ���������ϴ�. ���� 3�� �翬�� ���������ϴ�.
// 2 + 3 = 5�� ���� 5�� ���������ϴ�.
// �׸��� 2 - 3 �Ǵ� 3 - 2�� ���밪�� 1�� ���� �����ϴ�.(1�� ����/������ ���⸸ �ٸ� �� +1, -1 �ᱹ ����)
// �̿ܿ��� ���� ������ ������ ����.
// �� 1, 2, 3, 5 ������ ���� �����ϰ� ���� 4 ���� ������ ������ ���� �Ұ����ϴ�.
// �̿� �����ؼ� DP[i][w]�� ���� �� i���� ó���� �� ���� w������ ���� ���ζ��,
// DP[i][w]�� false�� w�� ���� �Ұ����� ���� ���԰� �ȴ�.
// i�� N���� ��� Ž���ϸ� ���� ����, ���� �Ұ����� ���� ���Ե��� ��� ������.
// M[w]�� ������ �迭�� ����� DP[i][w]ó���� �� ���� ó���ϸ� �� �� ���ϴ�.
// �ҽ��� ���� ���� ���ذ� �ȴ�.
// ���ѽð� 1�� �� 0ms(2,156KB)�� �ҿ�Ǿ���.
// ������� 483/1522�� ���� 31.73%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int N; // ���� ����
vector<int> CHU; // ���� �迭
vector<vector<bool>> DP; // DP[i][w]���� ���� �����Ѱ�?
vector<bool> CHECK; // CHECK[w]�� w���� ���������� ���� �ΰ�?

void dfs(int i, int w)
{
	if (i > N) return;
	if (DP[i][w]) return;
	DP[i][w] = true;
	CHECK[w] = true;

	dfs(i + 1, w + CHU[i + 1]); // ���� ��(i + 1)�� ���ϴ� ���
	dfs(i + 1, abs(w - CHU[i + 1])); // ���� ��(i + 1)�� ���� ���
	dfs(i + 1, w); // ���� ��(i + 1)�� ���� �ʴ� ���
}

int main()
{
	FAST;

	cin >> N;
	CHU.resize(N + 2, 0);
	int sum = 0;
	for (int i = 1; i < N + 1; i++) {
		cin >> CHU[i];
		sum += CHU[i];
	}

	DP.resize(N + 1, vector<bool>(sum + 1, false));
	CHECK.resize(sum + 1, false);

	dfs(0, 0);
	int BN, B;
	bool result;
	cin >> BN;
	for (int i = 0; i < BN; i++) {
		result = false;
		cin >> B;
		if (B <= sum && CHECK[B]) result = true;
		cout << (result ? "Y" : "N") << " ";
	}
	cout << "\n";
}