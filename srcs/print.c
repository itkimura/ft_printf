/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 21:27:29 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/28 23:50:12 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_base(t_format *f, unsigned long long nb)
{
	if (f->type == TYPE_O)
		f->base = 8;
	if (f->type == TYPE_D || f->type == TYPE_I || f->type == TYPE_U)
		f->base = 10;
	if (f->type == TYPE_SX || f->type == TYPE_LX || f->type == TYPE_P)
		f->base = 16;
	if (f->type == TYPE_SX || f->type == TYPE_P)
		f->basestr = "0123456789abcdef";
	if (f->sharp || f->type == TYPE_P)
	{
		if ((f->type == TYPE_SX && nb != 0) || f->type == TYPE_P)
			f->prefix = "0x";
		if (f->type == TYPE_LX && nb != 0)
			f->prefix = "0X";
		f->sharp = 2;
	}
	if (f->sharp && f->type == TYPE_O && nb != 0)
	{
		f->prefix = "0";
		f->sharp = 1;
	}
}

int	int_putchar(char c)
{
	return (write(1, &c, 1));
}

void	flag_none(t_format *f, char c)
{
	while (f->space)
	{
		f->res += int_putchar(' ');
		f->space--;
	}
	while (*(f->prefix) && f->type != TYPE_S)
	{
		f->res += int_putchar(*f->prefix);
		f->prefix++;
	}
	while (f->zero)
	{
		f->res += int_putchar('0');
		f->zero--;
	}
	if (f->args_len)
	{
		f->res += int_putchar(c);
		f->args_len--;
	}
}

void	flag_minus(t_format *f, char c)
{
	while (*(f->prefix))
	{
		f->res += int_putchar(*f->prefix);
		f->prefix++;
	}
	while (f->zero)
	{
		f->res += int_putchar('0');
		f->zero--;
	}
	if (f->args_len)
	{
		f->res += int_putchar(c);
		f->args_len--;
	}
	while (f->space && !f->args_len)
	{
		f->res += int_putchar(' ');
		f->space--;
	}
}
