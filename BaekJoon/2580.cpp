// 2580.cpp
// 스도쿠
// backtracking 응용 문제이다.
// Olympiad > 한국정보올림피아드 > 한국정보올림피아드시․도지역본선 > 지역본선 2006 > 초등부 5번
// Olympiad > 한국정보올림피아드 > 한국정보올림피아드시․도지역본선 > 지역본선 2006 > 중등부 3번
// 초중학생 문제인데... 이틀을 고민하고도 풀지 못한 나 자신이 부끄럽다!!!
// 기본 concept은 9 * 9 = 81개의 모든 칸을 BackTracking으로 체크한다.
// N-Queen처럼 한 행 단위로 BackTracking하면 절대로 문제를 풀 수가 없다.(여기서 시간을 엄청 많이 잡아 먹었다!!!)
// 왜냐하면 N-Queen은 한 행에 한개만 선택할 수 있지만 수도쿠는 한 행에 여러 개가 선택이 가능하기 때문이다.
// 매 칸마다 BackTracking으로 나가는데 이미 값이 있는 칸은 바로 다음 칸으로 BackTracking 넘어가고,
// 값이 0인 빈칸은 1~9까지 차례로 대입하면서 수평, 수직, 사각형(3*3 사각형) 범위에 같은 것이 있는지 체크한다.
// 만일 채울 수 있는 숫자가 있으면 채우고 바로 다음 칸으로 넘어가고 1~9까지 뭘 넣어도 조건에 걸려서 채울 수 없으면
// 바로 BackTracking으로 이전 칸으로 넘어가서 그기서 다시 다른 숫자를 넣어보고 진행한다.
// 이런 방식을 반복해서 81칸이 모두 채워지면 된다.
// 각 빈칸에 값이 채워질 때마다 수평, 수직, 사각형을 체크하기 위해서 3개의 81개짜리 배열을 만들어
// 수평은 9개의 모든 행에 1~9까지 값에 true, false 체크하고
// 수직은 9개의 모든 열에 1~9까지 값에 true, false 체크하고
// 사각형은 9개의 모든 작은 사각형에 1~9까지 값에 true, false 체크한다.
// 3개의 조건을 모두 체크해서 겹치는 것이 없으면 선택된 값을 입력하고 다른 값 더 넣어볼 필요 없이 바로 loop빠져나오고
// 다음 칸으로 넘어간다. 만일 3 조건 중 하나라도 겹치거나 다음 칸에서부터 채운 결과가 false가 나오면 
// loop에서 다른 값을 대입한다.
// 이 3가지 조건 배열의 초기 상태값 입력은 문제의 sudoku 퍼즐 값을 입력하는 단계에서 이루어진다.
// 다음 칸으로 넘어가는 것은 행단위로 1~9 열까지 차례로 진행하고 최종 행 값이 9가 넘어가면
// 81개의 모든 칸을 다 채운 것이므로 더 이상 진행하지 않고 return한다.
// 검증 차원에서 sudoku.com에서 easy~expert 단계 문제까지 모두 넣어서 풀어보니 정상적으로 잘 풀렸다.
// 제한시간 1초 중 84ms(2,024KB)가 소요되었다.
// 맞은사람 1518/6392로 상위 23.74%에 rank되었다.
 
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

vector<vector<int>> sudoku;
vector<vector<bool>> ver; // vertical
vector<vector<bool>> hor; // horizontal
vector<vector<bool>> squ; // 3*3 square;

bool BackTracking(int r, int c)
{
	if (r > 9) return true; // 81칸이 모두 채워진 경우

	bool result = false;
	int sr, sc, next_r, next_c;
	next_r = (c + 1 > 9) ? r + 1 : r;
	next_c = (c + 1 > 9) ? 1 : c + 1;
	if (sudoku[r][c]) // 비어있지 않을 경우
		return BackTracking(next_r, next_c);
	sr = (r - 1) / 3 + 1;
	sc = (c - 1) / 3 + 1;
	for (int i = 1; i < 10; i++) { // 비어있는 경우, [r][c]에 1~9 차례로 대입
		if (!hor[r][i] && !ver[c][i] && !squ[(sr - 1) * 3 + sc][i]) {
			hor[r][i] = ver[c][i] = squ[(sr - 1) * 3 + sc][i] = true;
			sudoku[r][c] = i;
			result = BackTracking(next_r, next_c);
			if (!result) {
				hor[r][i] = ver[c][i] = squ[(sr - 1) * 3 + sc][i] = false;
				sudoku[r][c] = 0;
			}
			else
				break; // 채워진 어떤 값이 이상없으면 다른 숫자 또 넣어볼 필요 없이 바로 loop 빠져 나온다.
		}
	}
	return result;
}

int main() {

	FAST;

	sudoku.resize(10, vector<int>(10, 0));
	ver.resize(10, vector<bool>(10, false));
	hor.resize(10, vector<bool>(10, false));
	squ.resize(10, vector<bool>(10, false));

	int val, r, c;
	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			cin >> val;
			sudoku[i][j] = val;
			if (val > 0) {
				hor[i][val] = true; // 수평 check
				ver[j][val] = true; // 수직 check
				r = (i - 1) / 3 + 1;
				c = (j - 1) / 3 + 1;
				squ[(r - 1) * 3 + c][val] = true; // square check
			}
		}
	}
	BackTracking(1, 1);

	for (int i = 1; i < 10; i++) { // 결과 출력
		for (int j = 1; j < 10; j++)
			cout << sudoku[i][j] << " ";
		cout << "\n";
	}
}