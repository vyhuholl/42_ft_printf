/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:50:36 by sghezn            #+#    #+#             */
/*   Updated: 2019/12/18 14:50:36 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Auxillary functions used for printing
** formatted numeric types.
*/

/*
** A function to read a signed decimal integer
** of the expected size and type from CLI arguments.
*/

void		ft_read_int(t_fspec *spec, va_list ap)
{
	intmax_t	n;

	if (spec->length == PRINTF_LENGTH_HH)
		n = (char)va_arg(ap, int);
	else if (spec->length == PRINTF_LENGTH_H)
		n = (short)va_arg(ap, int);
	else if (spec->length == PRINTF_LENGTH_L)
		n = va_arg(ap, long);
	else if (spec->length == PRINTF_LENGTH_LL)
		n = va_arg(ap, long long);
	else if (spec->length == PRINTF_LENGTH_L_DOUBLE)
		n = va_arg(ap, long double);
	else if (spec->length == PRINTF_LENGTH_Z)
		n = va_arg(ap, ssize_t);
	else if (spec->length == PRINTF_LENGTH_J)
		n = va_arg(ap, intmax_t);
	else if (spec->length == PRINTF_LENGTH_T)
		n = va_arg(ap, ptrdiff_t);
	else
		n = va_arg(ap, int);
	spec->num_val = &n;
}

/*
** A function to read an unsigned integer
** of the expected size and type from CLI arguments.
*/

void		ft_read_uint(t_fspec *spec, va_list ap)
{
	uintmax_t	n;

	if (spec->length == PRINTF_LENGTH_HH)
		n = (unsigned char)va_arg(ap, unsigned int);
	else if (spec->length == PRINTF_LENGTH_H)
		n = (unsigned short)va_arg(ap, unsigned int);
	else if (spec->length == PRINTF_LENGTH_L)
		n = va_arg(ap, unsigned long);
	else if (spec->length == PRINTF_LENGTH_LL)
		n = va_arg(ap, unsigned long long);
	else if (spec->length == PRINTF_LENGTH_L_DOUBLE)
		n = va_arg(ap, long double);
	else if (spec->length == PRINTF_LENGTH_Z)
		n = va_arg(ap, ssize_t);
	else if (spec->length == PRINTF_LENGTH_J)
		n = va_arg(ap, uintmax_t);
	else if (spec->length == PRINTF_LENGTH_T)
		n = va_arg(ap, ptrdiff_t);
	else
		n = va_arg(ap, unsigned int);
	spec->num_val = &n;
}

/*
** A function to print the prefix to a number.
*/

int			ft_print_prefix(t_fspec *spec)
{
	if (spec->type == 'd')
	{
		if (spec->num_val > 0)
		{
			if (spec->flags & 2)
				write(1, "+", 1);
			if (spec->flags & 4)
				write(1, " ", 1);
		}
		else if (spec->num_val < 0)
			write(1, "-", 1);
		if (spec->num_val > 0 || spec->flags & 2 || spec->flags & 4)
			return (1);
	}
	if (spec->flags & 16 && ft_strchr_index("oxX", spec->type) != -1
		&& spec->num_val != 0)
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
** An auxillary function to print a character repeated n times.
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
