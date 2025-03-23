/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd_a_path_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:46:41 by moel-idr          #+#    #+#             */
/*   Updated: 2025/03/19 14:28:58 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

static char	*append_str(char *str, const char *append)
{
	char	*temp;

	temp = str;
	str = ft_strjoin(str, append);
	if (!str)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (str);
}

char	*build_check_path(char *str)
{
	char	**outcome;
	char	*check;
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
		check = append_str(check, "/");
		check = append_str(check, outcome[i++]);
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
		check = build_check_path(str);
		if (!check)
			return (NULL);
		paths = ft_split(envp, ':');
		if (!paths)
			return (free(check), NULL);
		if (is_valid_path(check, paths))
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
