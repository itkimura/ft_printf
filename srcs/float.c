/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:39:10 by itkimura          #+#    #+#             */
/*   Updated: 2022/04/04 01:48:12 by itkimura         ###   ########.fr       */
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

int		is_round(t_float *data, t_format *f)
{
	int		i;
	int		res;
	int		start;
//	printf("data->fracpart\t: ");
//	for (int i = 0; i < 100; i++)
//		printf("%d", data->fracpart[i]);
//	printf("\n");
	(void)f;
	res = 0;
	if (data->frac_len == 0)
		start = 0;
	else
		start = data->frac_len - 1;
//	printf("data->fracpart[%d] = %d\n", start, data->fracpart[start]);
	if (data->fracpart[start] >= 5)
	{
		i = start;
		while (i < 1077)
		{
			if (data->fracpart[i])
				res = 1;
			i++;
		}
	}
	if (data->fracpart[start] == 5)
	{
		i = start + 1;
		while (data->fracpart[i] == 0)
			i++;
		if (i == 1077)
			res = 2;
	}
	return (res);
}

void	print_f(t_format *f, t_float *data, void (*p_flag[])(t_format *, char), uint64_t tmp)
{
	int			round;
	int			len;
	char		*str;
	int			flag;
	int			i;
	/*
	printf("data->fracpart\t: ");
	for(int i = 0; i < 53; i++)
		printf("%d", data->fracpart[i]);
	printf("\n");
	printf("data->intpart\t: ");
	for(int i = 0; i < 53; i++)
		printf("%d", data->intpart[i]);
	printf("\n");
*/
//	printf("f->args_len = %d\n", f->args_len);
//	printf("data->dot = %d\n", data->dot);
	if (f->args_len < 4)
		len = 4;
	else
		len = f->args_len + 1;
	str = ft_strnew(len);
	i = len;
	round = is_round(data, f);
	flag = 1;
	//printf("round = %d\n", round);
//	for (int i = 0 ; i < f->args_len; i++)
//		str[i] = '0';
//	printf("str = %s\n", str);
	str[0] = '0';
	while (i >= 0)
	{
		if (i > data->dot)
			str[i] = data->fracpart[i - (data->dot + 1)] + '0';
		else
			str[i] = data->intpart[52 - (data->dot - i)] + '0';
/*
				printf("flag = %d ", flag);
				printf("i = %d ", i);
				printf("str[i] = %c ", str[i]);
				printf("str[i + 1] = %c\n", str[i + 1]);
*/
		if (str[i + 1] >= '5' && flag && ((round == 2 && ((str[i] - '0') % 2) == 1) || (round == 1)))
		{
			if (str[i + 1] == '9' && str[i] != '9')
			{
				str[i]++;
				flag = 1;
				while (str[flag] == '9')
				{
					str[flag] = '0';
					flag++;
				}
			}
			else if (str[i] != '9')
				str[i]++;
			if (str[i] < '5')
				flag = 0;
		}
		i--;
	}
	//printf("str = %s\n", str);
	len = f->args_len + 1;
	if (str[0] != '0')
	{
		i = 0;
		f->args_len++;
		len++;
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
	free(str);
	(void)tmp;
	(void)p_flag;
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
//	tbit(tmp, "\ntmp\t");
	if (is_longmax(tmp))
		print_s(f, "nan", p_flag);
	else
	{
		if (data.sign == 1)
			data.exp = data.exp ^ (1 << 11);
		convert_intpart(&data);
		convert_fracpart(&data);
		float_format(f, &data);
		print_f(f, &data, p_flag, tmp);
	}

}
