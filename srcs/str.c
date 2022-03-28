/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 21:37:47 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/28 23:52:16 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_c(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char))
{
	unsigned char	c;

	if (f->type == TYPE_C)
		c = (unsigned char)va_arg(*ap, int);
	if (f->type == TYPE_PER)
		c = '%';
	f->args_len = 1;
	if (f->args_len < f->width)
		f->space = f->width - f->args_len;
	if (f->flag == ZERO)
	{
		f->zero = f->space;
		f->space = 0;
	}
	p_flag[f->flag](f, c);
}

void	print_s(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char))
{
	char	*s;

	s = (char *)va_arg(*ap, char *);
	if (s == 0)
		s = "(null)";
	if (f->precision == DOT_ONLY)
		f->precision = 0;
	f->args_len = ft_strlen(s);
	if (f->precision < f->args_len && f->precision >= 0)
		f->args_len = f->precision;
	if (f->args_len < f->width)
		f->space = f->width - f->args_len;
	if (f->flag == ZERO)
	{
		f->zero = f->space;
		f->space = 0;
	}
	if (f->args_len == 0)
		p_flag[f->flag](f, 0);
	while (f->args_len)
	{
		p_flag[f->flag](f, *s);
		s++;
	}
}
