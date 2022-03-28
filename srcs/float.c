/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:39:10 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/28 23:11:53 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_f(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char))
{
	long double nb;

	nb = 0;
	if (f->length[L])
		nb = va_arg(*ap, long double);
	else
		nb = va_arg(*ap, double);
	(void)p_flag;
	(void)f;
	if (f->sign && nb >= 0)
		f->prefix = "+";
//	test_print_format(f);
//	(void)p_flag;

}
