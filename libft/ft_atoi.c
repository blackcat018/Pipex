/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:11:37 by moel-idr          #+#    #+#             */
/*   Updated: 2024/11/05 14:33:25 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	num;
	int		signe;

	num = 0;
	i = 0;
	signe = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -signe;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		if (num > (LONG_MAX - (str[i] - '0')) / 10 && signe == 1)
			return (-1);
		if (num > (LONG_MAX - (str[i] - '0')) / 10 && signe == -1)
			return (0);
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	return (num * signe);
}
