/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:11:48 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/28 17:53:47 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include "libft.h"

# define TYPE "cspdiouxXf%" 
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

enum e_extra
{
	PLUS,
	SHARP,
	SPACE,
	EXTRA_NUM
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
	TYPE_P,
	TYPE_D,
	TYPE_I,
	TYPE_O,
	TYPE_U,
	TYPE_SX,
	TYPE_LX,
	TYPE_F,
	TYPE_PER,
	TYPE_NUM
};


typedef struct s_format{
	int		flag;
	int		width;
	int		precision;
	int		type;
	int		args_len;
	int		extra_flag[EXTRA_NUM];
	int		zero;
	int		space;
	char	*prefix;
	char	*basestr;
	int		length[LEN_NUM];
	int		base;
	int		res;
}				t_format;

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
void	flag_zero(t_format *f, char c);
void	flag_minus(t_format *f, char c);
/*type.c*/
void	print_c(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char));
void	print_s(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char));
void	nbr_data(t_format *f, unsigned long long nb);
void	print_f(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char));
void	print_nbr(t_format *f, va_list *ap, void (*p_flag[])(t_format *, char));
/*width_and_precision.c*/
void	put_width(char **itr, t_format *f, va_list *ap);
void	put_precision(char **itr, t_format *f, va_list *ap);
void	put_length(char **itr, t_format *f);
/*ft_printf.c*/
int		is_specifier(char **itr, char *str);
int		get_digits(unsigned long long nb, int base);
int		ft_printf(const char *format, ...);
/*test*/
void	test_print_format(t_format *f);
#endif
