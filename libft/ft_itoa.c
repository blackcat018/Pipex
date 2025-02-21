/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:36:12 by moel-idr          #+#    #+#             */
/*   Updated: 2024/11/02 15:09:55 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_calc(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	long	j;

	j = n;
	len = len_calc(j);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (j < 0)
	{
		result[0] = '-';
		j = -j;
	}
	if (j == 0)
		result[0] = '0';
	result[len] = '\0';
	while (j > 0)
	{
		result[len - 1] = (j % 10) + '0';
		j = j / 10;
		len--;
	}
	return (result);
}
