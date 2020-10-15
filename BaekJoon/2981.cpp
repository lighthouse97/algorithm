// 2981.cpp
// 검문
// 최대공약수, 공약수의 응용 문제이다.
// 정답률이 21.669%로 낮은편이다. 즉 난이도가 높다는 말이다.
// 풀이방법은, A, B, C, D 가 있을 때
// 오름차순으로 정렬하고
// A = a*M + R
// B = b*M + R
// C = c*M + R
// D = d*M + R
// B-A = (b-a)*M
// C-B = (c-b)*M
// D-C = (d-c)*M
// B-A, C-B로부터 최대공약수를 구하고, 이 값과 D-C의 최대공약수를 구한다.
// 이렇게 해서 끝까지 가면 N개 수 전체의 최대공약수가 나온다.
// N개 수 전체의 최대공약수로 1을 제외한 약수를 구한다.
// 약수를 구할 때에는 sqrt(GCF)까지만 탐색하고 i번째에서 0으로 나누어지면 i, GCF/i를 리스트에 추가한다. 
// GCF/i=i인 경우는 i, GCF/i와 중복되므로 이때에는 한번만 리스트에 추가하도록 한다.
// 최대공약수는 유클리드 호제법으로 구하고 이를 가지고 약수(common factor)를 구한다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int nums[101] = { 0, };
vector<int> cfs;

int GCF(int A, int B)
{
	int large = A, small = B;
	int temp;
	if (A < B) {
		large = B;
		small = A;
	}
	while (small) {
		temp = large % small;
		large = small;
		small = temp;
	}
	return large;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, b;
	int gcf = 0;
	cin >> N;

	for (int i = 1; i <= N; i++)
		cin >> nums[i];
	sort(nums + 1, nums + 1 + N);
	gcf = nums[2] - nums[1];
	for (int i = 3; i <= N; i++) {
		b = nums[i] - nums[i-1];
		gcf = GCF(gcf, b); // make the gcf for whole numbers
	}
	for (int i = 1; i*i <= gcf; i++) { // make common factors with the whole gcf
		if (gcf % i == 0) {
			cfs.push_back(i);
			if (gcf / i != i)
				cfs.push_back(gcf / i);
		}
	}
	sort(cfs.begin(), cfs.end());
	for (unsigned int i = 1; i < cfs.size(); i++)
		cout << cfs[i] << " ";
	cout << "\n";
}