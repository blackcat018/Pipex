/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:52:28 by moel-idr          #+#    #+#             */
/*   Updated: 2024/11/09 19:01:17 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t length)
{
	size_t			i;
	unsigned char	*r;

	i = 0;
	r = (unsigned char *)s;
	while (i < length)
	{
		r[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
