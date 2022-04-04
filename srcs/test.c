/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:44 by itkimura          #+#    #+#             */
/*   Updated: 2022/04/04 11:32:22 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	test_print_format(t_format *f)
{
	printf("\nf->flag = %d\n", f->flag);
	printf("f->width = %d\n", f->width);
	printf("f->type = %d\n", f->type);
	printf("f->precision = %d\n", f->precision);
	printf("f->args_len = %d\n", f->args_len);
	printf("f->zero = %d\n", f->zero);
	printf("f->space = %d\n", f->space);
	printf("f->base = %d\n", f->base);
	printf("f->basestr = %s\n", f->basestr);
	printf("f->res = %d\n", f->res);
	printf("f->prefix = [%s]\n", f->prefix);
	printf("====flag====\n");
	printf("f->sign = %d\n", f->sign);
	printf("f->sharp = %d\n", f->sharp);
	printf("f->space_flag = %d\n", f->space_flag);
}

#include <float.h>

void	tbit(uint64_t	c, char *str)
{
	uint64_t	bit;
	int			i;

	i = 0;
	bit = 1L << 63;
	printf("%s\t: ", str);
	while (bit != 0)
	{
		if (c & bit)
			putchar('1');
		else
			putchar('0');
		bit >>= 1;
		i++;
		if (i == 1 || i == 12)
			putchar(' ');
	}
	putchar('\n');
}

void	test_print_float(t_float *data, long double nb)
{
	uint64_t	bit;
	uint64_t	tmp;
	int			i;
	int			j;
	int			len;

	i = 0;
	len = 0;
	printf("nb = %Lf\n", nb);
	while (i < 3)
	{
		bit = 0;
		if (i == 0)
		{
			len = 8;
			bit = 1 << 7;
			printf("data->sign\t: ");
			tmp = (uint64_t)data->sign;
		}
		else if (i == 1)
		{
			len = 32;
			bit = 1L << 31;
			printf("data->exp\t: ");
			tmp = (uint64_t)data->exp;
		}
		else
		{
			len = 64;
			bit = 1L << 63;
			printf("data->frac\t: ");
			tmp = data->frac;
		}
		j = 0;
		while (j < len)
		{
			if (tmp & bit)
				putchar('1');
			else
				putchar('0');
			bit >>= 1;
			j++;
			if ((i == 1 && (j % 21 == 0 || j % 24 == 0 || j % 28 == 0)) ||
				(i == 2 && j % 4 == 0)) 
				putchar(' ');
		}
		putchar('\n');
		i++;
	}
	printf("data->sign = %d\n", data->sign);
	printf("data->frac = %llu\n", data->frac);
	printf("data->exp = %d\n", data->exp);
	printf("data->dot = %d\n", data->dot);
	printf("data->frac_len = %d\n", data->frac_len);
		printf("int\t: ");
	for(int i = 0; i < 53; i++)
		printf("%d", data->intpart[i]);
	printf("\nfrac\t: ");
	for(int i = 0; i < 53; i++)
		printf("%d", data->fracpart[i]);
}
