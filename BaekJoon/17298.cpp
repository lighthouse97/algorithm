// 17298.cpp
// ��ū��
// �� ������ ������ �����ؼ� Ǭ��.
// �߱��̻��� â������ �ذ� �ɷ��� �ʿ��ϴ�.
// �Է� �迭 ����Ʈ�� ������ ���� Ž��
// 1) stack�� empty�̸� push, -1
// 2) �Է°� < top �̸� push, top
// 3) �Է°� >= top �̸� pop, 2)���� �ݺ�
// 4) ��� pop�ϴٰ� empty�Ǹ� 1)ó��, -1
// 5) �Է� �迭 ����Ʈ ���������� 1) ~ 4) �ݺ��Ѵ�.
// stack�� ������� �ʰ� ���� for���� �̿��ϸ� O(N^2)�� �Ǿ �ð��ʰ��� �߻��Ѵ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // getline, string, stoi
//#include <utility> // pair
//#include <map> // map
#include <stack>

using namespace std;

int arr[1000001] = { 0, };
stack <int> sti;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, iter;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> arr[i];
	
	for (int i = N; i >= 1; i--) {
		iter = arr[i];
		while (true) {
			if (sti.empty()) {
				sti.push(iter);
				arr[i] = -1;
				break;
			}
			else if (iter < sti.top()) {
				arr[i] = sti.top();
				sti.push(iter);
				break;
			}
			else {
				sti.pop();
			}
		}
	}
	for (int i = 1; i <= N; i++)
		cout << arr[i] << " ";
	cout << "\n";
}