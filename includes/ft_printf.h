/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:11:48 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/29 18:56:19 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define TYPE "csdiouxXpf%" 
# define LEN "0hlLjzt" 
# define INIT -1
# define INVALID -2
# define DOT_ONLY -3

enum e_flag
{
	NONE,
	MINUS,
	ZERO,
	FLAG_NUM
};

enum e_length
{
	no_len,
	h,
	l,
	L,
	j,
	z,
	t,
	hh,
	ll,
	LEN_NUM
};

enum e_type
{
	TYPE_C,
	TYPE_S,
	TYPE_D,
	TYPE_I,
	TYPE_O,
	TYPE_U,
	TYPE_SX,
	TYPE_LX,
	TYPE_P,
	TYPE_F,
	TYPE_PER,
	TYPE_NUM
};

typedef struct s_format{
	int		flag;
	int		width;
	int		length[LEN_NUM];
	int		type;
	int		precision;
	int		args_len;
	int		zero;
	int		space;
	char	*prefix;
	char	*basestr;
	int		base;
	int		res;
	int		sign;
	int		sharp;
	int		space_flag;
}				t_format;

struct          s_float
{
	uint8_t		float_sign;
	uint8_t		exp;
	uint32_t	frac;
};

/*
typedef struct s_args{
	int	c;
	int	flag;
	int	width;
	int	padding;
	int	has_width;
	int	precision;
	int	alignment;
	int	has_precision;
}				t_args;
*/

/*print.c*/
int		int_putchar(char c);
void	flag_none(t_format *f, char c);
void	flag_minus(t_format *f, char c);
/*nbr.c*/
void	nbr_data(t_format *f, unsigned long long nb);
void	print_f(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char));
void	print_nbr(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char));
/*str.c*/
void	print_c(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char));
void	print_s(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char));
/*format.c*/
int		is_specifier(char **itr, char *str);
void	print_format(t_format *f, va_list *ap);
void	put_width(char **itr, t_format *f, va_list *ap);
void	put_precision(char **itr, t_format *f, va_list *ap);
void	put_length(char **itr, t_format *f);
/*ft_printf.c*/
void	set_base(t_format *f, unsigned long long nb);
int		is_specifier(char **itr, char *str);
int		get_digits(unsigned long long nb, int base);
int		ft_printf(const char *format, ...);
/*test.c*/
# include <stdio.h>
void	test_print_format(t_format *f);
void	test_printbitc(uint32_t	c);
#endif
