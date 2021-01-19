// 2470.cpp
// �� ���
// Olympiad > �ѱ������ø��ǾƵ� > KOI 2010 > �ߵ�� 1��
// �� ������ two pointer ���� �����̴�.
// ���̵� �� �ö��µ� �ϴ� Ǯ��� ��������!
// 1) �Էµ� ������ �������� �����Ѵ�.
// 2) �� ó���� �� �������� ���Ѵ�.(left, right�� �ʱⰪ)
// 3) �������ʹ� left�� ���� right�� ���� ���Ѵ�.
// 4) �� ���� ����(-)�̸� left�� +1�ϰ� ���(+)�̸� right�� -1�Ѵ�.
// 5) 2) ~ 4)�� left < right�� ������ �ݺ��Ѵ�.
// 6) 2) ~ 4) �ݺ��ϸ鼭, 3) ������ ���Ѱ��� ���밪�� ���� ���� ��츦 left, right�� ���� �Բ� �����Ѵ�.
//    ���� 0�̸� ���� ���� ����̹Ƿ� �ٷ� �������´�.
// 7) ��� ����̸� ù 2��, ��� �����̸� ������ 2���� ���� �ȴ�.
// ���ѽð� 1�� �� 16ms(2,408KB)�� �ҿ�Ǿ���.
// ������� 133/1952�� ���� 6.81%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
#include <utility> // pair
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

	int N;
	vector<int> arr;	
	cin >> N;
	arr.resize(N, 0);	
	for (int i = 0; i < N; i++) cin >> arr[i];

	pair<int, int> result;
	sort(arr.begin(), arr.end());
		
	int sz = (int)arr.size();
	int sum = 0, left = 0, right = sz - 1, minval = 2000000999;
	if (arr[0] > 0) result = { arr[0], arr[1] }; // ��� +
	else if(arr[sz - 1] < 0) result = { arr[sz - 2], arr[sz - 1] }; // ��� -
	else {
		while (left != right) {
			sum = arr[left] + arr[right];
			if (abs(sum) < minval) {
				minval = abs(sum);
				result = { arr[left], arr[right] };
			}			
			if (minval == 0) break;
			if (sum < 0) left++;
			else right--;		
		}
	}
	cout << result.first << " " << result.second << "\n";
}