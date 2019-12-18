/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:50:36 by sghezn            #+#    #+#             */
/*   Updated: 2019/12/18 15:59:32 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Auxiliary functions for printing formatted numeric types.
*/

/*
** A function to read a signed decimal integer
** of the expected size and type from CLI arguments.
*/

void		ft_read_int(t_fspec *spec, va_list ap)
{
	if (spec->length == PRINTF_LENGTH_HH)
		spec->value = (char)va_arg(ap, int);
	else if (spec->length == PRINTF_LENGTH_H)
		spec->value = (short)va_arg(ap, int);
	else if (spec->length == PRINTF_LENGTH_L)
		spec->value = va_arg(ap, long);
	else if (spec->length == PRINTF_LENGTH_LL)
		spec->value = va_arg(ap, long long);
	else if (spec->length == PRINTF_LENGTH_L_DOUBLE)
		spec->value = va_arg(ap, long double);
	else if (spec->length == PRINTF_LENGTH_Z)
		spec->value = va_arg(ap, ssize_t);
	else if (spec->length == PRINTF_LENGTH_J)
		spec->value = va_arg(ap, intmax_t);
	else if (spec->length == PRINTF_LENGTH_T)
		spec->value = va_arg(ap, ptrdiff_t);
	else
		spec->value = va_arg(ap, int);
}

/*
** A function to read an unsigned integer
** of the expected size and type from CLI arguments.
*/

void		ft_read_uint(t_fspec *spec, va_list ap)
{
	if (spec->length == PRINTF_LENGTH_HH)
		spec->unsigned_value = (unsigned char)va_arg(ap, unsigned int);
	else if (spec->length == PRINTF_LENGTH_H)
		spec->unsigned_value = (unsigned short)va_arg(ap, unsigned int);
	else if (spec->length == PRINTF_LENGTH_L)
		spec->unsigned_value = va_arg(ap, unsigned long);
	else if (spec->length == PRINTF_LENGTH_LL)
		spec->unsigned_value = va_arg(ap, unsigned long long);
	else if (spec->length == PRINTF_LENGTH_L_DOUBLE)
		spec->unsigned_value = va_arg(ap, long double);
	else if (spec->length == PRINTF_LENGTH_Z)
		spec->unsigned_value = va_arg(ap, ssize_t);
	else if (spec->length == PRINTF_LENGTH_J)
		spec->unsigned_value = va_arg(ap, uintmax_t);
	else if (spec->length == PRINTF_LENGTH_T)
		spec->unsigned_value = va_arg(ap, ptrdiff_t);
	else
		spec->unsigned_value = va_arg(ap, unsigned int);
}

/*
** A function to print the prefix to a number.
*/

int			ft_print_prefix(t_fspec *spec)
{
	if (spec->type == 'd' && spec->value != 0)
	{
		if (spec->value < 0)
			write(1, "-", 1);
		else if (spec->flags & 2 && spec->value > 0)
			write(1, "+", 1);
		else if (spec->flags & 4 && spec->value > 0)
			write(1, " ", 1);
		return (1);
	}
	if (spec->type != 'd' && spec->flags & 16 && spec->unsigned_value != 0)
	{
		write(1, "0", 1);
		if (spec->type == 'o')
			return (1);
		write(1, &spec->type, 1);
		return (2);
	}
	return (0);
}

/*
** An auxiliary function to print a character repeated n times.
*/

void		ft_write_repeat(char c, int n)
{
	int	count;

	count = 0;
	while (count++ < n)
		write(1, &c, 1);
}

/*
** A function to pad a number with zeroes or spaces.
*/

int			ft_print_padding(t_fspec *spec, int prefix_len)
{
	char		c;
	int			len;

	c = (spec->flags & 8 ? '0' : ' ');
	len = ft_nbrlen(spec);
	if (spec->width > len && spec->width > spec->precision + prefix_len)
	{
		if (spec->precision + prefix_len > len)
			ft_write_repeat(c, spec->width - spec->precision + prefix_len);
		else
			ft_write_repeat(c, spec->width - len);
		return (spec->width - len);
	}
	else if (spec->precision > len)
	{
		ft_write_repeat('0', spec->precision - len);
		return (spec->precision + prefix_len);
	}
	return (len + prefix_len);
}
