// 2170.cpp
// �� �߱�
// ���⼭���� ������(sweeping) �����̴�.
// ������ ���� ���� �����ε� ������ �ظ��T_T...
// 1) (s, e)�� �Է¹޾Ƽ� �������� �����Ѵ�. ( ��, S < e�� �ǵ��� ó���ؾ� �Ѵ�!)
// 2) ������ ���� e�� ����� ���� ������ �ʱ�ȭ�Ѵ�.
// 3) ���� e <= ���� s �̸� ���� length = e - s �� �������ְ�
// 4) ���� e > ���� s �̸� ���� length - (���� e - ���� s)�� �ߺ��κ��� �� �ش�. �� ���� �����Ѵ�.
// 5) 4)������ ���� 0���� ���ų� ������ ������ ��ġ�� ���̹Ƿ� 0�� �����Ѵ�.
// 6) ���� e�� ���� e�� ������Ʈ �Ѵ�. ��! '���� e < ���� e' �϶��� �Ѵ�.(������ ��ġ�� ���� ���� e�� ������Ʈ���� �ʴ´�)
// 7) 3) ~ 6)�� N������ �ݺ��Ѵ�.
// ����!!!) 6)�� ������Ʈ ������ ��ó ���� ���ؼ� �� �ð��� ����߾���!!!(���� (1, 7), (2, 6), (3, 7)�� �ִ�.)
// ���ѽð� 1�� �� 380ms(9,832KB)�� �ҿ�Ǿ���.
// ������� 143/1304�� ���� 10.96%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy, swap
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

typedef pair<int, int> pii; // (start, end)
vector<pii> LINE;

int main()
{
	FAST;

	int N, sum = 0;	
	cin >> N;
	LINE.resize(N);

	int s, e;
	for (int i = 0; i < N; i++) {
		cin >> s >> e;
		LINE[i] = (s < e) ? pii(s, e) : pii(e, s);
	}
		
	sort(LINE.begin(), LINE.end()); // �������� ����
	int end = -1000000999, length = 0, temp;
	for (int i = 0; i < N; i++) {		
		length = LINE[i].second - LINE[i].first;
		if (end <= LINE[i].first) // ���� e <= ���� S			
			sum += length;
		else { // ���� e > ���� s
			temp = length - (end - LINE[i].first); // ��ģ �κ��� ���ش�.
			sum += (temp > 0 ? temp : 0); // �Ϻθ� ��ģ ���(��ģ�κ� �����ϰ� +) : ������ ��ģ ���(0 +)
		}		
		end = (end < LINE[i].second) ? LINE[i].second : end;
	}	
	cout << sum << "\n";
}