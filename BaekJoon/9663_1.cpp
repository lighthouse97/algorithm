// 9663_1.cpp
// N-Queen
// �� �ڷḦ ã�ƺ��� backtracking����� ����ϴ� ���� �´µ�,
// ���� IsPromising() �Լ��� �� �� ������ ȿ�������� ���� �� �ִ� �����
// �־���. for loop�� ���� level�� ������ �ϳ��� ã���� ������ ����, �밢���� ����ϴ� �ͺ���
// �� level�� ���� �ϳ� ���� ������ |(������), /(�밢��1), \(�밢��2)�� �ش��ϴ� ������
// �Ѳ����� marking�ؼ� ���� level�� �� ���� ������ ���� ���� ��ġ�� ���ؼ� marking�� ������ �ȴ�.
// ������ ��ġ�� �� level�� �ϳ��� ���� ��� ������ ���򼱿� ���� check�� �� �ʿ䰡 ����.
// ������, �밢��1, �밢��2 ������ �ش��ϴ� 3���� ���� �ʿ��ϸ�,
// |(������)�� �ش��ϴ� �迭�� �� column�� index�� true,false�� marking �ϸ� �ǰ�,
// /(�밢��1)�� �ش��ϴ� �迭�� row�� i, column�� j�� ���� ��, i + j�� index�� true/false�� marking�Ѵ�.
// \(�밢��2)�� �ش��ϴ� �迭�� row�� i, column�� j�� ���� ��, i - j + N + 1 �� index�� true/false�� marking�Ѵ�.
// \(�밢��2)�� ������ �� �� sample�� �̾Ƽ� ���纸�� �׷��� ���´�.
// �̷��� �� �ϳ� ���� ������ �� �� ���� ������ �̸� �ѹ��� ǥ���� �θ� ���� ������� �ξ� �� ���� ������ ���� ã�� �� �ִ�.
// �׸��� backtracking���� �� �ϳ� ����鼭 level�� �ö� �� ������ ����� ���� ǥ���� ���� �ٽ� �����־�� �Ѵ�.
// https://rebas.kr/761 �����Ͽ���.
// Ȯ���� �ð��� �پ�����.
// 4,096ms(2,016KB) -> 2,112ms(2,016KB)
// ���ѽð� 10�� �� 2,112ms(2,016KB)�� �ҿ�Ǿ���.
// ������� 2788/10706�� ���� 26.04%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int N = 0;
int cnt = 0;
vector<bool> A; // ������(|)
vector<bool> B; // �밢��1(/)
vector<bool> C; // �밢��2(\)

void BackTracking(int level)
{
	if (level > N) {
		cnt++;
		return;
	}
	else {
		for (int i = 1; i < N + 1; i++) {
			if (A[i] || B[level + i] || C[level - i + N + 1]) continue; // |, /, \ üũ
			else {
				A[i] = B[level + i] = C[level - i + N + 1] = true; // |, /, \ ǥ��
				BackTracking(level + 1);
				A[i] = B[level + i] = C[level - i + N + 1] = false; // |, /, \ ����
			}			
		}
	}
}

int main() {

	FAST;

	cin >> N;
	A.resize(N + 1, false);
	B.resize(N + N + 1, false);
	C.resize(N + N + 1, false);
	BackTracking(1);
	cout << cnt << "\n";
}