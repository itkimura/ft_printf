/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 22:29:48 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/21 00:20:23 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*
void	print_args(t_args *args)
{
	printf("args->c = %c\n", args->c);
	printf("args->width = %d\n", args->width);
	printf("args->has_width = %d\n", args->has_width);
	printf("args->precision = %d\n", args->precision);
	printf("args->has_precision = %d\n", args->has_precision);
}
*/
void	initialize_args(t_args *args)
{
	args->c = INIT;
	args->precision = INIT;
	args->width = INIT;
	args->body = 0;
	args->alignment = 0;
	args->padding = ' ';
	args->res = 0;
	args->prefix = "";
}

int	is_specifier(char c)
{
	int		i;
	char	*specs;

	specs = "cspdiuxX%";
	i = 0;
	while (i < SPEC_NUM)
	{
		if (specs[i] == c)
			return (i);
		i++;
	}
	return (-1);
}


int	int_putchar(char c)
{
	return (write(1, &c, 1));
}

int	int_putstr(char *str)
{
	int	res;

	if (!str)
		return (0);
	res = 0;
	while (*str)
	{
		res += int_putchar(*str);
		str++;
	}
	return (res);
}

int	int_putstr_len(char *str, int len)
{
	int	res;

	if (!str)
		return (0);
	res = 0;
	while (*str && len)
	{
		res += int_putchar(*str);
		str++;
		len--;
	}
	return (res);
}

int	get_digits(int nb)
{
	int	digits;

	digits = 0;
	if (nb == -214748364)
		return (11);
	if (nb < 0)
	{
		digits++;
		nb *= -1;
	}
	while (nb)
	{
		digits++;
		nb /= 10;
	}
	return (digits);
}

void	put_width(char *itr, t_args *args, va_list *ap)
{
	int	nb;

	nb = 0;
	if (itr == '*')
	{
		
	}


}

int		read_percentage(char *itr, size_t *i, va_list *ap)
{
	t_args	args;

	initialize_args(&args);
	while (*itr == '0')
	{
		args->flag = ZERO;
		itr++;
		
	}
	while (*itr == '-' || *itr == '0')
	{
		args.flag = DASH;
		itr++;
	}
	put_width(itr, &args, ap);
}

/*
 * va_start and va_end
 * A function may be called with a varying number of arguments of varying types
 * va_start -> initializes ap
 * va_args -> for each agument to be processed
 * va_end -> signals that there are no further arguments
*/

int			ft_printf(const char *format, ...)
{
	char *itr;
	int		res;
	t_args	args;
	va_list	ap;

	itr = (char *)format;
	if (!itr)
		return (0);
	i = 0;
	res = 0;
	va_start(ap, format);
	while (*itr)
	{
		if (*itr == '%' && *++itr != '%')
		{
			res = read_percentage(itr, &ap);
			if (res == -1)
				break ;
			continue ;
		}
		res += int_putchar(*itr);
		itr++;
	}
	va_end(ap);
	if (res == -1)
		return (-1);
	return (res);
}
