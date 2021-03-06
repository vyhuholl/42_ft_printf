/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specification_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:04:12 by sghezn            #+#    #+#             */
/*   Updated: 2019/12/30 09:39:22 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Functions to parse format specification strings.
*/

/*
** A function to parse the precision field.
*/

void	ft_parse_precision(const char *format, t_fspec *spec, int *i)
{
	int precision;

	if (format[*i] != '.')
		return ;
	if (format[++(*i)] == '*')
		spec->precision = INT_MAX;
	else
	{
		precision = 0;
		while (ft_isdigit(format[*i]))
		{
			precision = precision * 10 + (format[*i] - '0');
			(*i)++;
		}
		spec->precision = precision;
	}
}

/*
** A function to parse the length field.
*/

void	ft_parse_length(const char *format, t_fspec *spec, int *i)
{
	int	index;

	if ((index = ft_strchr_index("hlLzjt", format[*i])) == -1)
		return ;
	if ((index == 0 || index == 1) && format[*i] == format[(*i) + 1])
	{
		spec->length = index + 7;
		(*i)++;
	}
	else
		spec->length = index + 1;
	(*i)++;
}

/*
** A function to parse the type field.
*/

void	ft_parse_type(const char *format, t_fspec *spec, int *i)
{
	spec->type = format[*i];
	if (ft_strchr_index("DOUCS", spec->type) != -1)
		spec->length = PRINTF_LENGTH_L;
	if (spec->type == 'p')
		spec->length = PRINTF_LENGTH_LL;
	if (spec->type == 'i' || spec->type == 'D')
		spec->type = 'd';
	if (spec->type == 'O')
		spec->type = 'o';
	if (spec->type == 'U')
		spec->type = 'u';
	if (spec->type == 'C')
		spec->type = 'c';
	if (spec->type == 'S')
		spec->type = 's';
	(*i)++;
}
