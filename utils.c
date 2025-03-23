/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:45:15 by moel-idr          #+#    #+#             */
/*   Updated: 2025/03/15 16:26:35 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_fds(t_vabs *pipex)
{
	pipex->infile = open(pipex->av[1], O_RDONLY);
	if (pipex->infile < 0)
	{
		perror("infile");
	}
	pipex->outfile = open(pipex->av[pipex->ac - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile < 0)
	{
		perror("outfile");
		close(pipex->infile);
		return (-1);
	}
	return (0);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	contains_quotes(char *word)
{
	int		i;
	char	*s;

	i = 0;
	s = word;
	while (s[i])
	{
		if (s[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin2(char const *s1, char const *s2, char const *s3)
{
	char	*res;
	int		len1;
	int		len2;
	int		len3;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	res = malloc((len1 + len2 + len3 + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len1 + 1);
	ft_strlcat(res, s2, len1 + len2 + 1);
	ft_strlcat(res, s3, len1 + len2 + len3 + 1);
	return (res);
}

int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (!str[i]);
}
