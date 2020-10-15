// 12015.cpp
// ���� �� �����ϴ� �κ� ���� 2
// ������ ũ�Ⱑ 1,000,000�̱� ������ ���� DP ������δ� 2�� for���� ����
// ��� �ð��� ���� �ɷ� �ð� �ʰ��� �߻��Ѵ�.(O(N^2))
// �� ���� ���� �� �����ϴ� �κ� ������ ����� �����̱�� �ϳ� Ǯ�̴�
// DP�� �ƴ� �ٸ� ����� �̿��ؾ� �Ѵ�.
// �̺� Ž���� �ϴ� std::lower_bound()�� �̿����Ѵ�.(O(NlogN))
// �̺� Ž���� std::binary_search(), std::lower_bound(), std::upper_bound()�� �ִ�.
// �̺� Ž���� �̹� ���ĵ� ���� ���� Ž���ϴ� ������� ������ ���ݿ��� �� �´�.
// LIS(Longest Increasing Sequence)������ DP�� �̿��� ���� for���� �̿��ϴ� �����
// lower_bound�� �̿��ϴ� ����� �ִµ� �� ���� lower_bound�� �̿��ؾ� �Ѵ�.
// example : 10 20 30 40 1 2 3
// 10
// 10 20
// 10 20 30
// 10 20 30 40
// 1  20 30 40 => 1���� ���ų� ũ�鼭 ���� ������ index�� ã�´�.
// 1  2  30 40
// 1  2  3  40 ==> vector�� size�� 4�̴�.
// LIS�� ũ��� �������� LIS�� �ش��ϴ� ��Ȯ�� ������ �� �� ����.
// �������� �˷��� �ٸ� ����� �� ã�ƾ� �Ѵ�.

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm> // lower_bound

using namespace std;

int AR[1000001] = { 0, };
vector<int> DP;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> AR[i];
		if (i == 1) DP.push_back(AR[1]);
		else {
			if (DP.back() < AR[i]) DP.push_back(AR[i]);
			else 
				DP[lower_bound(DP.begin(), DP.end(), AR[i]) - DP.begin()] = AR[i];
		}
	}
	cout << DP.size() << "\n";
}