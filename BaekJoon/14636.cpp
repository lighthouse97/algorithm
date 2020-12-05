// 14636.cpp
// Money for Nothing
// ICPC > World Finals > 2017 World Finals D��
// �̰͵�  D&Q Optimization ���빮���̴�.
// D&Q �ٷ� ������ �ȵǰ� �ѹ� ��ó���� ���־�� �Ѵ�! �̰� ������� ���� �ʿ��ϴ�.
// �ϴ� Ǯ��� ������ �����ϱ�� ����!
// 10%���� �ð��ʰ� �߻�. �� ����ȭ�ؾ� �ڴ�!!!
// 1) producer�� ��¥ ������ �������� ����, ó������ Ž��, ���� ���� ������ �Ʒ��� �ִ� �͸� �����Ѵ�.
// 2) consumer�� ��¥ ������ �������� ����, ������ ���� Ž��, ���� ���� ���� ���� �ִ� �͸� �����Ѵ�.
// 1) , 2)�� ������ �߰� dealer ���忡�� ������ �ִ�� �ϱ� ���� ������ ������ ����ϸ� �翬�� ���̴�.
// 3) ���� ���� producer list�� i���� ������ �ϰ�, ���� ���� consumer�� ������ k�� ������ ��Ƽ� D&Q optimization�� �����Ѵ�.
//  consumer�� �߽����� producer�� ��¥ ���� * ���� ���̰� dealer�� ���� �� �ִ� ������ �ȴ�.
//  ���� ���� ����(-)�� ���� ���� �ִµ� ������ ���͵� ���������� �����ؼ� �ִ밪�� ���ϰ� ���⼭ optk���� ���ؼ� �����Ѵ�.
// 4) ��¥ ����, ���� ���̰� �� �� ����(-)�� ���� �׸��� �׷����� �˰����� ��� consumer�� ���� �頬�� +�� ���� �� ����.
//  ���� 0�� �ִ밪�� �� �� �ۿ� �����Ƿ� �� ���� �׳� 0���� �����Ѵ�.(optk�� �� �����ص� ������ ����� 0�̴�)
// 5) D&Q ������ ������ ���� �ִ밪�� �� ���� ū ��(��� ������ ���� 0)�� �ִ�� ���� �� �ִ� ������ �ȴ�.
// **) ������ ����(-)�� ������ ��츦 ���ٷ��� �̸����� �ļ��� ���� �ڵ� �������� ���� ����ð��� �� �ɷ� TLE�� �߻��Ѵ�!!!
// ���ѽð� 5�� �� 400ms(17,652KB)�� �ҿ�Ǿ���.
// ������� 21/71�� ���� 29.57%�� rank�Ǿ���.

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
		value = (dx < 0 && dy < 0) ? 0 : dx * dy; // -�� ���͵� -�� �����ؼ� �ִ밪�� ���غ���!!!
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
	// producer ��ó��
	sort(p_temp.begin(), p_temp.end(), cmp); // producer�� ��¥������ �������� ����
	producer.reserve(M);
	for (int i = 0; i < M; i++) 
		if (producer.empty() || producer.back().price > p_temp[i].price) producer.push_back(p_temp[i]); // ������ �Ʒ�
	// consumer ��ó��
	type = 1; // consumer
	sort(c_temp.begin(), c_temp.end(), cmp); // consumer�� ��¥������ �������� ����
	consumer.reserve(N);
	for (int i = N - 1; i >= 0; i--)
		if (consumer.empty() || consumer.back().price < c_temp[i].price) consumer.push_back(c_temp[i]); // ���� ��
	reverse(consumer.begin(), consumer.end()); // ������ ������ producer�� day ���� ���� �ش�.
		
	trade(0, (int)producer.size() - 1, 0, (int)consumer.size() - 1);
	cout << answer << "\n";
}