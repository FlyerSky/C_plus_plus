// strlen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <assert.h>
#include <iostream>
using namespace std;

int getStrlen1(const char* src){
	assert(NULL != src);
	int len = 0;
	while (*src++ != '\0'){
		++len;
	}
	return len;
}

int getStrlen2(const char* src){
	assert(NULL != src);
	const char* temp = src;
	while (*src++ != '\0');
	return (src - temp - 1); // 注意：这里需要减1
}

int _tmain(int argc, _TCHAR* argv[])
{
	char p[] = "Hello,World!";
	printf("getStrlen1 len:%d\n", getStrlen1(p));
	printf("getStrlen2 len:%d\n", getStrlen2(p));
	system("pause");
	return 0;
}