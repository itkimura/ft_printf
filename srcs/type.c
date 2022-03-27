/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 21:37:47 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/28 01:00:38 by itkimura         ###   ########.fr       */
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
	printf("f->res = %d\n\n", f->res);
}

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
	if (f->args_len == 0)
		p_flag[f->flag](f, 0);
	while (f->args_len)
	{
		p_flag[f->flag](f, *s);
		s++;
	}
}

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

void	nbr_data(t_format *f, unsigned long long nb)
{
	if (f->precision == -1 && nb == 0)
		f->args_len = 1;
	else
		f->args_len = get_digits(nb, f->base);
	if (f->args_len < f->precision)
		f->zero = f->precision - f->args_len;
	if (f->args_len + f->zero < f->width)
	{
		f->space = f->width - f->args_len - f->zero;
		if (f->extra_flag[PLUS] || ft_strcmp(f->prefix, "-") == 0 ||
			(f->extra_flag[SHARP] == 1 && f->type == TYPE_O))
			f->space--;
		if (f->extra_flag[SHARP] == 1 && (f->type == TYPE_SX || f->type == TYPE_LX ||
			f->type == TYPE_P))
			f->space -= 2;
		if (f->flag == ZERO && f->zero == 0)
		{
			f->zero = f->space;
			if (f->precision == -1)
				f->space = 0;
		}
	}
	if (f->type == TYPE_D && f->extra_flag[SPACE] && f->space == 0 &&
		ft_strcmp(f->prefix, "-") && ft_strcmp(f->prefix, "+"))
		f->space++;
}

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
	if ((f->extra_flag[SHARP] == 1 && f->type == TYPE_SX && nb != 0) || f->type == TYPE_P)
		f->prefix = "0x";
	if (f->extra_flag[SHARP] == 1 && f->type == TYPE_LX)
			f->prefix = "0X";
	if (f->extra_flag[SHARP] == 1 && f->type == TYPE_O)
			f->prefix = "0";
}

void	print_di(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char))
{
	unsigned long long	nb;
	long			tmp_nb;
	signed char		tmp_h;

	nb = 0;
	tmp_nb = 0;
	tmp_h = 0;
	tmp_nb = (int)va_arg(*ap, int);
	if ((f->length[h] || f->length[hh]) && tmp_nb < 32767)
	{
		tmp_h = (signed char)tmp_nb;
		if (tmp_h > 0 && f->length[h])
			f->prefix = "-";
		nb = tmp_h;
	}
	else if (tmp_nb < 0)
	{
		f->prefix = "-";
		nb = tmp_nb * -1;
	}
	else
		nb = tmp_nb;
	if (f->length[h] && tmp_nb > 32767)
		f->prefix = "-";
	if (f->extra_flag[PLUS] && nb >= 0 && tmp_nb >= 0)
		f->prefix = "+";
	set_base(f, nb);
	nbr_data(f, nb);
//	test_print_format(f);
//	(void)p_flag;
	nb_recursive(nb, f, p_flag);
}

void	print_nbr(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char))
{
	unsigned long long	nb;
	long				tmp_nb = 0;

	nb = 0;
	if (f->type == TYPE_SX || f->type == TYPE_LX || f->type == TYPE_U || f->type == TYPE_O)
	{
		tmp_nb = (long)va_arg(*ap, long);
		if (tmp_nb < 0 || f->length[h] || (tmp_nb >= 4294967296 && f->length[l] == 0 && f->length[ll] == 0))
			nb = (unsigned int)tmp_nb;
		else
			nb = tmp_nb;
	}
	if (f->type == TYPE_P)
		nb = (unsigned long long)va_arg(*ap, unsigned long long);
	if (f->extra_flag[PLUS] && nb >= 0 && tmp_nb >= 0 &&
		f->type != TYPE_P && f->type != TYPE_U)
		f->prefix = "+";
	set_base(f, nb);
	nbr_data(f, nb);
//	test_print_format(f);
//	(void)p_flag;
	nb_recursive(nb, f, p_flag);
}
