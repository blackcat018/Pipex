/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd_a_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:46:41 by moel-idr          #+#    #+#             */
/*   Updated: 2025/02/24 18:05:20 by moel-idr         ###   ########.fr       */
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

char	*get_current_path(char **env)
{
	char	*temp;
	char	**curr_path;
	int		i;

	i = 0;
	curr_path = NULL;
	temp = NULL;
	while (env[i])
	{
		if (ft_strncmp("PWD=", env[i], 4) == 0)
			temp = env[i];
		i++;
	}
	curr_path = ft_split(temp, '=');
	if (!curr_path)
		return (free(temp), NULL);
	return (curr_path[1]);
}

char	*add_curr_path(char *envp, char **env)
{
	char	*curr_path;
	char	*result;
	char	*temp;

	curr_path = get_current_path(env);
	temp = ft_strjoin(envp, ":");
	if (!temp)
		return ((free(temp)), (NULL));
	result = ft_strjoin(temp, curr_path);
	if (!result)
		return ((free(result)), (NULL));
	return (result);
}
