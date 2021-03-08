// 2339.cpp
// ���� �ڸ���
// ���� �������� Ǫ�� ������� �Ѵ�.
// �׷��� ������ ������ ���� ���ؼ� �ణ�� ��Ʈ�� ����� ���Ҵ�.
// �� ������ ������ �ʹ��� ������� ������ �� ���� �ɷȴµ�, �ϴ� Ǯ���� �ʹ��� ����� ����!
// 1) ���� N * N ��ü ��ǥ�� ���� �Է¹޴´�.
// 2) �Է¹��� �� ���� ���� �ٲپ �������� �ڸ� ���� ���� �����͸� �ϳ� �� �����.
// 3) �ڸ����� ���� ���� ��ü���� �� �ڸ� �ʿ���� ���Ǹ����ϴ���, �������� �ʴ��� �Ǵ��Ѵ�.
// 4) �ڸ� �ʿ䰡 ������ ������ �Ҽ����� �ִ� row�� �߽����� �ڸ���. �ڸ� �� �ִ� row�� ������
//    ���� �� �����Ƿ� ���ʴ�� ��� �� ����.
// 5) 4)���� �ڸ��� row�� ������ ������ �ȵȴ�.
// 6) �ڸ� ������ ������ ���¸� �Ǵ��Ѵ�. 
// 7) ������ �����ϸ� 1, �� �߶�� �Ǹ� �� �ڸ� ���� ������ �����ϴ� ����� ���� ���Ϲ޴´�.
//    �� �ڸ� �� �����̸� ����, �����̸� �������� ������ �ٲ㰡�鼭 �߶�� �Ѵ�. �� �ڸ��� ����
//    ���ȣ��� �����Ѵ�.
// 8) ���� �ڸ� �� ���� �� �Ѱ��� ������ �������� ������ ���� ������ �Ѿ��.
// 9) �ڸ� ���� ������ ���� ���� ����� ���� ���Ͽ� �̸� sum�� �����Ѵ�.(�ڸ� �� �ִ� ��� row�� ���� ��ġ�Ƿ� �����ϴ� ���̴�)
//    ���� ������ 2������ ������ �ٸ� ������ 3������ ������ 2 * 3 = 6 ������ ������ �̸� �����Ѵ�.
// 10) Ư�� row�� ���� �߶������ ���� �ڸ� �� �ִ� row�� �߶� ����.
// 11) �ڸ� �� �ִ� ��� row�� ���ؼ� ���� ����� ������ �� loop���� ���Ѵ�.(9�� �����Ѵٴ� �Ͱ� ���� �ǹ��̴�)
// 12) ���������� ������ ���� cut�Լ�(������ �ڸ��� �Լ�)�� ��������� �����Ѵ�.
// 13) ���� �������� �߶� ����� ��������, �������ε� �߶� ����� �ѹ� �� ����Ѵ�.
// 14) 13)�� �� ����� ���ؼ� ���� ��� ����� ���� ����Ѵ�. ���� ���� ���� 0�̸� -1�� ����Ѵ�.
// ���ѽð� 2�� �� 0ms(2,020KB)�� �ҿ�Ǿ���.
// ������� 166/273�� ���� 60.80%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
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

struct axis {
	int r, c;
	axis() : r(0), c(0) {}
	axis(int r, int c) : r(r), c(c) {}
};

int g_stone_h[21][21] = { {0, }, }; // �������� �ڸ��� ���� �迭
int g_stone_v[21][21] = { {0, }, }; // �������� �ڸ��� ���� �迭
int g_N = 0, g_cnt = 0;

int decide(const axis& s, const axis& e, int type) // ret : 0(����), 1(����), 2(�ڸ���)
{
	int cnt1 = 0, cnt2 = 0;
	int(*stone)[21] = (type == 0) ? g_stone_h : g_stone_v;
	for (int i = s.r; i <= e.r; i++) {
		for (int j = s.c; j <= e.c; j++) {
			if (stone[i][j] == 1) cnt1++; // �Ҽ��� count
			else if (stone[i][j] == 2) cnt2++; // ���� count
		}
	}
	if (cnt2 == 1 && cnt1 == 0) return 1; // ����
	else if (cnt2 >= 2 && cnt1 >= 1) return 2; // �� �ڸ���
	else return 0; // ����
}

int cut(const axis& s, const axis& e, int type) // type : 0(����), 1(����)
{
	int d1, d2, cnt1, cnt2, sum = 0;
	int(*stone)[21] = (type == 0) ? g_stone_h : g_stone_v;
	for (int i = s.r; i <= e.r; i++) {
		bool imp = false;
		for (int j = s.c; j <= e.c; j++) {
			if (stone[i][j] == 1) { imp = true; } // �Ҽ��� �߰�
			else if (stone[i][j] == 2) { imp = false; break; } // ���������� ���� row�� �Ѿ
		}
		if (imp && i > s.r && i < e.r) { // row�� ���� �ڸ��� �ʴ´�. i row���� �ڸ���
			d1 = decide(s, axis(i - 1, e.c), type);
			d2 = decide(axis(i + 1, s.c), e, type);
			if (d1 > 0 && d2 > 0) { // �ڸ� �� ���
				cnt1 = (d1 == 1) ? 1 : cut(axis(s.c, s.r), axis(e.c, i - 1), type ^ 1); // �ڸ��� ������ �ٲ�� ��, ���� �ٲ��.
				cnt2 = (d2 == 1) ? 1 : cut(axis(s.c, i + 1), axis(e.c, e.r), type ^ 1);
				sum += (cnt1 * cnt2);
			}
		}
	}
	return sum;
}

int main()
{
	FAST;

	int result;
	cin >> g_N;
	for (int i = 1; i < g_N + 1; i++) {
		for (int j = 1; j < g_N + 1; j++) {
			cin >> g_stone_h[i][j]; // 0 : ��ĭ, 1 : �Ҽ���, 2 : ����
			g_stone_v[j][i] = g_stone_h[i][j];
		}
	}

	result = decide(axis(1, 1), axis(g_N, g_N), 0);
	if (result == 0 || result == 1) { // �ڸ� �ʿ� ���� ���� �Ǵ� ������ ���
		cout << (result ? 1 : -1) << "\n";
		return 0;
	}
	else { // ������ �ڸ��� ���
		int cnt1, cnt2, answer;
		cnt1 = cut(axis(1, 1), axis(g_N, g_N), 0); // �����ڸ���� ����
		cnt2 = cut(axis(1, 1), axis(g_N, g_N), 1); // ���� �ڸ���� ����
		answer = cnt1 + cnt2;
		cout << (answer > 0 ? answer : -1) << "\n";
	}
}