/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:56:10 by sghezn            #+#    #+#             */
/*   Updated: 2019/04/08 19:29:25 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len;

	if ((s1 == NULL) || (s2 == NULL))
		return (NULL);
	len = (size_t)(ft_strlen((char*)s1) + ft_strlen((char*)s2));
	if (!(res = ft_memalloc(len + 1)))
		return (NULL);
	res = ft_strcpy(res, (char*)s1);
	res = ft_strcat(res, (char*)s2);
	return (res);
}
