// 1002.cpp
// Turret

#include "pch.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

int main()
{
	int T;
	int x1, y1, r1, x2, y2, r2;
	int diff_r, num_loc=0;
	double distance;

	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf("%d %d %d %d %d %d", &x1, &y1, &r1, &x2, &y2, &r2);
		distance = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
		diff_r = (r1 > r2) ? r1 - r2 : r2 - r1;
		if (distance > diff_r && distance < r1 + r2) num_loc = 2;
		else if(distance < diff_r || distance > r1 + r2) num_loc = 0;
		else if(distance == 0 && diff_r == 0) num_loc = -1;
		else if(distance == diff_r || distance == r1 + r2) num_loc = 1;
		printf("%d\n", num_loc);
	}
}