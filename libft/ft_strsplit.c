/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 13:49:01 by sghezn            #+#    #+#             */
/*   Updated: 2019/04/09 21:04:44 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c)
			n++;
		i++;
	}
	if (s[0] != c)
		n++;
	return (n);
}

static char	*ft_get_word(char const *s, char c, int *i)
{
	char	*word;
	int		j;

	if (!(word = (char*)malloc(sizeof(word) * ft_strlen(s))))
		return (NULL);
	j = 0;
	while (s[*i] != c && s[*i])
	{
		word[j] = s[*i];
		j++;
		*i += 1;
	}
	word[j] = '\0';
	while (s[*i] == c && s[*i])
		*i += 1;
	return (word);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;
	int		n_words;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	n_words = ft_word_count(s, c);
	if (!(res = (char**)malloc(sizeof(res) * (ft_word_count(s, c) + 1))))
		return (NULL);
	while (s[i] == c && s[i])
		i++;
	while (j < n_words && s[i])
	{
		if (!(res[j] = ft_get_word(s, c, &i)))
			return (NULL);
		j++;
	}
	res[j] = NULL;
	return (res);
}
