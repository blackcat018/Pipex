/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:43:44 by moel-idr          #+#    #+#             */
/*   Updated: 2025/02/21 18:00:14 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	norminette_is_a_bitch(t_vabs *pipex)
{
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	close(pipex->infile);
	close(pipex->outfile);
	wait(NULL);
	wait(NULL);
	free(pipex->envp);
}

int	open_fds(t_vabs *pipex)
{
	pipex->infile = open(pipex->av[1], O_RDONLY);
	if (pipex->infile == -1)
	{
		perror("open infile");
		return (-1);
	}
	pipex->outfile = open(pipex->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
	{
		perror("open outfile");
		close(pipex->infile);
		return (-1);
	}
	return (0);
}

void	handle_first_child(t_vabs *pipex)
{
	pid_t	pid1;
	char	**cmd1;

	pid1 = fork();
	if (pid1 == -1)
		(perror("fork"), exit(1));
	if (pid1 == 0)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
		close(pipex->infile);
		cmd1 = handle_command(pipex->av[2]);
		if (!cmd1)
		{
			(perror("ft_split"), free(pipex->envp));
			exit(1);
		}
		(exec_cmd(cmd1, pipex->env, pipex->envp), free_split(cmd1));
		exit(1);
	}
}

void	handle_second_child(t_vabs *pipex)
{
	pid_t	pid2;
	char	**cmd2;

	pid2 = fork();
	if (pid2 == -1)
		(perror("fork"), exit(1));
	if (pid2 == 0)
	{
		dup2(pipex->pipe_fd[0], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->pipe_fd[1]);
		close(pipex->pipe_fd[0]);
		close(pipex->outfile);
		cmd2 = handle_command(pipex->av[3]);
		if (!cmd2)
		{
			(perror("ft_split"), free(pipex->envp));
			exit(1);
		}
		(exec_cmd(cmd2, pipex->env, pipex->envp), free_split(cmd2));
		exit(1);
	}
}
