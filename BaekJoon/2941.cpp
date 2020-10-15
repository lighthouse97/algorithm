// 2941.cpp

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string croa[8] = {"c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z="};
	string txt;
	int found = 0;
	int pos;

	cin >> txt;
	for (int i = 0; i < 8; i++) {
		pos = txt.find(croa[i]);
		while (pos != string::npos) {
			found++;
			txt.replace(pos, croa[i].length(), ".");
			pos = txt.find(croa[i]);
		}
	}
	for (unsigned int i = 0; i < txt.length(); i++)
		if (txt[i] != '.') found++;
	
	cout << found << "\n";
}
