/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 22:29:48 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/14 17:10:22 by itkimura         ###   ########.fr       */
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

int	get_digits(int nb, int base)
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
		nb /= base;
	}
	return (digits);
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

int	int_putnbr(int nb)
{
	long	i;
	int		res;

	res = 0;
	i = nb;
	if (i < 0)
	{
		i *= -1;
		ft_putchar('-');
	}
	if (i >= 10)
	{
		ft_putnbr(i / 10);
		ft_putnbr(i % 10);
	}
	else
		ft_putchar(i + '0');
	return (res);
}

int	ft_d(t_args *args, va_list *ap)
{
	int	res;
	int	d;

	res = 0;
	d = va_arg(*ap, int);
	if (!args->has_precision)
		args->precision = get_digits(d, 10);
	if (args->alignment == '-')
		res += int_putnbr(d);
	while (args->width-- >args->precision)
		res+= int_putchar(args->padding);
	if (args->alignment != '-')
		res+= int_putnbr(d);
	return (res);
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
	if (args->c == 'c')
		return (ft_c(args, ap));
	if (args->c == 's')
		return (ft_s(args, ap));
	if (args->c == 'd')
		return (ft_d(args, ap));
//	else if (args->c == 'x')
//		return ft_put_x(args, ap);
	return (0);
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
		itr += get_digits(args->width = ft_atoi(itr), 10);
	if (*itr == '.')
	{
		if (ft_isdigit(*++itr))
		{
			args->has_precision = 1;
			args->precision = ft_atoi(itr);
			if (args->precision == 0)
				itr++;
			itr += get_digits(args->precision, 10);
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


int	main(void)
{
	ft_printf("01.[%d]\n", 123);
	printf("01.[%d]\n", 123);
	ft_printf("02.[%d]\n", -123);
	printf("02.[%d]\n", -123);
	ft_printf("03.[%d]\n", -2147483648);
	printf("03.[%d]\n", -2147483648);
	ft_printf("04.[%d]\n", 2147483647);
	printf("04.[%d]\n", 2147483647);
	ft_printf("05.[%.0d]\n", -2147483648);
	printf("05.[%.0d]\n", -2147483648);
	ft_printf("06.[%.5d]\n", -2147483648);
	printf("06.[%.5d]\n", -2147483648);
	ft_printf("07.[%.10d]\n", -2147483648);
	printf("07.[%.10d]\n", -2147483648);
	ft_printf("08.[%.20d]\n", -2147483648);
	printf("08.[%.20d]\n", -2147483648);
	ft_printf("09.[%.d]\n", -2147483648);
	printf("09.[%.d]\n", -2147483648);
	ft_printf("10.[%10.d]\n", -2147483648);
	printf("10.[%10.d]\n", -2147483648);
	ft_printf("11.[%20.d]\n", -2147483648);
	printf("11.[%20.d]\n", -2147483648);
	ft_printf("12.[%0.0d]\n", -2147483648);
	printf("12.[%0.0d]\n", -2147483648);
	ft_printf("13.[%5.0d]\n", -2147483648);
	printf("13.[%5.0d]\n", -2147483648);
	ft_printf("14.[%10.0d]\n", -2147483648);
	printf("14.[%10.0d]\n", -2147483648);
	ft_printf("15.[%20.0d]\n", -2147483648);
	printf("15.[%20.0d]\n", -2147483648);
	ft_printf("16.[%0.0d]\n", -2147483648);
	printf("16.[%0.0d]\n", -2147483648);
	ft_printf("17.[%0.5d]\n", -2147483648);
	printf("17.[%0.5d]\n", -2147483648);
	ft_printf("18.[%0.10d]\n", -2147483648);
	printf("18.[%0.10d]\n", -2147483648);
	ft_printf("19.[%0.20d]\n", -2147483648);
	printf("19.[%0.20d]\n", -2147483648);
	ft_printf("20.[%5.0d]\n", -2147483648);
	printf("20.[%5.0d]\n", -2147483648);
	ft_printf("21.[%5.5d]\n", -2147483648);
	printf("21.[%5.5d]\n", -2147483648);
	ft_printf("22.[%5.10d]\n", -2147483648);
	printf("22.[%5.10d]\n", -2147483648);
	ft_printf("23.[%5.20d]\n", -2147483648);
	printf("23.[%5.20d]\n", -2147483648);
	ft_printf("24.[%10.0d]\n", -2147483648);
	printf("24.[%10.0d]\n", -2147483648);
	ft_printf("25.[%10.5d]\n", -2147483648);
	printf("25.[%10.5d]\n", -2147483648);
	ft_printf("26.[%10.10d]\n", -2147483648);
	printf("26.[%10.10d]\n", -2147483648);
	ft_printf("27.[%10.20d]\n", -2147483648);
	printf("27.[%10.20d]\n", -2147483648);
	ft_printf("28.[%20.0d]\n", -2147483648);
	printf("28.[%20.0d]\n", -2147483648);
	ft_printf("29.[%20.5d]\n", -2147483648);
	printf("29.[%20.5d]\n", -2147483648);
	ft_printf("30.[%20.10d]\n", -2147483648);
	printf("30.[%20.10d]\n", -2147483648);
	ft_printf("31.[%20.20d]\n", -2147483648);
	printf("31.[%20.20d]\n", -2147483648);
	ft_printf("32.[%10d]\n", 0);
	printf("32.[%10d]\n", 0);
	ft_printf("33.[%10.d]\n", 0);
	printf("33.[%10.d]\n", 0);
	ft_printf("34.[%10.0d]\n", 0);
	printf("34.[%10.0d]\n", 0);
	ft_printf("35.[%.0d]\n", 0);
	printf("36.[%.0d]\n", 0);
	ft_printf("37.[%10.0d]\n", 10);
	printf("38.[%10.0d]\n", 10);
}

