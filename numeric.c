/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:50:36 by sghezn            #+#    #+#             */
/*   Updated: 2019/12/12 19:19:39 by sghezn           ###   ########.fr       */
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

void		ft_read_num_val(t_fspec *spec, va_list ap)
{
	if (spec->length == PRINTF_LENGTH_HH)
		spec->num_val = (spec->type == 'd' ? (char)va_arg(ap, int) : (unsigned char)va_arg(ap, unsigned int));
	else if (spec->length == PRINTF_LENGTH_H)
		spec->num_val = (spec->type == 'd' ? (short)va_arg(ap, int) : (unsigned short)va_arg(ap, unsigned int));
	else if (spec->length == PRINTF_LENGTH_L)
		spec->num_val = (spec->type == 'd' ? va_arg(ap, long) : va_arg(ap, unsigned long));
	else if (spec->length == PRINTF_LENGTH_LL)
		spec->num_val = (spec->type == 'd' ? va_arg(ap, long long) : va_arg(ap, unsigned long long));
	else if (spec->length == PRINTF_LENGTH_L_DOUBLE)
		spec->num_val = (spec->type == 'd' ? va_arg(ap, long double) : va_arg(ap, unsigned long double));
	else if (spec->length == PRINTF_LENGTH_Z)
		spec->num_val = va_arg(ap, ssize_t);
	else if (spec->length == PRINTF_LENGTH_J)
		spec->num_val = (spec->type == 'd' ? va_arg(ap, intmax_t) : va_arg(ap, uintmax_t));
	else if (spec->length == PRINTF_LENGTH_T)
		spec->num_val = va_arg(ap, ptrdiff_t);
	else
		spec->num_val = (spec->type == 'd' ? va_arg(ap, int) : va_arg(ap, unsigned int));
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
	else if (spec->flags & 16 && spec->num_val != 0 && ft_strchr_index("oxX", spec->type) != -1)
	{
		write(1, "0", 1);
		if (spec->type == 'x' || spec->type == 'X')
		{
			write(1, spec->type, 1);
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
		write (1, &c, 1);
}

/*
** A function which prints zeros/spaces used to pad a number.
*/

int			ft_print_padding(t_fspec *spec, int prefix_len)
{
	intmax_t	n;
	int			len;
	char		c;

	n = (spec->num_val < 0 ? -spec->num_val : spec->num_val);
	c = (spec->flags & 8 ? '0' : ' ')
	len = (spec->num_val == 0 ? 1 : 0);
	while (n)
	{
		n /= 10;
		len++;
	}
	if (spec->width > len && spec->width > spec->precision + prefix_len)
	{
		if (spec->precision + is_neg > len)
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
