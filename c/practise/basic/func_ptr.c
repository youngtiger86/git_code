#include <stdio.h>

typedef int (*calc)(int a, int b);

int add(int m, int n)
{
	return (m + n);
}

int main()
{
	int result;

	calc func;
	func = add;

	result = func(1, 2);
	printf("%d\n", result);

	return 0;	
}
