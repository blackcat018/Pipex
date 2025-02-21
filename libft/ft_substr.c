/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:33:38 by moel-idr          #+#    #+#             */
/*   Updated: 2024/11/02 15:10:31 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	unsigned int	b;

	if (!str)
		return (NULL);
	if (start > (unsigned int)ft_strlen(str))
		return (ft_strdup(""));
	if (len > (unsigned int)ft_strlen(str) - start)
		len = ft_strlen(str) - start;
	i = 0;
	b = start;
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (str[b] && i < len)
	{
		sub[i] = str[b];
		b++;
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
