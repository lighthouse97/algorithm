// 11718.cpp

#include "pch.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
	char buf[101];

	while (fgets(buf, 101, stdin))
	{
		cout << buf;
	}
}