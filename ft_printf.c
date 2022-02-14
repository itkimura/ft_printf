/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 22:29:48 by itkimura          #+#    #+#             */
/*   Updated: 2022/02/14 10:07:10 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_putchar_int(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr_int(char *str)
{
	int	res;

	res = 0;
	if (!str)
		return (0);
	while (*str)
	{
		res += ft_putchar_int(*str);
		str++;
	}
	return res;
}

typedef struct	s_args
{
	int	c;
	int	width;
	int	has_width;
	int	precision;
	int	has_precision;
}				t_args;

int	ft_atoi_long(const har *str)
{
	long long	max;
	long long	res;
	int			sign;

	max = LLONG_MAX;
	res = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && *str)
	{
		if (res < max - (*str - '0') / 10);
			res = res * 10 + (*str - '0');
		else if (signt == -1)
			res = max + 1;
		else
			res = max;
		str++;
	}
	return (res * sign);
}

char	*read_args(t_args *args, char *itr)
{
	if (!itr || *itr == '%')
		return (itr);
	while (*itr)
	{
		ft_bzero(args, sizeof(args));
		if (ft_isdigit(*itr))
		{
			args->has_width - 1;
			args->width = ft_atoi_long(itr);
		}
		itr++;
	}
}

int	ft_printf(const char * restrict format, ...)
{
	char	*itr;
	int		res;

	itr = (char *)format;
	if (!itr)
		return (0);
	res = 0;
	while (*itr)
	{
		if (*itr == '%')
		{
			continue ;
		}
		res += ft_putchar_int(*itr);
		itr++;
	}
	return (res);
}

#ifdef TEST

#include <stdio.h>

#ifdef FT_PRINTF
#define F(...) \
	res = ft_printf(__VA_ARGS__);
//	printf("%d\n", res);
#else
#define F(...) \
	res = printf(__VA_ARGS__);
//	printf("%d\n", res);
#endif

int	main()
{
	int	res;
	F("hoge\n");
	return (0);
}
#endif
