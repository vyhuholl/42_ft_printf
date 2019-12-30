/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 14:19:25 by sghezn            #+#    #+#             */
/*   Updated: 2019/12/30 06:01:53 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Auxiliary functions for printing formatted numeric types.
*/

/*
** An auxiliary function to compute the length of an integer, excluding prefix.
*/

int		ft_number_len(t_fspec *spec)
{
	int			len;
	int			base;
	intmax_t	n_int;
	uintmax_t	n_uint;

	n_int = (spec->value < 0 ? -spec->value : spec->value);
	n_uint = spec->unsigned_value;
	len = 1;
	base = 10;
	if (spec->type != 'd')
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
		if (spec->value > 0 && (spec->flags & 2 || spec->flags & 4))
			return (1);
	}
	if (spec->flags & 16 && spec->unsigned_value != 0)
	{
		if (spec->type == 'o')
			return (1);
		if (spec->type == 'x' || spec->type == 'X')
			return (2);
	}
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
	prefix_len = ft_prefix_len(spec);
	len = number_len + prefix_len;
	if (spec->precision > number_len)
		return (spec->precision + prefix_len);
	if (spec->flags & 8 && !(spec->flags & 1)
		&& !spec->precision && spec->width > len)
		return (spec->width);
	return (len);
}

/*
** An auxiliary function which allocates an empty string
** for an integer number and writes the correct prefix to the string.
*/

char	*ft_set_prefix(t_fspec *spec)
{
	char	*res;
	int		len;

	len = ft_number_full_len(spec);
	if (!(res = ft_strnew(len)))
		return (NULL);
	if (spec->type == 'd' && spec->value != 0)
	{
		if (spec->value < 0)
			res[0] = '-';
		else if (spec->flags & 2)
			res[0] = '+';
		else if (spec->flags & 4)
			res[0] = ' ';
	}
	if (spec->flags & 16 && spec->unsigned_value != 0)
	{
		if (spec->type == 'o' || spec->type == 'x' || spec->type == 'X')
		{
			res[0] = '0';
			if (spec->type != 'o')
				res[1] = spec->type;
		}
	}
	return (res);
}
