/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 14:19:25 by sghezn            #+#    #+#             */
/*   Updated: 2019/12/30 17:49:22 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Auxiliary functions.
*/

int		ft_is_ok(char c)
{
	static char	*chars = "$*.1234567890-+ 0#hlLzjtdDioOuUxXeEfFgGaAcCsSpn%";

	if (!c || ft_strchr_index(chars, c) == -1)
		return (0);
	return (1);
}

int		ft_parse(const char *format, int *i, int *is_ok)
{
	static char	*chars = "dDioOuUxXeEfFgGaAcCsSpn%";

	while (format[*i] && ft_is_ok(format[*i]) &&
		   ft_strchr_index(chars, format[*i]) == -1)
			(*i)++;
	if (ft_is_ok(format[*i]))
	{
		*is_ok = 1;
		(*i)++;
	}
	else
		return (1);
	return (0);
}

/*
** An auxiliary function to compute the length of an integer, excluding prefix.
*/

int		ft_number_len(t_fspec *spec)
{
	int			len;
	int			base;
	intmax_t	n_int;
	uintmax_t	n_uint;

	if (spec->precision == 0 && spec->type == 'd' && spec->value == 0)
		return (0);
	if (spec->precision == 0 && spec->type != 'd' && spec->unsigned_value == 0)
		return (0);
	n_int = (spec->value < 0 ? -spec->value : spec->value);
	n_uint = spec->unsigned_value;
	len = 1;
	base = 10;
	if (spec->type != 'd' && spec->type != 'u')
		base = (spec->type == 'o' ? 8 : 16);
	if (spec->type == 'd')
		while (n_int /= 10)
			len++;
	else
		while (n_uint /= base)
			len++;
	return (len);
}

/*
** An auxiliary function to compute length of an integer prefix.
*/

int		ft_number_prefix_len(t_fspec *spec)
{
	if (spec->type == 'd')
	{
		if (spec->value < 0)
			return (1);
		if (spec->value >= 0 && (spec->flags & 2 || spec->flags & 4))
			return (1);
	}
	if (spec->flags & 16 && spec->unsigned_value != 0)
	{
		if (spec->type == 'o')
			return (1);
		if (spec->type == 'x' || spec->type == 'X')
			return (2);
	}
	if (spec->type == 'p')
		return (2);
	return (0);
}

/*
** An auxiliary function to compute full length of an integer,
** including prefix and zeroes padding.
*/

int		ft_number_full_len(t_fspec *spec)
{
	int	number_len;
	int	prefix_len;
	int	len;

	number_len = ft_number_len(spec);
	prefix_len = ft_number_prefix_len(spec);
	len = number_len + prefix_len;
	if (spec->precision > number_len)
		return (spec->precision + prefix_len);
	if (spec->flags & 8 && !(spec->flags & 1)
		&& spec->precision == -1 && spec->width > len)
		return (spec->width);
	return (len);
}
