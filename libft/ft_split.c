/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:19:55 by moel-idr          #+#    #+#             */
/*   Updated: 2024/11/03 20:41:43 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char *str, char c)
{
	int	i;
	int	word;

	word = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			word++;
			while (str[i] != c && str[i])
				i++;
			if (str[i] == '\0')
				return (word);
		}
		i++;
	}
	return (word);
}

static void	free_all(char **str, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static char	*ft_alloc(char *s, char c, int *pos)
{
	int		start;
	int		word_len;
	int		i;
	char	*word;

	word_len = 0;
	i = 0;
	while (s[*pos] && s[*pos] == c)
		(*pos)++;
	start = *pos;
	while (s[*pos] && s[*pos] != c)
	{
		(*pos)++;
		word_len++;
	}
	word = malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (NULL);
	while (i < word_len)
	{
		word[i] = s[start + i];
		i++;
	}
	word[word_len] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		wds;
	int		pos;
	char	**result;

	if (s == NULL)
		return (NULL);
	i = 0;
	pos = 0;
	wds = word_count((char *)s, c);
	result = malloc((wds + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < wds)
	{
		result[i] = ft_alloc((char *)s, c, &pos);
		if (!result[i])
		{
			free_all(result, i);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
