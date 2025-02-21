/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:45:11 by moel-idr          #+#    #+#             */
/*   Updated: 2024/11/05 14:50:02 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	size;

	size = ft_strlen(str);
	c = (char)c;
	while (size >= 0)
	{
		if (str[size] == (char)c)
		{
			return ((char *)&str[size]);
		}
		size--;
	}
	return (NULL);
}
