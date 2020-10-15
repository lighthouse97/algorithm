// 11049_1.cpp
// ��� ���� ����
// �� ������ DP�����̴�.
// �ٷ� ���� 11049���� Ǯ���� ���� recursive ����̰� ������ Ǯ������
// ���� �ð��� 148ms�ɸ��� 2972KB �����Ͽ���.
// recursive ����� �ڵ��� ���ش� ��������� ������ ����ð��� ���� �ɷ�
// �̸� ���̱� ���� for���� ����ϴ� iteration ������� ó���Ͽ���.
// recursive����� ��� (1,N) ��ü���� (1,1)���� �Ʒ��� �������� top-down ����̶��
// iteration����� �ݴ�� ��� (1,1)���� ���(1,N)���� �ö󰡴� bottom-up ����̴�.
// ��ȭ���� ������ ����.
// for(int k=i; k<j; k++)
//   DP[i][j] = DP[i][k] + DP[k+1][j] + M[i].row * M[k].col * M[j].col
// �� �� (i, j)�� ������ 0�̳� 1�̳� 2�̻��̳Ŀ� ���� �ٸ��� ó���Ѵ�.
// (i, j) ������ 1�� ������ ���� ��ü N���� Ȯ��ȴ�.
// iteration ����� �����ϸ� 40ms, 2972KB�� �޸𸮻��� ũ��� �����ϰ� ����ð��� 3.7�� �پ���.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // min
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

int DP[501][501] = { {0, }, };
int M[501][2] = { {0, }, }; // 0 : row, 1 : column

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, j, temp;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> M[i][0] >> M[i][1];

	// (i,j) ������ 0�� ���� �̸� 0���� �ʱ�ȭ �Ǿ� �ִ�.
	// (i,j) ������ 1�� ��츦 �̸� ����� �д�.
	for (int i = 1; i <= N - 1; i++)
		DP[i][i + 1] = M[i][0] * M[i][1] * M[i + 1][1];

	// (i,j) ������ 2�̻��� ����̴�.
	for (int l = 2; l <= N; l++) { // (i,j) ������ 2���� N���� �ø���.(�����δ� N-1������ ��ȿ�ϴ�)
		for (int i = 1; i <= N - l; i++) { // i�� �����ġ�� ���Ѵ�.
			j = i + l; // j�� ��ġ�� ���Ѵ�.
			for (int k = i; k < j; k++) { // (i,j) ���̸� �����ϴ� k�� ��ġ�� ���Ѵ�.
				temp = DP[i][k] + DP[k + 1][j] + M[i][0] * M[k][1] * M[j][1];
				if(DP[i][j] == 0 || temp < DP[i][j])
				  DP[i][j] = temp;
			}
		}
	}
	cout << DP[1][N] << "\n";
}