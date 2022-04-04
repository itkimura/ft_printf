/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_rounding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:39:10 by itkimura          #+#    #+#             */
/*   Updated: 2022/04/04 22:41:51 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_round(t_float *data)
{
	int		i;
	int		res;
	int		start;
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
	res = 0;
	if (data->frac_len == 0)
		start = 0;
	else
		start = data->frac_len - 1;
//	printf("start = %d\n", start);
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

void	round_check(int i, char *str, int *flag)
{
	int	j;

	if (str[i + 1] == '9' && str[i] != '9')
	{
		j = i + 1;
		while (str[j] == '9')
			str[j++] = '0';
		*flag = 0;
	}
	if (str[i] != '9')
	{
		str[i]++;
		*flag = 0;
	}
}

void	rounding(char *str, int round)
{
	int	i;
	int	flag;

	i = ft_strlen(str);
	flag = 1;
//	printf("str = %s ", str);
//	printf("round = %d\n", round);
	while (i >= 0)
	{
		if (str[i + 1] >= '5' && flag
			&& ((round == 2 && ((str[i] - '0') % 2) == 1) || (round == 1)))
			round_check(i, str, &flag);
		if (str[i + 1] >= '5' && round == 2 && ((str[i] - '0') % 2) == 0)
			break ;
		i--;
	}
}

void	print_floatstr(t_format *f, t_float *data,
		char *str, void (*p_flag[])(t_format *, char))
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
	i = f->args_len;
	str[0] = '0';
	while (i >= 0)
	{
		if (i > data->dot)
			str[i] = data->fracpart[i - (data->dot + 1)] + '0';
		else
			str[i] = data->intpart[52 - (data->dot - i)] + '0';
		i--;
	}
	rounding(str, is_round(data));
	print_floatstr(f, data, str, p_flag);
	free(str);
}
