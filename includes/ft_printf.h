/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:11:48 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/21 00:14:45 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include "libft.h"

/*# define CONV "dxsc"*/

# define INIT -1
# define INVALID -2
# define DOT_ONLY -3

enum e_flag
{
	NONE,
	DASH,
	ZERO,
	FLAG_NUM
};

enum e_char
{
	CHAR_C,
	CHAR_S,
	CHAR_P,
	CHAR_D,
	CHAR_I,
	CHAR_U,
	CHAR_SX,
	CHAR_LX,
	CHAR_PER,
	CHAR_NUM
};

typedef struct s_args{
	int		flag;
	int		width;
	int		precision;
	int		c;
	int		args_len;
	int		zero;
	int		blank;
	char	*prefix;
	char	*basestr;
	int		base;
	int		res;
}				t_args;

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
int			ft_printf(const char *format, ...);
#endif
