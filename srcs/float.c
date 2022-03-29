/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:39:10 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/29 19:04:24 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_f(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char))
{
	long double		nb;
	struct			s_float data;
	uint32_t		tmp;

	nb = 0;
	(void)p_flag;
	(void)f;
	(void)data;
	(void)ap;
	if (f->length[L])
		nb = va_arg(*ap, long double);
	else
		nb = va_arg(*ap, double);
	tmp = nb;
	printf("nb = %Lf\n", nb);
	printf("nb\t: ");
	test_printbitc(nb);
	printf("tmp\t: ");
	test_printbitc(tmp);
	if (f->sign && nb >= 0)
		f->prefix = "+";
//	test_print_format(f);
//	(void)p_flag;
}
/*
struct s_ifloat store_ifloat(float num)
{

    memcpy(&mem, &num, sizeof(uint32_t));
    ifloat.sign = mem >> 31;
    ifloat.exp = mem >> 23;
    ifloat.frac = mem << 9;
    return (ifloat);
}
*/
