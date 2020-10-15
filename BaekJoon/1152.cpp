// 1152.cpp

#include "pch.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <cstdio>
#include <cstring> // strtok
#include <vector>
#include <string>

using namespace std;

int main()
{
	char str[1000000];
	char* token;
	vector<string> token_list;

	for (int i = 0; i < 1000000; i++)
		str[i] = 0;

	if (fgets(str, 1000000, stdin) != NULL) {
		token = strtok(str, " ");
		while (token != NULL) {
			if(token[0] != '\n') token_list.push_back(token);
			token = strtok(NULL, " ");
		}
		printf("%d\n", token_list.size());
	}
}