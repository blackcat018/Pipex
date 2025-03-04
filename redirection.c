/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:43:44 by moel-idr          #+#    #+#             */
/*   Updated: 2025/03/04 17:52:13 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	open_fds(t_vabs *pipex)
{
	pipex->infile = open(pipex->av[1], O_RDONLY);
	if (pipex->infile == -1)
	{
		perror("open infile");
		return (-1);
	}
	pipex->outfile = open(pipex->av[pipex->ac - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
	{
		perror("open outfile");
		close(pipex->infile);
		return (-1);
	}
	return (0);
}

void	handle_child(t_vabs *pipex, int index, int prev_pipe_fd,
		int next_pipe_fd)
{
	char	**cmd;

	if (index == 2)
		dup2(pipex->infile, STDIN_FILENO);
	else
		dup2(prev_pipe_fd, STDIN_FILENO);
	if (index == pipex->ac - 2)
		dup2(pipex->outfile, STDOUT_FILENO);
	else
		dup2(next_pipe_fd, STDOUT_FILENO);
	close(prev_pipe_fd);
	close(next_pipe_fd);
	close(pipex->infile);
	close(pipex->outfile);
	cmd = handle_command(pipex->av[index], pipex->envp);
	if (!cmd)
		(perror("comman failed"), free(pipex->envp), exit(1));
	exec_cmd(cmd, pipex->env, pipex->envp);
	free_split(cmd);
	exit(1);
}

void	closing_end(int prev_pipe_fd, int end_ac, char *envp)
{
	int	index;

	index = 2;
	if (prev_pipe_fd != -1)
		close(prev_pipe_fd);
	index = 2;
	while (index < end_ac)
	{
		wait(NULL);
		(index++);
	}
	free(envp);
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
			handle_child(pipex, index, prev_pipe_fd, next_pipe_fd[1]);
		else
		{
			if (prev_pipe_fd != -1)
				close(prev_pipe_fd);
			close(next_pipe_fd[1]);
			prev_pipe_fd = next_pipe_fd[0];
			index++;
		}
	}
	closing_end(prev_pipe_fd, pipex->ac - 1, pipex->envp);
}
