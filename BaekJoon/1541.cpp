// 1541.cpp
// �Ҿ���� ��ȣ
// �׸��� �˰������� Ǭ��.
// -�� ������������ ��� �����ִٰ� - ���� ���ĺ��ʹ� ��� ���ִ� ���� �����̴�.
// 1) ��Ʈ�� �Է��� �޴´�.
// 2) ��Ʈ���� ���ʷ� �˻��ؼ� ���ڸ� ��Ʈ���� �����Ѵ�
// 3) ��ȣ�� ������ ���ݱ��� ������ ���ڽ�Ʈ���� ���ڷ� �ٲپ�(std::stoi ���) ������� ���ϰų� ����.
// 4) ��ȣ�� -�� ������������ ���ڸ� ��� �����ش�.
// 5) ��ȣ�� -�� ���� ���ĺ��ʹ� ���ڸ� ��� ���ش�.
// 6) ���ڹ迭 ������ ����
#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string expr, temp = "";
	int minus = 0, result = 0;
	cin >> expr;

	for (unsigned int i = 0; i < expr.length(); i++) {
		if (expr[i] >= '0' && expr[i] <= '9') {
			temp += expr[i];
		}
		else if (expr[i] == '+' || expr[i] == '-') {
			if (minus) result -= stoi(temp);
			else result += stoi(temp);
			minus = (expr[i] == '-') ? 1 : minus;
			temp = "";
		}
		else
			;
	}
	if (temp.length()) {
		if (minus) result -= stoi(temp);
		else result += stoi(temp);
	}
	
	cout << result << "\n";
}