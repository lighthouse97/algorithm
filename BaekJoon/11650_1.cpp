// 11650_1.cpp
// ��ǥ����
// x, y ��ǥ�� ��� ���� �� ���� ����.
// 11650�� qsort�� ������� �ʰ� �̹����� std::vector�� sort�� ����Ͽ���.
// qsort�� ����� ���(68ms),  -> std:sort�� ����� ���(64ms) ,4ms ���� �����ȴ�.
// ����(����ӵ�) ����
// 1. make_fair�� ���� �ʰ� coors �迭�� ����� �ٷ� �Ҵ�
// 2. scanf, printf�� ���� �ʰ� 'ios_base::sync_with_stdio(false)' �����Ͽ��� cin, cout ���
// �̷��� �����ϸ� 64ms -> 52ms, 12ms �����ȴ�. (��쿡 ���� 64ms -> 48ms, 16ms �����ȴ�.)

#include "pch.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
//#include <cstdio>
#include <utility> // pair
#include <vector> // vector
#include <algorithm> // sort

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	int N;	
	cin >> N;
	vector<pair<int, int>> coors(N);
	for (int i = 0; i < N; i++) {
		cin >> coors[i].first >> coors[i].second;
	}
	sort(coors.begin(), coors.end());
	for (int i = 0; i < N; i++)
	   cout << coors[i].first << " " << coors[i].second << "\n";
}