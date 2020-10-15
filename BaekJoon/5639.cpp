// 5639.cpp
// 이진 검색 트리
// 이건 내가 이진 탐색 트리 문제 자체를 완전히 잘못 이해하고 있어서
// 문제 푸는데 시간을 어마어마하게 잡아먹었다.
// 문제를 단어 하나도 빠지지 않고 꼼꼼히 잘 읽어봐야 한다는 것을 뼈저리게 느꼈다.
// 루트노드의 왼쪽에 있는 모든 서브트리의 값은 루트노드보다 작아야 하는 조건이
// 분명히 있는데도 불구하고 서브트리 특정 노드의 오른쪽 값이 루트보다 더 클 수 있다고
// 잘못 이해하는 바람에 문제 푸는데 실마리도 못잡고 완전히 꼬여버렸다.
// 전위순위의 가장 첫번째는 root이고 root보다 큰 값이 나올때까지 탐색해서 큰값의 왼쪽은
// 왼쪽 서브트리, 큰값부터 끝까지는 오른쪽 서브트리로 해서 재귀방식으로 푼다.
// 시간제한 1초에서 36ms(2308KB) 소요되었다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue>

using namespace std;

vector<int> PRE_ORDER;

void post_order(int start, int end)
{
	int root, position;
	if (start > end) return;
	root = PRE_ORDER[start];
	position = start + 1;
	while ((position <= end) && (PRE_ORDER[position] < root)) {
		position++;
	}
	post_order(start + 1, position - 1); // LEFT
	post_order(position, end); // RIGHT
	cout << root << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int num;
	PRE_ORDER.push_back(0);
	while (cin >> num) PRE_ORDER.push_back(num);
	post_order(1, (int)PRE_ORDER.size() - 1);
}