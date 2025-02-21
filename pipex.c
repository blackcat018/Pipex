/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:28:04 by moel-idr          #+#    #+#             */
/*   Updated: 2025/02/21 17:57:53 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

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
			path = ft_strdup(pr[1]);
			free(pr[0]);
			free(pr[1]);
			free(pr);
			return (path);
		}
		i++;
	}
	write(STDERR_FILENO, "Error: PATH not found in environment\n", 36);
	close(infile);
	close(outfile);
	exit(1);
}

void	exec_cmd(char **cmd, char **env, char *env_path)
{
	char	**real_path;
	int		i;
	char	*cmd_path;
	char	*temp;

	i = 0;
	real_path = ft_split(env_path, ':');
	while (real_path[i])
	{
		cmd_path = ft_strjoin(real_path[i++], "/");
		temp = cmd_path;
		cmd_path = ft_strjoin(cmd_path, cmd[0]);
		free(temp);
		if (access(cmd_path, X_OK) == 0)
		{
			execve(cmd_path, cmd, env);
			(perror("execve"), free(cmd_path));
			free_split(real_path);
			exit(1);
		}
		free(cmd_path);
	}
	free_split(real_path);
	perror("Command not found");
	exit(1);
}

int	main(int ac, char **av, char **env)
{
	t_vabs	pipex;

	if (ac != 5)
	{
		write(STDERR_FILENO, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 39);
		return (1);
	}
	pipex.av = av;
	pipex.env = env;
	if (open_fds(&pipex) == -1)
		return (1);
	pipex.envp = extract_env(pipex.env, pipex.infile, pipex.outfile);
	if (pipe(pipex.pipe_fd) == -1)
	{
		perror("pipe");
		free(pipex.envp);
		return (1);
	}
	handle_first_child(&pipex);
	handle_second_child(&pipex);
	norminette_is_a_bitch(&pipex);
	return (0);
}
