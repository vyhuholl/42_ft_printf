/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:21:03 by sghezn            #+#    #+#             */
/*   Updated: 2019/11/02 16:00:12 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_print_string(t_fspec *spec, va_list ap)
{
	char	*str;
	int		len;

	str = va_arg(ap, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (spec->precision > len)
		spec->precision = len;
	return (ft_print_string_one(str, len spec))
}

int		ft_print_char(t_fspec *spec, va_list ap)
{

}

int		ft_print_percent(t_fspec *spec, va_list ap)
{

}

int		ft_print_hex(t_fspec *spec, va_list ap)
{

}