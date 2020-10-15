// 16229.cpp
// �ݺ� ����
// Z �˰��� ���빮���̴�.
// Contest > ������� > ��2ȸ ������� Day 2 F��
// �ϴ� ���������� �� Ǯ��� ��������
// ���ڿ� ������ �ȵǾ� Ǯ�̸� ���� ����(�Ϸ�����) �����ϰ��� �˰� �Ǿ���.
// 1) �־��� string�� ���� Z[]���� ���Ѵ�.
// 2) 1 <= i < N�� ���ؼ� Z[i] > 0 �� �� i���� ���ڿ� ������ prefix ��ġ�ؾ� �ϹǷ�(�׷��� ���Ϲݺ� �� �� �ִ�)
//    i + Z[i] == N (or i + Z[i] >= N) �̾�� �Ѵ�. (�̰� ���Ծ ���� ��̴�!!)
// 3) N���� Z[i]��ŭ �� ���� P�� �ϸ� P�� �ݺ��Ǵ� ������ ���ڼ��� �ȴ�.
// 4) (N + K) / P �� ������ K���� ���� ���ڿ����� ��� �ݺ��� �Ǵ��� �ݺ�Ƚ�� C�� �ȴ�.
// 5) C >=2(�ּ� 2���̻� �ݺ��ؾ� �ϹǷ�...)�̰� P * C >= N(������ C�� �ݺ��� �� P*C�� N ���̴� �Ѿ�� �ؽ�Ʈ ��ü�� �ݺ��ȴ�)
//    �� �� answer = max(answer. P)�� �ȴ�. ������ �����ϴ� P�� ���� ū ��.
// 3)���� prefix ��,�ڰ� ������ ������ N-Z[i]�� �������� �ڸ��ϴ�.
//        prefix ��,�� �� �Ϻΰ� ��ġ�� N-Z[i]�� ������ �յ� prefix���ο��� �������� ��Ÿ����.
//        abababa�� ���� ��� ab�� �յ� prefix ababa�� �������� ��Ÿ���� �� �� �ִ�.
//   0123456
//   abababa
//     abababa
//   ��ġ�� �κ�(2~6)�� ��ġ�Ƿ� ���� ���� ab�� �� prefix ���� ab�� �����Ƿ� �ᱹ ab�� ������ �ȴ�.(���� ���� �����ؼ� �˾Ҵ�)
// ���� N - Z[i]�� �ݺ��Ǵ� ������ ���̰� �ȴ�.
// ���ѽð� 1�� �� 0ms(2,748KB)�� �ҿ�Ǿ���.
// ������� 16/39�� ���� 41.02%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> Z;

void z_algorithm(const string& str)
{
	int R = 0, L = 0;
	int n = (int)str.length();
	for (int i = 1; i < n; i++) {
		if (i > R) {
			L = R = i;
			while (R < n && str[R - L] == str[R]) R++;
			Z[i] = R - L; R--;
		}
		else { // L < i <= R
			int k = i - L; // i'
			if (i + Z[k] - 1 < R) Z[i] = Z[k];
			else {
				L = i;
				while (R < n && str[R - L] == str[R]) R++;
				Z[i] = R - L; R--;
			}
		}
	}
	Z[0] = n;
}

int main()
{
	FAST;
	
	int N, K, answer = 0;
	string str;

	cin >> N >> K;
	cin >> str;
	if (K >= N) {
		cout << N << "\n";
		return 0;
	}
	Z.resize(N, 0);
	z_algorithm(str);	
	int p, c;
	for (int i = 1; i < N; i++) {
		if (Z[i] > 0 && i + Z[i] == N) {
			p = N - Z[i]; // pattern�� ����
			c = (N + K) / p; // pattern�� �ݺ� Ƚ��
			if (c >= 2 && p * c >= N) answer = max(answer, p);
		}
	}
	cout << answer << "\n";
}