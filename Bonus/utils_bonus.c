/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:29:34 by moel-idr          #+#    #+#             */
/*   Updated: 2025/03/15 16:27:42 by moel-idr         ###   ########.fr       */
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
	if (!temp)
		return (NULL);
	curr_path = ft_split(temp, '=');
	if (!curr_path)
		return (NULL);
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
		return ((free(curr_path)), free(temp), (NULL));
	free(curr_path);
	free(temp);
	return (result);
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
