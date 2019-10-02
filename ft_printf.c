/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 12:33:06 by sghezn            #+#    #+#             */
/*   Updated: 2019/10/02 15:30:21 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** An auxillary function
** for format specs symbols, which returns:
** 0 if the symbol is a flag;
** 1 if the symbol is a width modifier;
** 2 if the symbol is a precision modifier;
** 3 if the symbol is a length modifier;
** 4 if the symbol is a type conversion;
** -1 if the symbol is invalid.
*/

int	ft_symbols(const char c)
{
	if (ft_strchr_index("-+ 0#", c) != -1)
		return (0);
	if (ft_isdigit(c) || c == '*')
		return (1);
	if (ft_strchr_index("$*.", c) != -1)
		return (2);
	if (ft_strchr_index("hljz", c) != -1)
		return (3);
	if (ft_strchr_index("diouxXfFeEgGaAcsSpn%", c) != -1)
		return (4);
	return (-1);
}

int	ft_write(const char *format, int len, va_list ap)
{
	if (*format == '%')
		return (ft_print_spec(format, len, ap));
	else
	{
		write(1, format, len);
		return (len);
	}
}

/*
** A function to check whether a format spec is valid.
*/

int	ft_is_ok(const char *s, int *i)
{
	while (s[*i] && ft_symbols(s[*i]) >= 0 && ft_symbols(s[*i]) < 4)
		(*i)++;
	if (!s[*i] || ft_symbols(s[*i]) == -1)
		return (1);
	return (0);
}

/*
** A function to read format string and arguments.
*/

int	ft_read(const char *format, va_list ap)
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
			if (ft_is_ok(format, &i))
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

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, format);
	res = ft_read(format, ap);
	va_end(ap);
	return (res);
}
