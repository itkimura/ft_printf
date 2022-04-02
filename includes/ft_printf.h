/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:11:48 by itkimura          #+#    #+#             */
/*   Updated: 2022/04/02 12:54:07 by itkimura         ###   ########.fr       */
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
	ZERO
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
};

typedef struct s_format{
	int		flag;
	int		width;
	int		length[9];
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

/*
 * max_digits = 2 ^ -1023 - 53 = 1076 + 1 = 1077
 * The biggest [ossible int part = 53
 */

typedef struct	s_float
{
	int			dot;
	int			frac_len;
	uint8_t		sign;
	uint32_t	exp;
	uint64_t	frac;
	int8_t		intpart[53];
	int8_t		fracpart[1077];
}				t_float;

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

/*ft_printf.c*/
void	set_base(t_format *f, unsigned long long nb);
int		is_specifier(char **itr, char *str);
int		get_digits(unsigned long long nb, int base);
int		ft_printf(const char *format, ...);
/*format.c*/
int		is_specifier(char **itr, char *str);
void	print_format(t_format *f, va_list *ap);
void	put_width(char **itr, t_format *f, va_list *ap);
void	put_precision(char **itr, t_format *f, va_list *ap);
void	put_length(char **itr, t_format *f);
/*nbr.c*/
void	nbr_data(t_format *f, unsigned long long nb);
void	put_f(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char));
void	put_nbr(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char));
/*str.c*/
void	put_c(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char));
void	put_s(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char));
/*print.c*/
int		int_putchar(char c);
void	flag_none(t_format *f, char c);
void	flag_minus(t_format *f, char c);
/*float.c*/
/*float_convert.c*/
void	convert_intpart(t_float *data);
void	convert_fracpart(t_float *data, uint64_t tmp);
/*float_utils.c*/
void			array_add(int8_t *a, int8_t *b, int size);
void			array_divbytwo(int8_t *n, int size);
void			array_double(int8_t *n, int size);
/*test.c*/
# include <stdio.h>
# include <float.h>
void	test_print_format(t_format *f);
void	test_print_float(t_float *data, long double nb);
void	tbit(uint64_t	c, char *str);
#endif
