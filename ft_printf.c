/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 12:33:06 by sghezn            #+#    #+#             */
/*   Updated: 2019/11/02 15:40:23 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** A function to convert format placeholder string to a t_fspec structure.
*/

t_fspec	ft_to_spec(const char *format, int len)
{
	t_fspec	spec;
	int		i;

	spec = (t_spec)
	{
		.str = ft_strdup(format);
		.len = len;
		.param = 0;
		.flags = 0;
		.width = 0;
		.precision = 0;
		.length = 0;
		.type = 0;
	}
	i = 0;
	ft_parse_param(format, &spec, &i);
	ft_parse_flags(format, &spec, &i);
	ft_parse_width(format, &spec, &i);
	ft_parse_precision(format, &spec, &i);
	ft_parse_length(format, &spec, &i);
	ft_parse_type(format, &spec, &i);
	return (spec);
}


/*
** A function to print a format string and its arguments.
*/

int		ft_print_spec(t_fspec *spec, va_list ap)
{
	if (spec->type == 's')
		return (ft_print_string(spec, ap));
	if (spec->type == 'c')
		return (ft_print_char(spec, ap));
	if (spec->type == '%')
		return (ft_print_percent(spec, ap));
	return (ft_print_hex(spec, ap));
}

/*
** A function to print both regular strings and format strings.
*/

int		ft_write(const char *format, int len, va_list ap)
{
	if (*format == '%')
		return (ft_print_spec(&ft_to_spec(format, len), ap));
	else
	{
		write(1, format, len);
		return (len);
	}
}

/*
** A function to read format string and arguments.
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
			while (format[i] && (ft_strchr_index("-+ 0#123456789$*.hlLjzt", format[i]) != -1))
				i++;
			if (!format[i] || (ft_strchr_index("dDioOuUxXeEfFgGaAcCsSpn%", format[i]) == -1))
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
