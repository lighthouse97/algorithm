// 10775.cpp
// ����
// ���Ͽ� ���ε带 �����ϴ� �����̴�.(���)
// Canadian Computing Competition & Olympiad(2015) Senior Division�� ���Դ� �����̴�.
// ���� �رݸ� �����ص� Ǯ���ִ� �����ε� �� ������ �ȵǾ�
// �ᱹ Google �˻��ؼ� �˰����� ���� Ǯ�ԵǾ���.
// ��ð� ����ص� �𸣰ڴ� ���� 5�ʵ� �ȵǾ� �˰��� ������ ���� �˰ԵǾ���.
// �̰� �ɷ��ڿ� �ѽ��� ���� ���̰� �ƴѰ� �ʹ�!!!
// �����ϴ� ����⸶�� Gi���� ������ ���� ����Ʈ�� ���� (Gi-1)�� ��Ʈ�� �����.
// �� (Gi-1)���� join�Ѵ�.
// �̷��� Gi���� ��� �����Ű�ٰ� ��� ���� Ư�� Gi���� root�� 0�� �Ǹ� �� �̻�
// ����Ⱑ ��ŷ�� ����Ʈ�� ���� �ȴ�. ���ĺ��ʹ� �� �̻� ��ŷ�� �Ұ����ϴ�.
// �˰��� ���� ������ �˰����̴�...T_T
// �ҿ�ð��� ���ѽð� 1�� �� 12ms(2376KB)�̴�.
// (��ü 822 �� 105�� ���� 12.77%�� �����.)

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min, lower_bound
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue>
//#include <unordered_map>

using namespace std;

int G, P;
vector<int> DJS;

int find_djs(int item)
{
	if (DJS[item] == item) return item;
	else
		return DJS[item] = find_djs(DJS[item]);
}

void union_djs(int s1, int s2)
{
	int r1, r2;
	r1 = find_djs(s1);
	r2 = find_djs(s2);
	if (r1 == r2) return; // already same set!
	else
		DJS[r2] = r1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int count = 0, available = 1, gi, root;
	cin >> G >> P;
	DJS.resize(G + 1, 0);
	for (int i = 0; i <= G; i++) DJS[i] = i;
	for (int i = 0; i < P; i++) {
		cin >> gi;
		if (!available) continue;
		root = find_djs(gi);
		if (root != 0) {
			union_djs(root - 1, root);
			count++;
		}
		else
			available = 0;
	}
	cout << count << "\n";
}
