/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 12:33:06 by sghezn            #+#    #+#             */
/*   Updated: 2019/12/18 13:04:43 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** A function to convert a format placeholder string to a t_fspec structure.
*/

t_fspec	ft_to_spec(const char *format)
{
	t_fspec	spec;
	int		i;

	spec = (t_fspec) {
		.str = ft_strdup(format),
		.param = 0,
		.flags = 0,
		.width = 0,
		.precision = 0,
		.length = 0,
		.type = 0
	};
	i = 1;
	ft_parse_param(format, &spec, &i);
	ft_parse_flags(format, &spec, &i);
	ft_parse_width(format, &spec, &i);
	ft_parse_precision(format, &spec, &i);
	ft_parse_length(format, &spec, &i);
	ft_parse_type(format, &spec, &i);
	return (spec);
}

/*
** A function to print an argument formatted
** accordingly to a specification.
*/

int		ft_print_spec(t_fspec *spec, va_list ap)
{
	if (spec->type == 'c')
		return (ft_print_char(spec, ap));
	if (spec->type == 's')
		return (ft_print_string(spec, ap));
	if (spec->type == '%')
		return (ft_print_percent(spec, ap));
	return (ft_print_number(spec, ap));
}

/*
** A function to print both regular strings and formatted strings.
*/

int		ft_write(const char *format, int len, va_list ap)
{
	t_fspec	spec;

	if (*format == '%')
	{
		spec = ft_to_spec(format);
		return (ft_print_spec(&spec, ap));
	}
	else
	{
		write(1, format, len);
		return (len);
	}
}

/*
** A function to read a format string and its arguments
** and print the corresponding formatted string.
*/

int		ft_read(const char *format, va_list ap)
{
	int	res;
	int	start;
	int	i;

	res = 0;
	i = 0;
	while (format[i])
	{
		start = i;
		if (format[i] == '%')
		{
			i++;
			while (format[i] && ft_strchr_index(
				"-+ 0#123456789$*.hlLjzt", format[i]) != -1)
				i++;
			if (!format[i] || ft_strchr_index(
				"dDioOuUxXeEfFgGaAcCsSpn%", format[i]) == -1)
				continue;
		}
		else
			while (format[i] && format[i] != '%')
				i++;
		res += ft_write(format + start, i - start, ap);
	}
	return (res);
}

/*
** The main function.
*/

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, format);
	res = ft_read(format, ap);
	va_end(ap);
	return (res);
}
