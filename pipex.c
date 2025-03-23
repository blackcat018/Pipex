/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:28:04 by moel-idr          #+#    #+#             */
/*   Updated: 2025/03/19 14:37:12 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*extract_env(char **env, int infile, int outfile)
{
	int		i;
	char	**pr;
	char	*path;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			pr = ft_split(env[i], '=');
			if (!pr)
				return (NULL);
			path = ft_strdup(pr[1]);
			if (!path)
				return ((free_split(pr), (NULL)));
			free_split(pr);
			return (path);
		}
		i++;
	}
	write(STDERR_FILENO, "Error: PATH not found in environment\n", 36);
	((close(infile)), (close(outfile)));
	exit(1);
}

void	exec_cmd(char **cmd, char **env, char *env_path)
{
	char	**real_path;
	int		i;
	char	*cmd_path;

	i = 0;
	real_path = ft_split(env_path, ':');
	if (!real_path)
	{
		perror("failed to get command");
		exit(1);
	}
	while (real_path[i])
	{
		cmd_path = ft_strjoin2(real_path[i++], "/", cmd[0]);
		if (!cmd_path)
			(ft_putstr("command not found"), free_split(real_path), exit(1));
		if (access(cmd_path, X_OK) == 0)
		{
			execve(cmd_path, cmd, env);
			(perror("execve"), free(cmd_path), free_split(real_path), exit(1));
		}
		free(cmd_path);
	}
	((free_split(real_path)), (perror("Command not found")), (exit(1)));
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

int	main(int ac, char **av, char **env)
{
	t_vabs	pipex;
	char	*path;

	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 1);
		return (1);
	}
	pipex.av = av;
	pipex.env = env;
	pipex.ac = ac;
	open_fds(&pipex);
	path = extract_env(pipex.env, pipex.infile, pipex.outfile);
	pipex.envp = add_curr_path(path, env);
	free(path);
	execute_it(&pipex);
	free(path);
	free(pipex.envp);
	return (0);
}
