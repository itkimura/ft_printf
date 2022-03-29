/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:44 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/29 23:47:04 by itkimura         ###   ########.fr       */
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

union IntAndFloat {
	int i;
	long double f;
};

void	test_printbitc(long double	c)
{
	int i;
	union IntAndFloat target;

	i = 0;
	target.f = c;
	printf("target.f = %Lf\n", target.f);
	target.f = target.f << 1;
	printf("target.f = %Lf\n", target.f);
	while (i < 64)
	{
		if ((target.i & ) == 0x3FEFFFFFFFFFFFFF)
			putchar('1');
		else
			putchar('0');
		if (i == 1 || i == 11)
			putchar(' ');
		target.i = target.i << 1;
		i++;
	}
	putchar('\n');
	(void)c;
}
