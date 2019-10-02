/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 12:33:06 by sghezn            #+#    #+#             */
/*   Updated: 2019/10/02 12:55:55 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** The main function.
*/

int	ft_printf(const char *format, ...)
{
	t_fstring	*fstring;

	if (!(fstring = (t_fstring*)ft_memalloc(sizeof(t_fstring))))
		return (-1);
	fstring->format = format;
	ft_new_fstring(fstring);
}
