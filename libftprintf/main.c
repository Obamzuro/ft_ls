#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"
#include <locale.h>

int main(void)
{
	int a;
	int b;

	setlocale(LC_ALL, "");
	a = printf("%5%\n");
	b = ft_printf("%5%\n");
	printf("a = %d, b = %d", a, b);
}
