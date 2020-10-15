// 2618.cpp
// ������
// ���̳��� ���α׷������� Ǭ��.
// �ᱹ�� �׸���� Ǯ� Ʋ���� �ٸ� ����� Ǭ ���� ����������,
// ��ȭ���� ������ ����.(recursive�� Ǯ��� �Ѵ�)
// DP[car1][car2]�� car1, car2 ��ġ�� �� ������ ��� ��ġ���� �����ϴ� �ִ� �Ÿ���� �Ѵٸ�
// DP[car1][car2] = min(position(here, car2) + distance(POS[car1], POS[here]), position(car1, here) + distance(POS[car2], POS[here]))
// here�� car1 �Ǵ� car2�� �̵��ϴ� ���� event ��ġ (here = max(car1, car2) + 1, +1�� ���� ��� ��ġ)
// position(x, y) : car1, car2�� x, y��ġ�� �� ������ ��� ��ġ���� �����ϴ� �ִ� �Ÿ�
// distance(x, y) : x, y ������ �Ÿ�
// ���� ��ġ car1, car2���� car1�� ���õ� ���, car2�� ���õ� ��� ��� ��쿡 ���ؼ� ���� ���� ������� �����ؼ� ������
// event ���� ���ԵǸ� ��� ��쿡 ���� ��� ����� �ϹǷ� DP[1][2]�� ������ ��ü �ִ� ��ΰ� ���´�.
// �ִ� ��ο� ���� path�� PATH[car1][car2] �迭�� ���� ������ �� �迭�� ���� car1�� ���õǸ� 1, car2�� ���õǸ� 2�� �����Ѵ�.
// PATH[1][2]���� �����ؼ� car1�̸� car1 �ε����� ������Ű�� car2�̸� car2 ���ؽ��� �������Ѽ� car1 �Ǵ� car2�� W+2���� �����ϸ�
// PATH[][]�� ���� Ž���� ������. �ε��� ������ max(car1, car2) + 1�� �Ѵ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <cstdlib> // abs
#include <vector>
#include <algorithm> // max, sort
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair
//#include <stack> // stack

using namespace std;

struct point {
	int row;
	int col;
	point() {}
	point(int r, int c) : row(r), col(c) {}
};

int N, W; // ������ ����, ����� ����
vector<point> EVENTS; // �̺�Ʈ ����Ʈ + 2 (���� 2���� �ʱ� ��ġ)
vector<vector<int>> DP; // car1, car2 ��ġ���� event������ �� ���� �ִ� �Ÿ�
vector<vector<int>> PATHS; // car1, car2 ��ġ���� car1�� �����ߴ��� car2�� �����ߴ��� ����

int distance(point x, point y)
{
	return abs(x.row - y.row) + abs(x.col - y.col);
}

// car1, car2 ��ġ���� event �߻��� �ִ� �Ÿ� ����
int process(int car1, int car2)
{
	int dist1, dist2, here;
	here = max(car1, car2) + 1; // ���� �߻��� event
	if (here > W + 2) return 0;
	if (DP[car1][car2] > -1) return DP[car1][car2];
	dist1 = process(here, car2) + distance(EVENTS[car1], EVENTS[here]); // car1 ������ ���
	dist2 = process(car1, here) + distance(EVENTS[car2], EVENTS[here]); // car2 ������ ���
	if (dist2 < dist1) {
		DP[car1][car2] = dist2;
		PATHS[car1][car2] = 2;
	}
	else {
		DP[car1][car2] = dist1;
		PATHS[car1][car2] = 1;
	}

	return DP[car1][car2];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int car1, car2;
	cin >> N >> W;
	EVENTS.resize(W + 1 + 2, point(0,0));
	DP.resize(W + 1 + 2, vector<int>(W + 1 + 2, -1));
	PATHS.resize(W + 1 + 2, vector<int>(W + 1 + 2, -1));
	for (int i = 3; i <= W + 2; i++) {
		cin >> EVENTS[i].row >> EVENTS[i].col;
	}
	EVENTS[1] = point(1, 1);
   EVENTS[2] = point(N, N);
	cout << process(1,2) << "\n";
	car1 = 1, car2 = 2;
	// ��ü �ִ� ��ο��� ��� �������� �����ؼ� car1�� ���õǸ� car1 ��ġ ����, car2�� ���õǸ� car2 ��ġ ����,
	// W���� �����ϸ鼭 car1, car2 ��ġ���� ���õ� car ��ȣ(PATH[car1][car2])�� ����ϸ� �ȴ�. 
	while (true) {
		if (max(car1, car2) == W + 2) break;
		cout << PATHS[car1][car2] << "\n";
		if (PATHS[car1][car2] == 1) car1 = max(car1, car2) + 1;
		else if(PATHS[car1][car2] == 2) car2 = max(car1, car2) + 1;
	}
}