/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:50:36 by sghezn            #+#    #+#             */
/*   Updated: 2019/11/27 14:52:22 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Auxillary functions used for printing
** formatted numeric types.
*/


/*
** A function which reads a numeric value
** of the expected size and type from CLI arguments.
*/

intmax_t	ft_read_num_val(t_fspec *spec, va_list ap)
{
	intmax_t	n;

	if (spec->length == PRINTF_LENGTH_HH)
		n = (char)va_arg(ap, int);
	else if (spec->length == PRINTF_LENGTH_H)
		n = (char)va_arg(ap, int);
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
	return (n);
}

/*
** A function which returns a string
** prepended to positive or non-zero numbers.
*/

char		*ft_get_prefix(t_fspec *spec)
{
	if ((!(spec->flags & 16) || (spec->num_val && *(uintmax_t *)spec->num_val == 0)) && !(spec->flags & 16 && spec->type == 'o') && !(spec->type == 'p'))
	{
		if (spec->type != 'd' && spec->flags & 8)
			return ("0");
		return (" ");
	}
	else if (spec->type == 'x' || spec->type == 'p')
		return ("0x");
	else if (spec->type == 'X')
		return ("0X");
	else if (spec->type == 'o')
		return ("0");
	return ("");
}

/*
** Utility function used to compute the length of
** the ASCII string formed from a decimal number
** accordingly to a specification.
*/

int			ft_itoa_printf_len(intmax_t n, t_fspec *spec)
{
	int			is_neg;
	int			len;
	intmax_t	n_copy;

	is_neg = (n < 0 ? 1 : 0);
	len = (n == 0 ? 1 : 0);
	n_copy = (n < 0 ? -n : n);
	while (n_copy)
	{
		n_copy /= n;
		len++;
	}
	if (len < spec->precision)
		len = spec->precision;
	if (!(spec->flags & 1) && spec->flags & 8 && len < spec.width - is_neg)
	{
		len = spec->width - is_neg;
		if (spec->precision > 0)
			len = spec_precision;
	}
	return (len);
}

/*
** A function to convert a decimal number
** to an ASCII string accordingly to a specification.
*/

char		*ft_itoa_printf(intmax_t n, t_fspec *spec)
{
	static char	*digits = "0123456789";
	char		*res;
	int			is_neg;
	int			len;

	is_neg = (n < 0 ? 1 : 0);
	len = ft_itoa_printf_len(n, spec);
	if (n < 0)
		n *= -1;
	res = ft_memalloc(len + is_neg + 1);
	if (!res)
		return (NULL);
	if (is_neg)
		res[0] = '-';
	while (len)
	{
		res[len + is_neg - 1] = digits[n % 10];
		n /= 10;
		len--;
	}
	return (res);
}

/*
** A function to convert an unsigned octal or hexadecimal number
** to an ASCII string accordingly to a specification.
*/

char		*ft_itoa_oct_hex_printf(uintmax_t n, t_fspec *spec)
{

}
