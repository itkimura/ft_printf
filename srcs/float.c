/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:39:10 by itkimura          #+#    #+#             */
/*   Updated: 2022/04/04 19:29:46 by itkimura         ###   ########.fr       */
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
	if (data->sign == 1)
	{
		f->prefix = "-";
		f->sign = 1;
		f->space_flag = 0;
	}
	if (f->sign == 1 && data->sign == 0)
		f->prefix = "+";
}

void	float_len(t_format *f, t_float *data)
{
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
}

void	float_format(t_format *f, t_float *data)
{
	float_len(f, data);
	float_flag(f, data);
	f->args_len = data->dot + data->frac_len;
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

int		is_round(t_float *data)
{
	int		i;
	int		res;
	int		start;

	res = 0;
	if (data->frac_len == 0)
		start = 0;
	else
		start = data->frac_len - 1;
	if (data->fracpart[start] > 5)
		return (1);
	if (data->fracpart[start] == 5)
	{
		i = start + 1;
		while (data->fracpart[i] == 0 && i < 1077)
			i++;
		if (i == 1077)
			res = 2;
		else
			res = 1;
	}
	return (res);
}


void	rounding(t_float *data, char *str, int len, int round)
{
	int	i;
	int	j;
	int	flag;

	i = len - 2;
	flag = 1;
	while (i >= 0)
	{
		if (str[i + 1] >= '5' && flag
			&& ((round == 2 && ((str[i] - '0') % 2) == 1) || (round == 1)))
		{
			if (str[i + 1] == '9' && str[i] != '9')
			{
				j = i + 1;
				while (str[j] == '9')
					str[j++] = '0';
				flag = 0;
			}
			if (str[i] != '9')
			{
				str[i]++;
				flag = 0;
			}
		}
		if (str[i + 1] >= '5' && round == 2 && ((str[i] - '0') % 2) == 0)
			break ;
		i--;
	}
	(void)data;
	(void)str;
}


void	print_floatstr(t_format *f, t_float *data, char *str, void (*p_flag[])(t_format *, char))
{
	int		len;
	int		i;

	len = f->args_len + 1;
	if (str[0] != '0')
	{
		i = 0;
		f->args_len++;
		len++;
		if (f->space)
			f->space--;
		else if (f->flag == ZERO && f->zero)
			f->zero--;
	}
	else
		i = 1;
	while (i < len)
	{
		p_flag[f->flag](f, str[i]);
		if (i == data->dot)
			p_flag[f->flag](f, '.');
		i++;
	}
}

void	print_f(t_format *f, t_float *data, void (*p_flag[])(t_format *, char))
{
	int			len;
	char		*str;
	int			i;

	if (f->args_len < 4)
		len = 4;
	else
		len = f->args_len + 1;
	str = ft_strnew(len);
	i = len;
	str[0] = '0';
	while (i >= 0)
	{
		if (i > data->dot)
			str[i] = data->fracpart[i - (data->dot + 1)] + '0';
		else
			str[i] = data->intpart[52 - (data->dot - i)] + '0';
		i--;
	}
	rounding(data, str, len, is_round(data)); 
	print_floatstr(f, data, str, p_flag);
	free(str);
}

int	is_longmax(uint64_t tmp)
{
	uint64_t	bit;
	int			i;

	i = 0;
	bit = 1L << 63;
	while (bit != 0)
	{
		if (tmp & bit)
			i++;
		else
			break ;
		bit >>= 1;
	}
	if (i == 64)
		return (1);
	else
		return (0);
}



void	put_f(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char))
{
	double		nb;
	long double		longnb;
	t_float			data;
	uint64_t		tmp;

	nb = 0;
	tmp = 0;
	float_initialize(&data);
	if (f->length[L])
	{
		longnb = va_arg(*ap,long double);
		nb = (double)longnb;
	}
	else
		nb = va_arg(*ap, double);
	memcpy(&tmp, &nb, sizeof(uint64_t));
	data.sign = tmp >> 63;
	data.exp = tmp >> 52;
	data.frac = tmp << 12;
	if (is_longmax(tmp))
		print_s(f, "nan", p_flag);
	else if (data.exp == 2047 && data.frac == 0)
	{
		if (f->flag == ZERO)
			f->flag = NONE;
		print_s(f, "inf", p_flag);
	}
	else
	{
		if (data.sign == 1)
			data.exp = data.exp ^ (1 << 11);
		convert_intpart(&data);
		convert_fracpart(&data);
		float_format(f, &data);
		print_f(f, &data, p_flag);
	}

}
