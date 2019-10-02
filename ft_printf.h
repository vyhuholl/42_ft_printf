/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 12:33:30 by sghezn            #+#    #+#             */
/*   Updated: 2019/10/02 16:01:32 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

/*
** Format specification.
*/

typedef struct	s_fspec
{
	const char	*str;
	int			len;
	int			param;
	int			flags;
	int			width;
	int			precision;
	int			length;
	char		type;
}				t_fspec;

int				ft_printf_atoi(const char *format, int *i);
int				ft_symbols(const char c);
int				ft_is_ok(const char *s, int *i);
int				ft_read(const char *format, va_list ap);
void			ft_parse_param(const char *format, t_fspec *spec, int *i);
void			ft_parse_flags(const char *format, t_fspec *spec, int *i);
void			ft_parse_width(const char *format, t_fspec *spec, int *i);
void			ft_parse_precision(const char *format, t_fspec *spec, int *i);
void			ft_parse_length(const char *format, t_fspec *spec, int *i);
void			ft_parse_type(const char *format, t_fspec *spec, int *i);
t_fspec			*ft_to_spec(const char *format, int len);
int				ft_write(const char *format, int len, va_list ap);
int				ft_printf(const char *format, ...);

#endif