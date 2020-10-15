// 1874.cpp
// ���� ����
// �̰͵� STL�� ������ �����ؼ� Ǯ �� �ִ�.
// ������������ stack�� �ֱ⶧���� stack�� top�� �Է°����� ���ų� �۾ƾ� �Ѵ�.
// ������ ���� ������ stack�� ��� push�ϰ� ������ pop�� �Ѵ�. �� �������� '+', '-'��
// �迭�� �����Ѵ�.
// +, -�� vector�� ���� �ʰ� char�迭�� �ְ� �ٷ� ����ϸ�
// �� �� ���� ó���ȴ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // getline, string, stoi
//#include <utility> // pair
//#include <map> // map
#include <stack>

using namespace std;

int input;
stack <int> sti;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, num=1;
	vector <char> st_info;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> input;
		while (true) {
			if (sti.empty() || sti.top() < input) {
				sti.push(num++);
				st_info.push_back('+');
			}
			else if (sti.top() == input) {
				sti.pop();
				st_info.push_back('-');
				break;
			}
			else
				break;
		}
	}
	if (!sti.empty()) cout << "NO" << "\n";
	else {
		for (auto& x : st_info)
			cout << x << "\n";
	}
}