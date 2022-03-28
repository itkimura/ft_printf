/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 22:29:48 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/28 12:31:57 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	initialize_int_array(int *array, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		array[i] = 0;
		i++;
	}
}
void	initialize_format(t_format *f)
{
	f->flag = NONE;
	f->width = INIT;
	f->type = INIT;
	f->precision = INIT;
	f->args_len = 0;
	f->zero = 0;
	f->space = 0;
	f->base = 0;
	f->res = 0;
	initialize_int_array(f->extra_flag, EXTRA_NUM);
	initialize_int_array(f->length, LEN_NUM);
	f->prefix = "";
	f->basestr = "0123456789ABCDEF";
}

int	get_digits(unsigned long long nb, int base)
{
	int	digits;

	digits = 0;
	while (nb)
	{
		digits++;
		nb /= base;
	}
	return (digits);
}

int	is_specifier(char **itr, char *str)
{
	int		i;
	char	c;

	i = 0;
	c = **itr;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	print_format(t_format *f, va_list *ap)
{
	void	(*p_type[TYPE_NUM])(t_format *, va_list *,
			void (*p_flag[])(t_format *, char));
	void	(*p_flag[FLAG_NUM])(t_format *, char);

	p_type[TYPE_C] = print_c;
	p_type[TYPE_S] = print_s;
	p_type[TYPE_P] = print_nbr;
	p_type[TYPE_D] = print_nbr;
	p_type[TYPE_O] = print_nbr;
	p_type[TYPE_I] = print_nbr;
	p_type[TYPE_U] = print_nbr;
	p_type[TYPE_LX] = print_nbr;
	p_type[TYPE_SX] = print_nbr;
	p_type[TYPE_PER] = print_c;
	p_flag[NONE] = flag_none;
	p_flag[MINUS] = flag_minus;
	p_flag[ZERO] = flag_none;
	p_type[f->type](f, ap, p_flag);
}

void	put_flag(t_format *f, char **itr)
{
	while (**itr == '0' || **itr == '-' || **itr == '+' ||
			**itr == '#' || **itr == ' ')
	{
		if (**itr == '0' && f->flag != MINUS)
			f->flag = ZERO;
		if (**itr == '-')
			f->flag = MINUS;
		if (**itr == '+')
			f->extra_flag[PLUS] = 1;
		if (**itr == '#')
			f->extra_flag[SHARP] = 1;
		if (**itr == ' ')
			f->extra_flag[SPACE] = 1;
		(*itr)++;
	}
}

int	read_percentage(t_format *f, char **itr, va_list *ap)
{
	char **start;
	start = itr;
	initialize_format(f);
	put_flag(f, itr);
	put_width(itr, f, ap);
	if (**itr == '.')
		put_precision(itr, f, ap);
	put_length(itr, f);
	f->type = is_specifier(itr, TYPE);
	if (f->type == -1)
		return (0);
	else
		(*itr)++;
	print_format(f, ap);
	return (f->res);
}

/*
 * va_start and va_end
 * A function may be called with a varying number of arguments of varying types
 * va_start -> initializes ap
 * va_args -> for each agument to be processed
 * va_end -> signals that there are no further arguments
*/

int	ft_printf(const char *format, ...)
{
	char		*itr;
	int			res;
	va_list		ap;
	t_format	f;

	itr = (char *)format;
	if (!itr)
		return (0);
	res = 0;
	va_start(ap, format);
	while (*itr)
	{
		if (*itr == '%' && *++itr != '%')
		{
			res += read_percentage(&f, &itr, &ap);
			continue ;
		}
		res += int_putchar(*itr);
		itr++;
	}
	va_end(ap);
//	if (res == -1)
//		return (0);
	return (res);
}
