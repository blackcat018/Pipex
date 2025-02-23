/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd_a_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:46:41 by moel-idr          #+#    #+#             */
/*   Updated: 2025/02/23 01:04:44 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*build_check_path(char *str)
{
	char	**outcome;
	char	*check;
	char	*temp;
	int		i;
	int		j;

	outcome = ft_split(str, '/');
	if (!outcome)
		return (NULL);
	j = 0;
	while (outcome[j])
		j++;
	check = NULL;
	i = 0;
	while (i < j - 1)
	{
		temp = check;
		check = ft_strjoin(check, "/");
		free(temp);
		temp = check;
		check = ft_strjoin(check, outcome[i++]);
		free(temp);
	}
	free_split(outcome);
	return (check);
}

int	is_valid_path(char *check, char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (ft_strncmp(check, paths[i], ft_strlen(check)) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*cmd_is_path(char *str, char *envp)
{
	char	**paths;
	char	*check;
	char	**outcome;
	int		j;

	if (str[0] == '/')
	{
		check = build_check_path(str);//bach njebdo lpath bla cmd
		if (!check)
			return (NULL);
		paths = ft_split(envp, ':');
		if (!paths)
			return (free(check), NULL);
		if (is_valid_path(check, paths))//kan9anrno lpath lijbda mra les path li kaynin
		{
			outcome = ft_split(str, '/');
			(j = 0);
			while (outcome[j])
				j++;
			str = ft_strdup(outcome[j - 1]);
			free_split(outcome);
		}
		(free_split(paths)), (free(check));
	}
	return (str);
}
