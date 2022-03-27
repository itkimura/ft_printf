/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_and_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 21:43:45 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/27 22:53:38 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_width(char **itr, t_format *f, va_list *ap)
{
	int	nb;

	nb = 0;
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
	while (ft_isspace(**itr))
		(*itr)++;
	if (**itr >= '0' && **itr <= '9')
	{
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
	if (**itr >= '0' && **itr <= '9')
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
	if (ft_strstr(*itr, "hh"))
	{
		f->length[hh] = 1;
		(*itr) += 2;
	}
	else if (ft_strstr(*itr, "ll"))
	{
		f->length[ll] = 1;
		(*itr) += 2;
	}
	else if ((i = is_specifier(itr, LEN)) > 0)
	{
		f->length[i] = 1;
		(*itr)++;
	}
}
