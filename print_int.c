/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:50:36 by sghezn            #+#    #+#             */
/*   Updated: 2019/12/31 19:40:22 by sghezn           ###   ########.fr       */
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
** A function to print a prefix to an integer number.
*/

void	ft_print_prefix(t_fspec *spec, int len)
{
	int	count;

	if (spec->type == 'd')
	{
		if (spec->value < 0)
			write(1, "-", 1);
		else if (spec->flags & 2)
			write(1, "+", 1);
		else if (spec->flags & 4)
			write(1, " ", 1);
	}
	if (spec->flags & 16 && spec->unsigned_value != 0)
	{
		if (spec->type == 'o' || spec->type == 'x' || spec->type == 'X')
		{
			write(1, "0", 1);
			if (spec->type != 'o')
				write(1, &spec->type, 1);
		}
	}
	if (spec->type == 'p')
		write(1, "0x", 2);
	count = len - ft_number_len(spec) - ft_number_prefix_len(spec);
	while (count--)
		write(1, "0", 1);
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
	if (!len || !(res = ft_strnew(len)))
		return ;
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
	if (!len || !(res = ft_strnew(len)))
		return ;
	base = 10;
	if (spec->type != 'd' && spec->type != 'u')
		base = (spec->type == 'o' ? 8 : 16);
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
