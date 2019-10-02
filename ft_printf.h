/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 12:33:30 by sghezn            #+#    #+#             */
/*   Updated: 2019/10/02 13:01:44 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

/*
** A structure for formatted strings.
*/

typedef struct	s_fstring
{
	char	*format;
	int		len;
	int		flags;
	int		width;
	int		precision;
	va_list	args;

}				t_fstring;

t_fstring		*ft_new_fstring(t_fstring *fstring);
int				ft_printf(const char *format, ...);

#endif