// Lab_9.cpp : Defines the entry point for the console application.
//
#include <conio.h>
#include "stdafx.h"

namespace x{
	int n = 10;
}

namespace y{
	int n = 20;
}
int main()
{
	bool way = true;
	int n = 100;
	{
		if (way) using namespace x;
		else using namespace y;
		printf("%d\n", n);
	
	}

//	_getch();
	printf("%d", n);
	_getch();
    return 0;
}

