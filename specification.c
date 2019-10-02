/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specification.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 15:10:30 by sghezn            #+#    #+#             */
/*   Updated: 2019/10/02 16:01:32 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_parse_param(const char *format, t_fspec *spec, int *i)
{
	int	param;
	int	temp;

	(*i)++;
	temp = *i;
	if (!ft_isdigit(format[*i]))
		return ;
	param = ft_printf_atoi(format, i);
	if (format[*i] != '$')
		*i = temp;
	else
		spec->param = param;
}

/*
** A function to convert format string to a t_fspec structure.
*/

t_fspec	*ft_to_spec(const char *format, int len)
{
	t_fspec	*spec;
	int		i;

	spec = (t_spec*)ft_memalloc(sizeof(t_spec));
	spec->str = ft_strdup(format);
	i = 0;
	ft_parse_param(format, spec, &i);
	ft_parse_flags(format, spec, &i);
	ft_parse_width(format, spec, &i);
	ft_parse_precision(format, spec, &i);
	ft_parse_length(format, spec, &i);
	ft_parse_type(format, spec, &i);
	return (spec);
}
