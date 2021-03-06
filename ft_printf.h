/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 12:33:30 by sghezn            #+#    #+#             */
/*   Updated: 2019/12/31 19:39:36 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# define PRINTF_LENGTH_H 1
# define PRINTF_LENGTH_L 2
# define PRINTF_LENGTH_L_DOUBLE 3
# define PRINTF_LENGTH_Z 4
# define PRINTF_LENGTH_J 5
# define PRINTF_LENGTH_T 6
# define PRINTF_LENGTH_HH 7
# define PRINTF_LENGTH_LL 8

/*
** Format specification structure.
** All flags are stored in a single integer,
** where n-th bit is n-th flag.
** 1:-(minus) - left-align the output;
** 2:+(plus) - prepend a plus for positive numbers;
** 4: (space) – prepend a space for positive numbers;
** 8:0(zero) – prepend zeros for numbers if width is specified;
** 16:#(hash) – alternate form.
*/

typedef struct	s_fspec
{
	const char	*str;
	intmax_t	value;
	uintmax_t	unsigned_value;
	int			param;
	int			flags;
	int			width;
	int			precision;
	int			length;
	char		type;
}				t_fspec;

int				ft_is_ok(char c);
int				ft_parse(const char *format, int *i, int *is_ok);
int				ft_read(const char *format, va_list ap);
void			ft_parse_param(const char *format, t_fspec *spec, int *i);
void			ft_parse_flags(const char *format, t_fspec *spec, int *i);
void			ft_parse_width(const char *format, t_fspec *spec, int *i);
void			ft_parse_precision(const char *format, t_fspec *spec, int *i);
void			ft_parse_length(const char *format, t_fspec *spec, int *i);
void			ft_parse_type(const char *format, t_fspec *spec, int *i);
t_fspec			ft_to_spec(const char *format);
int				ft_print_spec(t_fspec *spec, va_list ap);
void			ft_read_int(t_fspec *spec, va_list ap);
void			ft_read_uint(t_fspec *spec, va_list ap);
int				ft_number_len(t_fspec *spec);
int				ft_number_prefix_len(t_fspec *spec);
int				ft_number_full_len(t_fspec *spec);
void			ft_print_prefix(t_fspec *spec, int len);
void			ft_print_signed_int(t_fspec *spec);
void			ft_print_unsigned_int(t_fspec *spec);
int				ft_print_char(t_fspec *spec, va_list ap);
int				ft_print_string(t_fspec *spec, va_list ap);
int				ft_print_percent(t_fspec *spec, va_list ap);
int				ft_print_number(t_fspec *spec, va_list ap);
int				ft_write(const char *format, int len, int is_ok, va_list ap);
int				ft_printf(const char *format, ...);

#endif
