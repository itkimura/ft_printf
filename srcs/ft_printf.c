/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 22:29:48 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/09 18:21:49 by itkimura         ###   ########.fr       */
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
	args->c = 0;
	args->has_width = 0;
	args->has_precision = 0;
	args->width = 0;
	args->precision = 0;
	args->flag = 0;
	args->alignment = 0;
	args->padding = ' ';
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


int	ft_print_s(t_args *args, char *s, int total_len)
{
	int	res;

	res = 0;
	if (args->alignment == '-')
	{
		res += int_putstr_len(s, args->precision);
		total_len -= args->precision;
		args->precision = 0;
	}
	while (total_len-- > args->precision)
		res += int_putchar(args->padding);
	return (res += int_putstr_len(s, args->precision));
}

int	ft_s(t_args *args, va_list *ap)
{
	char	*s;
	int		total_len;

	s = va_arg(*ap, char *);
	if (!s)
		s = "(null)";
	total_len = ft_strlen(s);
	if (args->has_width)
			total_len = args->width;
	if (!args->has_precision)
		args->precision = ft_strlen(s);
	return (ft_print_s(args, s, total_len));
}

int	ft_c(t_args *args, va_list *ap)
{
	int	c;
	int	res;

	res = 0;
	c = va_arg(*ap, int);
	if (args->alignment == '-')
		res += int_putchar(c);
	while (args->width-- > 1)
		res += int_putchar(args->padding);
	if (args->alignment != '-')
	res += int_putchar(c);
	return (res);
}

int	ft_put_conv(t_args *args, va_list *ap)
{
	if (args->c == 's')
		return (ft_s(args, ap));
	if (args->c == 'c')
		return (ft_c(args, ap));
//	else if (args->c == 'x')
//		return ft_put_x(args, ap);
	return (0);
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

char	*read_args(t_args *args, char *itr)
{
	initialize_args(args);
	if (*itr == '-' || *itr == '+')
		args->alignment = *itr++;
	if (*itr == '0')
		args->padding = *itr++;
	if (*itr == '#' || *itr == ' ')
		args->flag = *itr++;
	if (ft_isdigit(*itr))
		args->has_width = 1;
		itr += get_digits(args->width = ft_atoi(itr));
	if (*itr == '.')
	{
		if (ft_isdigit(*++itr))
		{
			args->has_precision = 1;
			args->precision = ft_atoi(itr);
			if (args->precision == 0)
				itr++;
			itr += get_digits(args->precision);
		}
	}
	if (ft_strchr(CONV, *itr))
		args->c = *itr++;
	return (itr);
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
	char	*itr;
	int		res;
	t_args	args;
	va_list	ap;

	itr = (char *)format;
	if (!itr)
		return (0);
	res = 0;
	va_start(ap, format);
	while (*itr)
	{
		if (*itr == '%' && *++itr != '%')
		{
			itr = read_args(&args, itr);
			res += ft_put_conv(&args, &ap);
			continue ;
		}
		res += int_putchar(*itr);
		itr++;
	}
	va_end(ap);
	return (res);
}
