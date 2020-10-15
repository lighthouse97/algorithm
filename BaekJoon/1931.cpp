// 1931.cpp
// ȸ�ǽ� ����
// �׸��� �˰������� Ǯ��� �ϴ� �����̴�.
// ���� ȸ�ǰ� ���� ������ �ð������� �����ϰ� ���� ���� ������ �ð��� ���� �ð���
// ���� �ð��� ȸ�ǳ� �ð��� ��ġ���� üũ�Ͽ� ��ġ�� �������� �Ѿ�� ��ġ�� ������
// ī��Ʈ +1�ϰ� �������� �Ѿ��.
// �̷��� ��û�� �ð��� ������ Ž���Ѵ�.
// ������ ī��Ʈ �� ��ŭ ���� ���� ȸ�Ǹ� ��û�� �� �ִ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

struct mtime {
	unsigned long start;
	unsigned long end;
};

vector<mtime> rooms;

int compare(mtime i, mtime j)
{
	if (i.end == j.end)
		return (i.start < j.start);
	else
		return (i.end < j.end);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, count = 0;
	unsigned long ltime = 0;
	mtime temp;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> temp.start >> temp.end;
		rooms.push_back(temp);
	}

	sort(rooms.begin(), rooms.end(), compare);

	for (int i = 0; i < N; i++) {
		if (rooms[i].start >= ltime) {
			count++;
			ltime = rooms[i].end;
		}
	}
	cout << count << "\n";
}