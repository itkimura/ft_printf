#include <stdio.h>
#include "ft_printf.h"

int	main(void)
{
	ft_printf("{%f}{%lf}{%Lf}\n", 1.42, 1.42, 1.42l);
	printf("{%f}{%lf}{%Lf}\n", 1.42, 1.42, 1.42l);
	return (0);
}
