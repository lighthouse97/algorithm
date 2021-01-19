// 1806.cpp
// �κ���
// ICPC > Regionals > Europe > Southeastern European Regional Contest > SEERC 2006 B��
// ���� two pointer ���� �����̴�.
// �ϴ� ������ �¿�� �� ���纸�� ��������.
// 1) left = 0, right = 0 ���� �����Ѵ�. sum�� ù��° ���Ұ����� �ʱ�ȭ�Ѵ�.
// 2) sum�� S���� ���ų� ũ�� sum���� left���� ���� left�� 1�� ���Ѵ�. �� �� ���̵� 1�� ����.
// 3) sum�� S���� ������ sum���� ���� ���Ҹ� ���ϰ� right�� 1�� ���Ѵ�. �� �� ���̵� 1�� ���Ѵ�.
// 4) 1) ~ 3)�� left  < N && right < N �� ������ �ݺ��Ѵ�.
// 5) 1) ~ 3) �ݺ��ϸ鼭 sum�� S���� ���ų� Ŭ �� �� ���� ������ ���� ���� ���� �����Ѵ�.
//    ���� ���̰� 1�̸� ���� ���� ���̹Ƿ� �� �� �� ���� �ٷ� �������´�.
// 6) ������ ���� �ڿ� ���� ���� ���̰��� ����ϴµ� ���� ���̰��� ������Ʈ ���� ������ ������ �������� ���ϹǷ� 0�� ����Ѵ�.
// ���ѽð� 0.5�� �� 8ms(2,408KB)�� �ҿ�Ǿ���.
// ������� 526/3976�� ���� 13.22%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	int N, S;
	vector<int> nums;

	cin >> N >> S;
	nums.resize(N, 0);
	for (int i = 0; i < N; i++) cin >> nums[i];

	int sum = 0, minLen = N + 99999, len = 1, left = 0, right = 0;
	sum = nums[left];
	while (left  < N && right < N) {		
		if (sum >= S) { 
			minLen = min(minLen, len);
			if (minLen == 1) break;
		}
		if (sum >= S) {
			sum -= nums[left];			
			left++;			
			len--;
		}
		else {
			right++;
			if (right < N) {
				sum += nums[right];
				len++;
			}
		}
	}
	cout << ((minLen > N) ? 0 : minLen) << "\n";
}