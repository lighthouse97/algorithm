// 25305.cpp
// ĿƮ����
// University > �������б� �̷�ķ�۽� > 2022 �������б� �̷�ķ�۽� ����ο� �ڵ���Ȱ B��

#include "pch.h"
#include <iostream>
//#include <sstream>
//#include <string>
#include <vector>
#include <algorithm>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	int N, k;
	vector<int> score;

	cin >> N >> k;
	score.resize(N, 0);
	for (int i = 0; i < N; i++) {
		cin >> score[i];
	}
	sort(score.begin(), score.end(), std::greater<int>());
	cout << score[k - 1] << '\n';
}