/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:28:04 by moel-idr          #+#    #+#             */
/*   Updated: 2025/03/04 15:31:25 by moel-idr         ###   ########.fr       */
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
			(perror("execve"), free(cmd_path), free_split(real_path), exit(1));
		}
		free(cmd_path);
	}
	free_split(real_path);
	perror("Command not found");
	exit(1);
}

void	norminette_suuuuuuuuks(t_vabs *pipex)
{
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	close(pipex->infile);
	close(pipex->outfile);
	while (wait(NULL) > 0)
		;
	free(pipex->envp);
}

int	main(int ac, char **av, char **env)
{
	t_vabs	pipex;
	char	*path;

	if (ac < 5)
	{
		write(STDERR_FILENO, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 39);
		return (1);
	}
	pipex.av = av;
	pipex.env = env;
	pipex.ac = ac;
	if (open_fds(&pipex) == -1)
		exit(EXIT_FAILURE);
	path = extract_env(pipex.env, pipex.infile, pipex.outfile);
	pipex.envp = add_curr_path(path, env);
	execute_it(&pipex);
	norminette_suuuuuuuuks(&pipex);
	return (0);
}
