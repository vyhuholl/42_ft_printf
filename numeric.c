/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:50:36 by sghezn            #+#    #+#             */
/*   Updated: 2019/12/12 22:25:57 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Auxillary functions used for printing
** formatted numeric types.
*/

/*
** A function which reads a signed decimal integer
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
** A function which reads an unsigned integer
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
** A function which prints a prefix prepended to a number.
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
	if (spec->flags & 16 && ft_strchr_index("oxX", spec->type) != -1)
	{
		write(1, "0", 1);
		if (spec->type == 'x' || spec->type == 'X')
		{
			write(1, &spec->type, 1);
			return (2);
		}
		return (1);
	}
	return (0);
}

/*
** Utility function to print a character c n times.
*/

void		ft_write_repeat(char c, int n)
{
	int	count;

	count = 0;
	while (count++ < n)
		write(1, &c, 1);
}

/*
** A function which prints zeros/spaces used to pad a number.
*/

int			ft_print_padding(t_fspec *spec, int prefix_len)
{
	intmax_t	n;
	int			len;
	char		c;

	n = *(intmax_t*)spec->num_val;
	if (n < 0)
		n *= -1;
	c = (spec->flags & 8 ? '0' : ' ');
	len = 1;
	while (n /= 10)
		len++;
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
