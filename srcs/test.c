/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:44 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/29 19:04:26 by itkimura         ###   ########.fr       */
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

void	test_printbitc(uint32_t	c)
{
	uint32_t	bit;
	int			i;

	i = 0;
	bit = 1 << 31;
	while (bit != 0)
	{
		if (c & bit)
			putchar('1');
		else
			putchar('0');
		bit >>= 1;
		i++;
		if (i == 1 || i == 8)
			putchar(' ');
	}
	putchar('\n');
}
