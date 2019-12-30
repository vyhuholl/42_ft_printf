/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:50:36 by sghezn            #+#    #+#             */
/*   Updated: 2019/12/30 06:03:27 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Functions to print integers.
*/

/*
** A function to read a signed decimal integer
** of the expected size and type from CLI arguments.
*/

void	ft_read_int(t_fspec *spec, va_list ap)
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

void	ft_read_uint(t_fspec *spec, va_list ap)
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
** A function to print a signed decimal integer.
*/

void	ft_print_signed_int(t_fspec *spec)
{
	char		*res;
	int			len;
	intmax_t	n;

	n = (spec->value < 0 ? -spec->value : spec->value);
	len = ft_number_len(spec);
	res = ft_set_prefix(spec);
	while (len)
	{
		res[--len] = n % 10 + 48;
		n /= 10;
	}
	ft_putstr(res);
	free(res);
}

/*
** A function to print an unsigned integer.
*/

void	ft_print_unsigned_int(t_fspec *spec)
{
	static char	*digits = "0123456789abcdef";
	char		*res;
	int			base;
	int			len;
	uintmax_t	n;

	n = spec->unsigned_value;
	len = ft_number_len(spec);
	res = ft_set_prefix(spec);
	base = (spec->type == 'o' ? 8 : 16);
	if (spec->type == 'u')
		base = 10;
	while (len)
	{
		res[--len] = digits[n % base];
		if (spec->type == 'X' && n % base > 9)
			res[len] -= 32;
		n /= base;
	}
	ft_putstr(res);
	free(res);
}
