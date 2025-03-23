/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:43:44 by moel-idr          #+#    #+#             */
/*   Updated: 2025/03/15 16:58:26 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_child(t_vabs *pipex, int index, int prev_pipe_fd,
		int *next_pipe_fd)
{
	char	**cmd;

	close(next_pipe_fd[0]);
	if (index == 2 && pipex->infile > 0)
		dup2(pipex->infile, 0);
	else
		dup2(prev_pipe_fd, 0);
	if (index == pipex->ac - 2)
		dup2(pipex->outfile, 1);
	else
		dup2(next_pipe_fd[1], 1);
	close(prev_pipe_fd);
	close(next_pipe_fd[1]);
	close(pipex->infile);
	close(pipex->outfile);
	cmd = handle_command(pipex->av[index], pipex->envp);
	if (!cmd)
		(perror("command failed"), free(pipex->envp), exit(1));
	exec_cmd(cmd, pipex->env, pipex->envp);
	free_split(cmd);
	exit(1);
}

void	parent_proc(int *prev_pipe_fd, int next_pipe_fd[2])
{
	if (*prev_pipe_fd != -1)
		close(*prev_pipe_fd);
	close(next_pipe_fd[1]);
	*prev_pipe_fd = next_pipe_fd[0];
}

void	closing(int prev_pipe_fd, t_vabs *pipex)
{
	int	index;

	if (prev_pipe_fd != -1)
		close(prev_pipe_fd);
	index = 2;
	while (index < pipex->ac - 1)
	{
		wait(NULL);
		index++;
	}
	free(pipex->envp);
	exit(0);
}

void	execute_it(t_vabs *pipex)
{
	pid_t	pid;

	int (index), (prev_pipe_fd), (next_pipe_fd[2]);
	index = 2;
	prev_pipe_fd = -1;
	while (index < pipex->ac - 1)
	{
		if (pipe(next_pipe_fd) == -1)
			(perror("pipe"), free(pipex->envp), exit(1));
		pid = fork();
		if (pid == -1)
			(perror("fork"), free(pipex->envp), exit(1));
		if (pid == 0)
		{
			if (index == 2 && pipex->infile == -1)
				exit(1);
			handle_child(pipex, index, prev_pipe_fd, next_pipe_fd);
		}
		else
		{
			parent_proc(&prev_pipe_fd, next_pipe_fd);
			index++;
		}
	}
	closing(prev_pipe_fd, pipex);
}
