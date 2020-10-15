// 11049.cpp
// ��� ���� ����
// �� ������ DP�����̴�.
// ���� �ð� ��� ���� ��Ľ��� ���ؼ� ���� ��ȭ���� ������ ����.
// DP[N] = min((DP[N-1] + x[1]*y[n-1]*y[n]) , (DP[N-2] + x[1]*y[n-2]*y[n] + y[n-2]*y[n-1]*y[n]))
// ���� ��ȭ�����δ� Ʋ������ ���´�.
// �ڷḦ �����ؼ� ��ȭ���� �ٽ� �����. (�ڷ���� â�������� ����⿡�� ���� ������)
// ��� x���� ��� y������ ������ ������ func(x,y)��� �ϸ�,
// if(x==y) return 0;
// if(DP[x][y] != -1) return DP[x][y];
// for(int k=x; k<y; k++) {
//   temp = func(x,k) + func(k+1,y) + m[x].row*m[k].col*m[y].col;
//   minval = min(minval, temp);
// }
// DP[x][y] = minval;
// EX)
// (1,2) (2,3) (3,4)
// f(1,1) + f(2,3) + 1*2*4 = 0 + 24 + 8 = 32
// f(1,2) + f(3,3) + 1*3*4 = 6 + 0 + 12 = 18
// DP[1][3] = 18

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
#include <cstring> // memset
//#include <vector>
#include <algorithm> // min
#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

int DP[501][501];
int M[501][2] = { {0, }, }; // 0 : row, 1 : column

int function(int x, int y)
{
	int minval = INT_MAX;
	if (x == y) return 0;
	if (DP[x][y] != -1) return DP[x][y]; // if already exist
	for (int i = x; i < y; i++) {
		minval = min(minval, function(x, i) + function(i + 1, y) + M[x][0] * M[i][1] * M[y][1]);
	}
	DP[x][y] = minval;
	return minval;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	memset(DP, -1, sizeof(DP));
	int N;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> M[i][0] >> M[i][1];
		
	cout << function(1, N) << "\n";
}