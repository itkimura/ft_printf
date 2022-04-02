/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:39:10 by itkimura          #+#    #+#             */
/*   Updated: 2022/04/02 12:54:18 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	float_initialize(t_float *data)
{
	data->dot = 0;
	data->frac_len = 0;
	data->sign = 0;
	data->exp = 0;
	data->frac = 0;
	ft_memset(data->intpart, 0, sizeof(data->intpart));
	ft_memset(data->fracpart, 0, sizeof(data->fracpart));
}

void	float_flag(t_format *f, t_float *data)
{
//	printf("data->sign = %d\nf->sharp = %d\nf->sign = %d\n", data->sign, f->sharp, f->sign);
	if (data->sign == 1)
	{
		f->prefix = "-";
		f->sign = 1;
		f->space_flag = 0;
	}
	if (f->sign == 1 && data->sign == 0)
		f->prefix = "+";
	f->basestr = "01234567890";
}

void	float_len(t_format *f, t_float *data)
{
//	test_print_format(f);
	while (data->intpart[data->dot] == 0 && data->dot < 53)
		data->dot++;
	if (data->dot == 53)
		data->dot = 1;
	else
		data->dot = 53 - data->dot;
	if (f->precision == INIT || f->precision == INVALID)
		data->frac_len = 7;
	else if (f->precision != 0 && f->precision != DOT_ONLY)
		data->frac_len = f->precision + 1;
	else if ((f->precision == DOT_ONLY || f->precision == 0) && f->sharp)
		data->frac_len = 1;
	else
		data->frac_len = 0;
//	printf("args_len = %d\n", f->args_len);
}

void	float_format(t_format *f, t_float *data)
{
	float_len(f, data);
	float_flag(f, data);
	f->args_len = data->dot + data->frac_len;
//	test_print_format(f);
//	test_print_float(data, 0.0);
	if (f->args_len < f->width)
	{
		f->space = f->width - f->args_len - f->zero - f->sign;
		if (f->flag == ZERO)
		{
			f->zero = f->space - f->space_flag;
			f->space = 0;
		}
	}
	if (f->space_flag && f->space == 0 && f->sign == 0)
		f->space++;
}
void	print_f(t_format *f, t_float *data, void (*p_flag[])(t_format *, char), long double nb)
{
	int			i;
	long double	tmp;
	int			frac;
	int			roundup;
	char		c;
/*
	for(int i = 0; i < 53; i++)
		printf("%d", data->fracpart[i]);
*/
	i = 0;
	tmp = (nb - (int64_t)nb) * 10;
	if (tmp < 0)
		tmp *= -1;
//	test_print_format(f);
	while (i < data->dot + data->frac_len + 1)
	{
//		printf("\ni = %d result = ", i);
		if (i < data->dot)
		{
			c = f->basestr[data->intpart[53 - data->dot + i]];
		}
		else if (i == data->dot)
			c = '.';
		else if (data->frac_len)
		{
			tmp = (tmp - (int)tmp) * 10;
			frac = data->fracpart[i - data->dot - 1];
			roundup = data->fracpart[i - data->dot];
//			printf("\ntmp = %Lf\troundup = %d frac = %d ", tmp, roundup, frac);
//			if (tmp > 9 || tmp < 1)
//				printf("tmp = Yes");
			if (roundup >= 5 && (tmp > 9 || tmp < 1) && f->precision != INIT
				&& f->sharp != 1)
//				f->precision == INIT) || i == data->dot + data->frac_len))
				frac++;
//			printf("frac = %d p_flag = ", frac);
			c = f->basestr[frac];
		}
		p_flag[f->flag](f, c);
		i++;
	}
	(void)p_flag;
}

void	put_f(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char))
{
	long double		nb;
	t_float			data;
	uint64_t		tmp;

	nb = 0;
	float_initialize(&data);
		nb = va_arg(*ap, long double);
	ft_memcpy(&tmp, &nb, sizeof(uint64_t));
	data.sign = tmp >> 63;
	data.exp = tmp >> 52;
	data.frac = tmp << 12;
	tbit(tmp, "tmp");
	if (data.sign == 1)
		data.exp = data.exp ^ (1 << 11);
	convert_intpart(&data);
	convert_fracpart(&data, tmp);
	float_format(f, &data);
	print_f(f, &data, p_flag, nb);

}
