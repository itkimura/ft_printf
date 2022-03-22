/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 22:29:48 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/22 23:51:45 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	test_print_args(t_args *args)
{
	printf("\nargs->flag = %d\n", args->flag);
	printf("args->width = %d\n", args->width);
	printf("args->c = %d\n", args->c);
	printf("args->precision = %d\n", args->precision);
	printf("args->args_len = %d\n", args->args_len);
	printf("args->zero = %d\n", args->zero);
	printf("args->space = %d\n", args->space);
	printf("args->base = %d\n", args->base);
	printf("args->res = %d\n\n", args->res);
}

void	initialize_args(t_args *args)
{
	args->flag = NONE;
	args->width = INIT;
	args->c = INIT;
	args->precision = INIT;
	args->args_len = 0;
	args->zero = 0;
	args->space = 0;
	args->base = 0;
	args->res = 0;
	args->prefix = "";
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

int	is_specifier(char **itr)
{
	int		i;
	char	c;

	i = 0;
	c = **itr;
	(*itr)++;
	while (i < CHAR_NUM)
	{
		if (CONV[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	put_width(char **itr, t_args *args, va_list *ap)
{
	int	nb;

	nb = 0;
	if (**itr == '*')
	{
		nb = va_arg(*ap, int);
		if (nb < 0)
		{
			nb *= -1;
			args->flag = MINUS;
		}
		args->width = nb;
		(*itr)++;
	}
	else if (**itr >= '0' && **itr <= '9')
	{
		while (**itr >= '0' && **itr <= '9')
		{
			nb = nb * 10 + (**itr - '0');
			(*itr)++;
		}
		args->width = nb;
	}
}

void	put_precision(char **itr, t_args *args, va_list *ap)
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
		args->precision = nb;
	}
	else if (**itr >= '0' && **itr <= '9')
	{
		while (**itr >= '0' && **itr <= '9')
		{
			nb = nb * 10 + (**itr - '0');
			(*itr)++;
		}
		args->precision = nb;
	}
	else
		args->precision = DOT_ONLY;
}

void	flag_none(t_args *args, char c)
{
	while (args->space)
	{
		args->res += int_putchar(' ');
		args->space--;
	}
	while (*(args->prefix))
	{
		args->res += int_putchar(*args->prefix);
		args->prefix++;
	}
	while (args->zero)
	{
		args->res += int_putchar('0');
		args->zero--;
	}
	if (args->args_len)
	{
		args->res += int_putchar(c);
		args->args_len--;
	}
}

void	flag_zero(t_args *args, char c)
{
	while (*(args->prefix))
	{
		args->res += int_putchar(*args->prefix);
		args->prefix++;
	}
	while (args->space)
	{
		args->res += int_putchar('0');
		args->space--;
	}
	if (args->args_len)
	{
		args->res += int_putchar(c);
		args->args_len--;
	}
}

void	flag_minus(t_args *args, char c)
{
	while (*(args->prefix))
	{
		args->res += int_putchar(*args->prefix);
		args->prefix++;
	}
	while (args->zero)
	{
		args->res += int_putchar('0');
		args->zero--;
	}
	if (args->args_len)
	{
		args->res += int_putchar(c);
		args->args_len--;
	}
	while (args->space && !args->args_len)
	{
		args->res += int_putchar(' ');
		args->space--;
	}
}

void	print_c(t_args *args, va_list *ap, void (*print_flag[])(t_args *, char))
{
	unsigned char	c;

	c = (unsigned char)va_arg(*ap, int);
	args->args_len = 1;
	if (args->args_len < args->width)
		args->space = args->width - args->args_len;
	print_flag[args->flag](args, c);
}

void	print_s(t_args *args, va_list *ap, void (*print_flag[])(t_args *, char))
{
	char	*s;

	s = (char *)va_arg(*ap, char *);
	if (s == 0)
		s = "(null)";
	test_print_args(args);
	if (args->precision == DOT_ONLY)
		args->precision = 0;
	args->args_len = ft_strlen(s);
	if (args->args_len < args->width)
		args->space = args->width - args->args_len;
	if (args->args_len == 0)
		print_flag[args->flag](args, 0);
	while (args->args_len)
	{
		print_flag[args->flag](args, *s);
		s++;
	}

}

void	put_arg(t_args *args, va_list *ap)
{
	void	(*print_args[CHAR_NUM])(t_args *, va_list *, void (*print_flag[])(t_args *, char));
	void	(*print_flag[FLAG_NUM])(t_args *, char);

	print_args[CHAR_C] = print_c;
	print_args[CHAR_S] = print_s;
	print_flag[NONE] = flag_none;
	print_flag[MINUS] = flag_minus;
	print_flag[ZERO] = flag_zero;
	print_args[args->c](args, ap, print_flag); 
}

int	read_percentage(char **itr, va_list *ap)
{
	t_args	args;

	initialize_args(&args);
	while (**itr == '0')
	{
		args.flag = ZERO;
		(*itr)++;
	}
	while (**itr == '-' || **itr == '0')
	{
		args.flag = MINUS;
		(*itr)++;
	}
	put_width(itr, &args, ap);
	if (**itr == '.')
		put_precision(itr, &args, ap);
	args.c = is_specifier(itr);
	if (args.c == -1)
		return (-1);
	put_arg(&args, ap);
	return (args.res);
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
	char	*itr;
	int		res;
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
			res += read_percentage(&itr, &ap);
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
