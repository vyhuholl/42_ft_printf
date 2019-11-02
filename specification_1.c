/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specification_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 15:10:30 by sghezn            #+#    #+#             */
/*   Updated: 2019/11/02 15:56:46 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** A function to parse parameter field.
*/

void	ft_parse_param(const char *format, t_fspec *spec, int *i)
{
	int	param;
	int	temp;

	if (!ft_isdigit(format[++(*i)]))
		return ;
	param = 0;
	temp = *i;
	while (ft_isdigit(format[*i]))
	{
		param = param * 10 + (format[*i] - '0')
		(*i)++;
	}
	if (format[*i] != '$')
		*i = temp;
	else
	{
		(*i)++;
		spec->param = param;
	}
}

/*
** A function to parse flags.
*/

void	ft_parse_flags(const char *format, t_fspec *spec, int *i)
{
	int index;

	while ((*i < spec->len) && ((index = ft_strchr_index("-+ 0#", format[*i])) != -1))
	{
		spec->flags |= (1 << index);
		(*i)++;
	}
}

/*
** A function to parse width field.
*/

void	ft_parse_width(const char *format, t_fspec *spec, int *i)
{
	int	width;

	if (format[*i] == '*')
	{
		spec->width = INT_MAX;
		(*i)++;
	}
	else
	{
		width = 0;
		while (ft_isdigit(format[*i]))
		{
			width = width * 10 + (format[*i] - '0')
			(*i)++;
		}
		spec->width = width;
	}
}
