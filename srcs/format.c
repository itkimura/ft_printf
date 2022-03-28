/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_and_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 21:43:45 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/28 16:49:22 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_width(char **itr, t_format *f, va_list *ap)
{
	int	nb;

	while (ft_isspace(**itr))
		(*itr)++;
	if (**itr == '*')
	{
		nb = va_arg(*ap, int);
		if (nb < 0)
		{
			nb *= -1;
			f->flag = MINUS;
		}
		f->width = nb;
		(*itr)++;
	}
	if (**itr >= '0' && **itr <= '9')
	{
		nb = 0;
		while (**itr >= '0' && **itr <= '9')
		{
			nb = nb * 10 + (**itr - '0');
			(*itr)++;
		}
		f->width = nb;
	}
}

void	put_precision(char **itr, t_format *f, va_list *ap)
{
	int	nb;

	nb = 0;
	(*itr)++;
	if (**itr == '*')
	{
		nb = va_arg(*ap, int);
		if (nb < 0)
			nb = INVALID;
		(*itr)++;
		f->precision = nb;
	}
	else if (**itr >= '0' && **itr <= '9')
	{
		while (**itr >= '0' && **itr <= '9')
		{
			nb = nb * 10 + (**itr - '0');
			(*itr)++;
		}
		f->precision = nb;
	}
	else
		f->precision = DOT_ONLY;
}

void	put_length(char **itr, t_format *f)
{
	int	i;

	i = 0;
	if (ft_strnstr(*itr, "hh", 2))
	{
		f->length[hh] = 1;
		(*itr) += 2;
	}
	else if (ft_strnstr(*itr, "ll", 2))
	{
		f->length[ll] = 1;
		(*itr) += 2;
	}
	else
	{
		i = is_specifier(itr, LEN);
		if (i > 0)
		{
			f->length[i] = 1;
			(*itr)++;
		}
	}
}
