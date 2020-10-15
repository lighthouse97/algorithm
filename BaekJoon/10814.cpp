// 10814.cpp
// ���̼� ����
// ������ ������ std::stable_sort(sort�� �ƴ� stable_sort�� ��� ����Ѵ�!)
// �� ����ص� ������ �� �� ������ �����ϱ� ���ؼ��� ���̰� �Է� 200�����̹Ƿ�
// vector<string>�� �迭�� �����(vector<string> members[201]�� ����)
// ���̸� �ε����� �ϰ� ���̿� ���� �̸��� string vector�� �����ϸ�,
// �迭�� ���� index 200���� ���������� �˻��ϸ鼭 �̸� ������ ũ�Ⱑ 0���� ū �͸� ���ʴ��
// �ε���(����), �ε����� ���͸���Ʈ(�̸���)�� ����ϸ� �־��� ������ �����ϸ鼭 ������ ó���� �� �ִ�.
// sort�� ������� ��(80ms) --> �迭���(32ms)�� �ҿ�ð��� ���� �پ�����.

#include "pch.h"
#include <iostream>
//#include <cstdio>
//#include <utility> // pair
#include <vector> // vector
//#include <algorithm> // sort
#include <string>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	vector<string> members[201];
	int N;
	int age;
	string name;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> age >> name;
		members[age].push_back(name);
	}
	for (int i = 0; i < 201; i++) {
		for (int j = 0; j < members[i].size(); j++)
			cout << i << " " << members[i][j] << "\n";
	}
}