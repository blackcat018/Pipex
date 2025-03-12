/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:28:04 by moel-idr          #+#    #+#             */
/*   Updated: 2025/03/12 19:24:43 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
		if (!cmd_path)
			(ft_putstr_fd("command path not found", 1), exit(1));
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

int	main_norm(int ac, t_vabs *pipex, char *first_arg, char *last_arg)
{
	if (ac < 5)
		return (ft_putstr("Invalid number of arguments\n"), 1);
	if (strcmp(first_arg, "here_doc") == 0)
	{
		if (ac < 6)
		{
			ft_putstr("Use: ./pipex here_doc LIM cmd1 cmd2 outfile\n");
			return (1);
		}
		pipex->is_here_doc = 1;
		handle_here_doc(pipex);
		pipex->outfile = open(last_arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (pipex->outfile < 0)
			return ((perror("outfile")), (close(pipex->infile)), (1));
	}
	else
	{
		if (ac < 5)
			return (ft_putstr("Usage:./pipex infile cmd1 cmd2 outfile\n"), 1);
		pipex->is_here_doc = 0;
		open_fds(pipex);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_vabs	pipex;
	char	*path;

	pipex.av = av;
	pipex.env = env;
	pipex.ac = ac;
	pipex.is_here_doc = 0;
	if (main_norm(ac, &pipex, av[1], av[ac - 1]) == 1)
		return (1);
	path = extract_env(pipex.env, pipex.infile, pipex.outfile);
	pipex.envp = add_curr_path(path, env);
	execute_it(&pipex);
	(free(path), free(pipex.envp));
	return (0);
}
