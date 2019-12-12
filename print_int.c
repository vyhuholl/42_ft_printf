/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 14:19:25 by sghezn            #+#    #+#             */
/*   Updated: 2019/12/12 21:09:34 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** A function to print a sidned decimal integer.
*/

void		ft_print_signed_int(t_fspec *spec)
{
	char		*res;
	int			len;
	intmax_t	n;

	n = *(intmax_t*)spec->num_val;
	if (n < 0)
		n *= -1;
	len = 1;
	while (n /= 10)
		len++;
	n = *(intmax_t*)spec->num_val;
	if (n < 0)
		n *= -1;
	if (!(res = ft_strnew(len)))
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
** A function to print an unsigned octal, decimal or hexadecimal integer.
*/

void		ft_print_unsigned_int(t_fspec *spec)
{
	static char	*digits = "0123456789abcdef";
	char		*res;
	int			base;
	int			len;
	uintmax_t	n;

	n = *(uintmax_t*)spec->num_val;
	base = (spec->type == 'o' ? 8 : 16);
	len = 1;
	while (n /= base)
		len++;
	n = *(uintmax_t*)spec->num_val;
	if (!(res = ft_strnew(len)))
		return ;
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
