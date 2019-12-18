/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 14:19:25 by sghezn            #+#    #+#             */
/*   Updated: 2019/12/18 13:33:36 by sghezn           ###   ########.fr       */
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
	intmax_t	n_copy;

	n = *(intmax_t*)spec->num_val;
	if (n < 0)
		n *= -1;
	len = 1;
	n_copy = n;
	while (n_copy /= 10)
		len++;
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
	uintmax_t	n_copy;

	n = *(uintmax_t*)spec->num_val;
	n_copy = n;
	base = (spec->type == 'o' ? 8 : 16);
	len = 1;
	while (n_copy /= base)
		len++;
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
