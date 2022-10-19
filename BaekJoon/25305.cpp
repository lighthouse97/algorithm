// 25305.cpp
// 커트라인
// University > 연세대학교 미래캠퍼스 > 2022 연세대학교 미래캠퍼스 슬기로운 코딩생활 B번

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