// 1316.cpp

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
	
	int N;
	int check = 0, sum = 0;
	string word, temps;
	vector<string> wordlist;

	cin >> N;
	if (N > 0 && N <= 100) {
		for (int i = 0; i < N; i++) {
			cin >> word;
			wordlist.push_back(word);
		}
		for (int i = 0; i < N; i++) {
			temps = wordlist.at(i);
			check = 0;
			for (unsigned int j = 0; j < temps.size(); j++) {
				for (unsigned int k = j + 1; k < temps.size(); k++) {
					if ((temps[j] == temps[k]) && (temps[k - 1] != temps[k])) {
						check++;
						break;
					}
				}
				if (check > 0) break;
			}
			if (check == 0) sum++;
		}
		cout << sum << "\n";
	}
}