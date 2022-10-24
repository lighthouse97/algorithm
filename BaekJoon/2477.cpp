// 2477.cpp
// 참외밭
// 기하 응용 문제이다.
// Olympiad > 한국정보올림피아드 > 한국정보올림피아드시․도지역본선 > 지역본선 2010 > 초등부 3번
// Olympiad > 한국정보올림피아드 > 한국정보올림피아드시․도지역본선 > 지역본선 2010 > 중등부 2번
// 2,020KB,	0ms 소요되었다.

#include "pch.h"
#include <iostream>
//#include <sstream>
//#include <string>
//#include <cstring> // strlen
//#include <cctype> // isdigit
//#include <vector>
//#include <list>
//#include <algorithm> // sort
//#include <unordered_map>
//#include <utility> // pair, make_pair()
//#include <set>
//#include <unordered_set>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	int K;
	int curr_dir = 0, curr_len = 0; // 현재 방향, 길이
	int prev_dir = 0, prev_len = 0;
	int first_dir = 0, first_len = 0;
	int max_hor = 0, max_ver = 0; // 가로 최대 길이, 세로 최대 길이
	int minus_area = 0; // 빼야 할 사각 면적

	cin >> K;
	for (int i = 0; i < 6; i++) {
		cin >> curr_dir >> curr_len;

		if (i == 0) {
			first_dir = curr_dir; // 최초의 방향, 길이 저장
			first_len = curr_len;
		}

		if (curr_dir == 1) { // 오른쪽
			if (curr_len > max_hor) max_hor = curr_len;
			if (prev_dir && prev_dir != 3) minus_area = curr_len * prev_len; // 아래 -> 오른쪽만 허용
		}
		else if (curr_dir == 2) { // 왼쪽
			if (curr_len > max_hor) max_hor = curr_len;
			if (prev_dir && prev_dir != 4) minus_area = curr_len * prev_len; // 위 -> 왼쪽만 허용
		}
		else if (curr_dir == 3) { // 아래
			if (curr_len > max_ver) max_ver = curr_len;
			if (prev_dir && prev_dir != 2) minus_area = curr_len * prev_len; // 왼쪽 -> 아래만 허용
		}
		else if (curr_dir == 4) { // 위
			if (curr_len > max_ver) max_ver = curr_len;
			if (prev_dir && prev_dir != 1) minus_area = curr_len * prev_len; // 오른쪽 -> 위만 허용
		}
		else
			;
		prev_dir = curr_dir;
		prev_len = curr_len;
	}

	if (minus_area == 0) { // 빼야할 사각형 면적이 0일 경우 최초 입력으로 다시 계산
		if (prev_dir == 1 && first_dir != 4) minus_area = first_len * prev_len;
		else if (prev_dir == 2 && first_dir != 3) minus_area = first_len * prev_len;
		else if (prev_dir == 3 && first_dir != 1) minus_area = first_len * prev_len;
		else if (prev_dir == 4 && first_dir != 2) minus_area = first_len * prev_len;
	}

	cout << K * (max_hor * max_ver - minus_area) << '\n';
}