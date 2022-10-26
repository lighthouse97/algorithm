// 10986.cpp
// ������ ��
// �� �ɷ����δ� ����� �����̴�.
// �׳� Ǯ���ٰ��� TLE�� ���� �� ���� Ǯ�̸� ���� ������
// ��μ� ���ظ� �ߴ�.
// �⺻������ ������ ����.
// 1) 1����(1���� ����) i������ �������� pSum[i]��� �� ��, A + 1 ���� B ����
// �������� pSum[B] - pSum[A]�� �ȴ�. 2) �� ���� �������� M���� �������� ����
// �������� 0�� �ȴٴ� ���� (pSum[B] - pSum[A]) % M = 0, �� pSum[B] % M =
// pSum[A] % M �̴�. �� �κ��� �ٽ��̴�. 3) ���� ��� �����յ鿡 ���� ��������
// ���� �͵鳢�� ������.(���� ���� ������ ����) �������� ���� ���� 2�� �̻��̸�
// ���� 2���� �������� ������ �̵��� �����տ� ���� �������� 0�� �͵��̴�. 4)
// ���� ��� �������� 2�ΰ��� 3���� ���� ��, �� 3���� ���� ��� �����յ���
// ���̰� �� 3������ 2���� ��� ������ ����� �� ������ 3C2=3�� �ǰ� �� 3����
// � ���� ������ ������ � �������� �������� 0�� �Ǵ� ������ �ȴ�.
// 9,840KB, 140ms �ҿ�Ǿ���.

#include "pch.h"
#include <iostream>
//#include <sstream>
//#include <string>
//#include <cstring> // strlen
//#include <cctype> // isdigit
#include <vector>
//#include <list>
//#include <algorithm> // sort
//#include <unordered_map>
//#include <utility> // pair, make_pair()
//#include <set>
//#include <unordered_set>
//#include <cmath> // sqrt
#define FAST ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);

using namespace std;

int main() {
   FAST;

   int N, M;
   vector<long long> pSum;
   vector<int> remainder;

   cin >> N >> M;
   pSum.resize(N + 1, 0);
   remainder.resize(M, 0);

   int num;
   long long count = 0;
   for (int i = 1; i < N + 1; i++) {
      cin >> num;
      pSum[i] += (pSum[i - 1] + num);
      remainder[pSum[i] % M]++;
   }

   count += remainder[0];
   for (int i = 0; i < M; i++) {
      if (remainder[i] >= 2)
         count += 1LL * remainder[i] * (remainder[i] - 1) / 2; // _cntC_2�� ���Ѵ�.
   }
   cout << count << '\n';
}