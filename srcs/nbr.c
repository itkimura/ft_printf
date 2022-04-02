/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 21:37:47 by itkimura          #+#    #+#             */
/*   Updated: 2022/04/01 10:21:42 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	nb_recursive(unsigned long long nb, t_format *f,
		void (*p_flag[])(t_format *, char))
{
	if (nb >= (unsigned long long)f->base)
	{
		nb_recursive(nb / f->base, f, p_flag);
		nb_recursive(nb % f->base, f, p_flag);
	}
	else
		p_flag[f->flag](f, f->basestr[nb]);
}

void	set_format(t_format *f, unsigned long long nb)
{
	if (f->type == TYPE_O && f->sharp && nb == 0)
		f->args_len = 1;
	else if (f->precision == -1 && nb == 0)
		f->args_len = 1;
	else
		f->args_len = get_digits(nb, f->base);
	if (f->args_len < f->precision)
		f->zero = f->precision - f->args_len;
	if (f->args_len + f->zero < f->width)
	{
		f->space = f->width - f->args_len - f->zero - f->sign - f->sharp;
		if (f->flag == ZERO && f->zero == 0 && (f->precision == -1 || f->precision == INVALID))
		{
			f->zero = f->space - f->space_flag;
			f->space = 0;
		}
	}
	if ((f->type == TYPE_D || f->type == TYPE_I)
		&& (f->space_flag && f->space == 0 && f->sign == 0))
		f->space++;
	if (f->sharp && f->type == TYPE_O && f->flag != ZERO && f->zero)
		f->zero--;
}

long long	get_signed(t_format *f, va_list *ap)
{
	f->sharp = 0;
	if (f->length[ll])
		return (va_arg(*ap, long long));
	if (f->length[l])
		return (va_arg(*ap, long));
	if (f->length[h])
		return ((short)va_arg(*ap, int));
	if (f->length[hh])
		return ((char)va_arg(*ap, int));
	else
		return (va_arg(*ap, int));
	return (0);
}

unsigned long long	get_unsigned(t_format *f, va_list *ap)
{
	f->sign = 0;
	if (f->length[ll])
		return (va_arg(*ap, unsigned long long));
	else if (f->length[l])
		return (va_arg(*ap, unsigned long));
	else if (f->length[h])
		return ((unsigned short)va_arg(*ap, int));
	else if (f->length[hh])
		return ((unsigned char)va_arg(*ap, int));
	else if (f->type == TYPE_P)
		return ((unsigned long) va_arg(*ap, unsigned long));
	else
		return ((unsigned) va_arg(*ap, unsigned int));
	return (0);
}

void	put_nbr(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char))
{
	unsigned long long	nb;
	long long			tmp_nb;

	nb = 0;
	tmp_nb = 0;
	if (f->type == TYPE_D || f->type == TYPE_I)
	{
		tmp_nb = get_signed(f, ap);
		if (tmp_nb < 0)
		{
			f->prefix = "-";
			f->sign = 1;
			nb = tmp_nb * -1;
		}
		else
			nb = tmp_nb;
		if (f->sign && nb >= 0 && tmp_nb >= 0)
		f->prefix = "+";
	}
	else
		nb = get_unsigned(f, ap);
	set_base(f, nb);
	set_format(f, nb);
	nb_recursive(nb, f, p_flag);
}
