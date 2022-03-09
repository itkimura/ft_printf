/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:11:48 by itkimura          #+#    #+#             */
/*   Updated: 2022/03/09 17:18:57 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include "libft.h"

# define CONV "dxsc"

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

int			ft_printf(const char *format, ...);
#endif
