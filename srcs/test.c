/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:44 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/28 23:12:19 by itkimura         ###   ########.fr       */
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
	printf("f->extra_flag[SHARP] = %d\n", f->extra_flag[SHARP]);
	printf("f->extra_flag[SPACE] = %d\n", f->extra_flag[SPACE]);
}
