// 1493.cpp
// �ڽ� ä���
// ���� ������ �̿��ؼ� Ǫ�� �����̴�.
// ���Ǹ����� ����ϸ� Ʋ����.
// ���� 4 * 5 * 7 �� ��� 4 * 4 * 4 cube�� ���� ä��� ���� ������ ���������� 2 * 2 * 2 cube�� ���� ä�� ���� ����.
// ���� ū ť����� ���� ���� ť����� l, w, h�� ���  cube�� �� ������ ��Ȯ�� ������ �������� ť��� ��� ä�� �� �ִ�.
// ���� ū ť����� ���ʷ� ä�� ������.
// example�� ���� ��� �����ϸ�,
// 1) 4*4*4 cube�� �ڽ��� ä��� (4/4)*(4/4)*(8/4)=2, 2���� ä�� �� �ִ�. �׷��� cube�� 1���� 1���� ä���.
// 2) 2*2*2 cube�� �ڽ��� ä��� (4/2)*(4/2)*(8/2)=16, 16�� ä�� �� �ִ�. �׷��� ���� 4*4*4 cube���� 1�� ä��� �����Ƿ�
//    (4/2)*(4/2)*(4/2)=8, 16���� 8�� ����� �Ѵ�. 16-8=8, 2*2*2 cube 10���̹Ƿ� 8���� ��� ä�� �� �ִ�.
// 3) 1*1*1 cube�� �ڽ��� ä��� (4/1)*(4/1)*(8/1)=128, 128�� ä�� �� �ִ�. �׷��� ���� 1), 2)���� ä�� �ڽ��� ����� �ϹǷ�
//    (4/1)*(4/1)*(4/1)=64, (2/1)*(2/1)*(2/1)=8, 8*8=64, 64 + 64 = 128�� ����� �Ѵ�. 128 - 128 = 0
// 1)�� 1��, 2)�� 8��, 3)�� 0�� ��� ���ϸ� 9���� ���´�.
// 1), 2), 3) ������ �ܰ迡�� l, w, h�� ��� cube�� �� ������ ��Ȯ�� ������ ��������, cube������ ����ؼ� ��� ä�� �� ������
// ���� �ܰ�(cube)�� �Ѿ �ʿ���� ���� �ܰ迡�� ������ �ȴ�.
// ������ cube���� ��� ������������ �ұ��ϰ� l, w, h�� cube�� �� ������ ��Ȯ�� ������ �������� �ʰ�, cube�� ��� ä�� ��
// ������ �־��� cube�� �ڽ��� ��� ä�� �� ���� ����̹Ƿ� �̶��� -1�� ����Ѵ�.
// ���ѽð� 1�� �� 0ms(2,016KB)�� �ҿ�Ǿ���.
// ������� 154/410�� ���� 37.56%�� rank�Ǿ���.

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
#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
typedef long long ll;

int main()
{
	FAST;

	int length, width, height;
	int n, a, b;
	vector<pair<int, int>> cube;

	cin >> length >> width >> height;
	cin >> n;
	cube.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		cube[i] = { a, b };
	}
	sort(cube.begin(), cube.end());

	int ln;
	ll num, sum = 0;
	vector<ll> count(n, 0);
	bool fit = false;
	for (int i = n - 1; i >= 0; i--) {		
		ln = 1 << cube[i].first;
		if (length >= ln && width >= ln && height >= ln) {
			num = 1LL * (length / ln) * (width / ln) * (height / ln); // ���� cube�� �ִ� � ä��� �ִ��� ���			
			for (int j = n - 1; j > i; j--) { // �� ���� ť��� ä�� ��� ���� ū ť�꿡�� ä�� ��ŭ ���ش�.
				ll temp = 1LL << ((cube[j].first - cube[i].first) * 3);				
				temp *= count[j];				
				num -= temp;
			}						
			fit = (length % ln == 0) && (width % ln == 0) && (height % ln == 0);
			if (cube[i].second < num) {
				count[i] = cube[i].second;
				fit = false; // cube�� ���°� ä�� �� ������ cube ���� ���ڶ�� ���� fit���� ���ϴ�.
			}
			else {
				count[i] = num;		
				if (fit) break; // Ư�� cube�� �ڽ��� �¾ƶ������� �� ���� �� �ʿ����.
			}			
		}		
	}
	for (ll x : count) sum += x;
	cout << (fit ? sum : -1) << "\n";
}