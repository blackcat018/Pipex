/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:29:34 by moel-idr          #+#    #+#             */
/*   Updated: 2025/03/11 14:44:39 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	open_fds(t_vabs *pipex)
{
	if (pipex->is_here_doc == 0)
	{
		pipex->infile = open(pipex->av[1], O_RDONLY);
		if (pipex->infile < 0)
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

char	*get_current_path(char **env)
{
	char	*temp;
	char	**curr_path;
	char	*result;
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
	result = ft_strdup(curr_path[1]);
	free_split(curr_path);
	return (result);
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
	free(curr_path);
	free(temp);
	return (result);
}
