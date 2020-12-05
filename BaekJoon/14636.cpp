// 14636.cpp
// Money for Nothing
// ICPC > World Finals > 2017 World Finals D번
// 이것도  D&Q Optimization 응용문제이다.
// D&Q 바로 적용이 안되고 한번 전처리를 해주어야 한다! 이게 응용력이 많이 필요하다.
// 일단 풀어보고 맞으면 정리하기로 하자!
// 10%에서 시간초과 발생. 더 최적화해야 겠다!!!
// 1) producer를 날짜 순으로 오름차순 정렬, 처음부터 탐색, 다음 것이 오른쪽 아래에 있는 것만 선택한다.
// 2) consumer를 날짜 순으로 오름차순 정렬, 끝에서 부터 탐색, 다음 것이 왼쪽 위에 있는 것만 선택한다.
// 1) , 2)의 이유는 중간 dealer 입장에서 이윤을 최대로 하기 위한 문제의 조건을 고려하면 당연한 것이다.
// 3) 새로 만든 producer list를 i값의 범위로 하고, 새로 만든 consumer의 범위를 k의 범위로 잡아서 D&Q optimization을 실행한다.
//  consumer를 중심으로 producer의 날짜 차이 * 가격 차이가 dealer가 취할 수 있는 이윤이 된다.
//  곱한 값이 음수(-)가 나올 수도 있는데 음수가 나와도 음수값까지 포함해서 최대값을 구하고 여기서 optk값을 구해서 적용한다.
// 4) 날짜 차이, 가격 차이가 둘 다 음수(-)인 경우는 그림을 그려보면 알겠지만 모든 consumer에 대해 면젹이 +가 나올 수 없다.
//  따라서 0이 최대값이 될 수 밖에 없으므로 이 경우는 그냥 0으로 리턴한다.(optk를 뭘 선택해도 어차피 결과는 0이다)
// 5) D&Q 수행할 때마다 나온 최대값들 중 가장 큰 값(모두 음수인 경우는 0)이 최대로 취할 수 있는 이윤이 된다.
// **) 면적이 음수(-)가 나오는 경우를 없앨려고 이리저리 꼼수를 쓰면 코드 지저분해 지고 수행시간이 더 걸려 TLE가 발생한다!!!
// 제한시간 5초 중 400ms(17,652KB)가 소요되었다.
// 맞은사람 21/71로 상위 29.57%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef long long ll;
const ll MINVAL = LLONG_MIN;

struct widget {
	int price;
	int day;
	widget() : price(0), day(0) {}
	widget(int p, int d) : price(p), day(d) {}
};

int M = 0, N = 0; // the number of producer and consumer companies in the market
vector<widget> producer;
vector<widget> consumer;
ll answer = 0;

void trade(int start, int end, int left, int right)
{
	ll value = 0;
	ll maxv = MINVAL;
	int optk = 0;
	if (start > end) return;
	int mid = (start + end) >> 1;
	for (int k = left; k <= right; k++) {
		ll dx = 1LL * consumer[k].day - producer[mid].day;
		ll dy = 1LL * consumer[k].price - producer[mid].price;
		value = (dx < 0 && dy < 0) ? 0 : dx * dy; // -가 나와도 -값 포함해서 최대값을 구해본다!!!
		if (value > maxv) {
			maxv = value;
			optk = k;
		}
	}
	trade(start, mid - 1, left, optk);
	trade(mid + 1, end, optk, right);
	answer = max(answer, maxv);
}

int main()
{
	FAST;

	vector<widget> p_temp, c_temp;
	int type = 0; // 0 : procucer, 1 : consumer
	cin >> M >> N;
	p_temp.resize(M, { 0, 0 });
	c_temp.resize(N, { 0, 0 });	
	for (int i = 0; i < M; i++) cin >> p_temp[i].price >> p_temp[i].day;
	for (int i = 0; i < N; i++) cin >> c_temp[i].price >> c_temp[i].day;

	auto cmp = [&](const widget& i, const widget& j) {
		if (i.day == j.day) {
			if (!type) return (i.price < j.price); // producer
			else return (i.price > j.price); // consumer
		}
		return i.day < j.day;
	};
	// producer 전처리
	sort(p_temp.begin(), p_temp.end(), cmp); // producer를 날짜순으로 오름차순 정렬
	producer.reserve(M);
	for (int i = 0; i < M; i++) 
		if (producer.empty() || producer.back().price > p_temp[i].price) producer.push_back(p_temp[i]); // 오른쪽 아래
	// consumer 전처리
	type = 1; // consumer
	sort(c_temp.begin(), c_temp.end(), cmp); // consumer를 날짜순으로 오름차순 정렬
	consumer.reserve(N);
	for (int i = N - 1; i >= 0; i--)
		if (consumer.empty() || consumer.back().price < c_temp[i].price) consumer.push_back(c_temp[i]); // 왼쪽 위
	reverse(consumer.begin(), consumer.end()); // 순서를 뒤집어 producer와 day 순서 맞춰 준다.
		
	trade(0, (int)producer.size() - 1, 0, (int)consumer.size() - 1);
	cout << answer << "\n";
}