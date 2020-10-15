// 1520.cpp
// ������ ��
// DP�����ε� ����� ������δ� �̹� Ǯ����.
// �ݺ����� ���� bottom up ������� Ǯ���!
// ��θ� ���󰡸鼭 Ž���ϴ� ���� ����� ����̰�
// �ݺ����� ���� ����� ������ ���������� �˻��� �ϴµ� �־��� ������ �״��
// ��������� ���ʴ�� ã�ư��鼭 ������ üũ�ϸ� ���� ������ �ʴ´�.
// �־��� �����͸� ������������ �����ϰ� ���� ���� ������ ���� ���ʴ�� ������ üũ�ϸ�
// DP[1][1]�� ù ����������� ���Ϸ��� ����� ���� ������ �ȴ�.
// ���� ������ ������ ǥ�� ����� ���� ���� �¾Ҵ�.
// �ݺ����� ���� ���� ����� 40ms(32ms, �Ʒ� ����ȭ), 8648KB�� ���Դ�. ��Ϳ����� 24ms, 3948KB�� ���Դ�.
// �ݺ������� �� ���� DP ���� ��� ���̸� ���������, ����Լ��� �� ���� ����������� ���ǿ� �´� ���̸�
// ã�Ƽ� ����ϱ� ������ ��� ȸ���� �� ����.
// ���� DP������� ó���� �� �ݺ����� �� �������� �� ��쿡�� ����Լ��� �̿��� ����� �� ������.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // max, sort
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

struct loc {
	int x;
	int y;
	int h; // height
};

#if 0 // ������ ó���ϱ� ���� �� �� ����ȭ ���� ���Ҵ�.
vector<loc> PATH;
int DP[501][501] = { { 0, }, };
int AR[501][501] = { { 0, }, };
int MX[4] = { 0, 1, 0, -1 }; // move X
int MY[4] = { 1, 0, -1, 0 }; // move Y

int compare(loc x, loc y)
{
	if (x.h < y.h) return 1;
	else return 0;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int M, N;
	int adx, ady, cx, cy;
	cin >> M >> N;
	PATH.push_back({0, 0, 0});
	for (int i = 1; i <= M; i++)
		for (int j = 1; j <= N; j++) {
			cin >> AR[i][j];
			PATH.push_back({i, j, AR[i][j]});
		}
	// sort item's value to ascending order
	sort(PATH.begin(), PATH.end(), compare);
	DP[M][N] = 1;
	for (unsigned int i = 1; i < PATH.size(); i++) {
		cx = PATH[i].x; cy = PATH[i].y;
		for (int k = 0; k < 4; k++) {
			adx = cx + MX[k]; ady = cy + MY[k];
			if(adx <= M && ady <= N && adx >=1 && ady >= 1)
			  if (AR[cx][cy] < AR[adx][ady]) DP[adx][ady] += DP[cx][cy];
		}
	}
	cout << DP[1][1] << "\n";
}
#else
vector<loc> PATH[10001]; // ������ �ʿ���� ��ü ���� �迭�� �ٷ� �ִ´�.
int DP[501][501] = { { 0, }, };
int AR[501][501] = { { 0, }, };
int MX[4] = { 0, 1, 0, -1 }; // move X
int MY[4] = { 1, 0, -1, 0 }; // move Y

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int M, N;
	int adx, ady, cx, cy;
	cin >> M >> N;
	for (int i = 1; i <= M; i++)
		for (int j = 1; j <= N; j++) {
			cin >> AR[i][j];
			PATH[AR[i][j]].push_back({ i, j, AR[i][j] });
		}
	DP[M][N] = 1;
	for (int i = 1; i <= 10000; i++) {
		for (unsigned int j = 0; j < PATH[i].size(); j++) {
			cx = PATH[i][j].x; cy = PATH[i][j].y;
			for (int k = 0; k < 4; k++) {
				adx = cx + MX[k]; ady = cy + MY[k];
				if (adx <= M && ady <= N && adx >= 1 && ady >= 1 
					&& AR[cx][cy] < AR[adx][ady])
					DP[adx][ady] += DP[cx][cy];
			}
		}
	}
	cout << DP[1][1] << "\n";
}

#endif