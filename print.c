/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:21:03 by sghezn            #+#    #+#             */
/*   Updated: 2019/12/11 15:58:36 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Functions to print formatted arguments.
*/


/*
** A function to print a string formatted
** accordingly to a specification.
*/

int		ft_print_string(t_fspec *spec, va_list ap)
{
	char	*str;
	int		len;
	int		res;

	if (spec->width == -1)
		spec->width = va_arg(ap, int);
	if (spec->precision == INT_MAX)
		spec->precision = va_arg(ap, int);
	str = va_arg(ap, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (spec->precision > len)
		spec->precision = len;
	else
		len = spec->precision;
	if (spec->width < len)
		spec->width = len;
	res = spec->width;
	while (!(spec->flags & 1) && spec->width-- > len)
		write(1, " ", 1);
	write(1, str, len);
	while ((spec->flags & 1) && spec->width-- > len)
		write(1, " ", 1);
	return (res);
}

/*
** A function to print a character formatted
** accordingly to a specification.
*/

int		ft_print_char(t_fspec *spec, va_list ap)
{
	char	c;
	int		res;

	if (spec->width == -1)
		spec->width = va_arg(ap, int);
	if (spec->precision == INT_MAX)
		spec->precision = va_arg(ap, int);
	c = va_arg(ap, char);
	if (spec->width < 1)
		spec->width = 1;
	res = spec->width;
	while (!(spec->flags & 1) && spec->width-- > 1)
		write(1, " ", 1);
	write(1, &c, 1);
	while ((spec->flags & 1) && spec->width-- > 1)
		write(1, " ", 1);
	return (res);
}

/*
** A function to print a numeric type
** formatted accordingly to a specification.
*/

int		ft_print_number(t_fspec *spec, va_list ap)
{
	char		*prefix;
	int			prefix_len;
	int			res;

	res = 0;
	if (spec->width == -1)
		spec->width = va_arg(ap, int);
	if (spec->precision == INT_MAX)
		spec->precision = va_arg(ap, int);
	ft_read_num_val(spec, ap);
	prefix_len = ft_print_prefix(spec);
	if (!spec->flags & 1)
		res = ft_print_padding(spec, prefix_len);
	if (spec->type == 'd')
		ft_print_signed_int(spec);
	else
		ft_print_unsigned_int(spec);
	if (spec->flags & 1)
		res = ft_print_padding(spec, prefix_len);
	return (res);
}
