// 10986.cpp
// 나머지 합
// 내 능력으로는 어려운 문제이다.
// 그냥 풀었다가는 TLE가 나올 거 같아 풀이를 한참 보고서야
// 비로소 이해를 했다.
// 기본원리는 다음과 같다.
// 1) 1부터(1부터 시작) i까지의 누적합을 pSum[i]라고 할 대, A + 1 부터 B 까지
// 구간합은 pSum[B] - pSum[A]가 된다. 2) 이 때의 구간합을 M으로 나누었을 때의
// 나머지가 0이 된다는 것은 (pSum[B] - pSum[A]) % M = 0, 즉 pSum[B] % M =
// pSum[A] % M 이다. 이 부분이 핵심이다. 3) 다음 모든 누적합들에 대해 나머지가
// 같은 것들끼리 모은다.(모은 것의 갯수를 저장) 나머지가 같은 것이 2개 이상이면
// 이중 2개씩 조합으로 묶으면 이들이 구간합에 대해 나머지가 0인 것들이다. 4)
// 예를 들어 나머지가 2인것이 3개가 나올 때, 이 3개는 각각 어떠한 누적합들일
// 것이고 이 3개에서 2개씩 묶어서 조합을 만들면 그 갯수는 3C2=3이 되고 이 3개가
// 어떤 구간 인지는 모르지만 어떤 구간합의 나머지가 0이 되는 갯수가 된다.
// 9,840KB, 140ms 소요되었다.

#include "pch.h"
#include <iostream>
//#include <sstream>
//#include <string>
//#include <cstring> // strlen
//#include <cctype> // isdigit
#include <vector>
//#include <list>
//#include <algorithm> // sort
//#include <unordered_map>
//#include <utility> // pair, make_pair()
//#include <set>
//#include <unordered_set>
//#include <cmath> // sqrt
#define FAST ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);

using namespace std;

int main() {
   FAST;

   int N, M;
   vector<long long> pSum;
   vector<int> remainder;

   cin >> N >> M;
   pSum.resize(N + 1, 0);
   remainder.resize(M, 0);

   int num;
   long long count = 0;
   for (int i = 1; i < N + 1; i++) {
      cin >> num;
      pSum[i] += (pSum[i - 1] + num);
      remainder[pSum[i] % M]++;
   }

   count += remainder[0];
   for (int i = 0; i < M; i++) {
      if (remainder[i] >= 2)
         count += 1LL * remainder[i] * (remainder[i] - 1) / 2; // _cntC_2를 구한다.
   }
   cout << count << '\n';
}