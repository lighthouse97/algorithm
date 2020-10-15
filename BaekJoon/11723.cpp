// 11723.cpp
// ����
// 20�� �迭 ����� �׳� �����ϸ� �� �� ����.
// �� �ҿ�ð��� 724ms�� 1988B�� ���Դ�.
// scanf, printf�� �ٲ㼭 �� ���� 1048ms�� �ð��� �� ���� �ҿ�Ǿ���.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <cstdlib> // abs
//#include <vector>
//#include <algorithm> // max, sort
//#include <climits> // INT_MAX
#include <string>
//#include <utility> // pair
//#include <stack> // stack
#include <bitset> // bitmask

using namespace std;

int M;
bitset<20> S;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string cmd;
	int arg;

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> cmd;
		if (cmd == "add") {
			cin >> arg;
			if (!S[arg-1]) S[arg - 1] = 1;
		}
		else if (cmd == "remove") {
			cin >> arg;
			if (S[arg - 1]) S[arg - 1] = 0;
		}
		else if (cmd == "check") {
			cin >> arg;
			cout << (S[arg - 1] ? 1 : 0) << "\n";
		}
		else if (cmd == "toggle") {
			cin >> arg;
			S.flip(arg - 1);
		}
		else if (cmd == "all") {
			S.set();
		}
		else if (cmd == "empty") {
			S.reset();
		}
		else {
		}
	}
}
