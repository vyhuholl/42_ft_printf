/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 14:19:25 by sghezn            #+#    #+#             */
/*   Updated: 2019/12/18 14:59:13 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** An auxillary function to compute the length of an integer
** (unsigned octal, unsigned hexadecimal or signed decimal).
*/

int			ft_nbrlen(t_fspec *spec)
{
	int			len;
	int			base;
	intmax_t	n_int;
	uintmax_t	n_uint;

	len = 1;
	n_int = 0;
	n_uint = 0;
	if (spec->type == 'd')
	{
		ft_memcpy(&*(intmax_t*)spec->num_val, &n_int, sizeof(spec->num_val));
		n_int = (n_int < 0 ? -n_int : n_int);
		while (n_int /= 10)
			len++;
	}
	else
	{
		base = (spec->type == 'o' ? 8 : 16);
		ft_memcpy(&*(uintmax_t*)spec->num_val, &n_uint, sizeof(spec->num_val));
		while (n_uint /= base)
			len++;
	}
	return (len);
}

/*
** A function to print a sidned decimal integer.
*/

void		ft_print_signed_int(t_fspec *spec)
{
	char		*res;
	int			len;
	intmax_t	n;

	n = 0;
	ft_memcpy(&*(intmax_t*)spec->num_val, &n, sizeof(spec->num_val));
	n = (n < 0 ? -n : n);
	len = ft_nbrlen(spec);
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

	n = 0;
	ft_memcpy(&*(uintmax_t*)spec->num_val, &n, sizeof(spec->num_val));
	len = ft_nbrlen(spec);
	base = (spec->type == 'o' ? 8 : 16);
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
