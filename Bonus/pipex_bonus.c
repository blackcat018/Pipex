/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:28:04 by moel-idr          #+#    #+#             */
/*   Updated: 2025/03/15 17:09:34 by moel-idr         ###   ########.fr       */
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

int	main_norm(int ac, t_vabs *pipex, char *first_arg, char *last_arg)
{
	if (ac < 5)
		return (ft_putstr("Invalid number of arguments\n"), 1);
	if (ft_strncmp(first_arg, "here_doc", ft_strlen(first_arg)) == 0)
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
	free(path);
	execute_it(&pipex);
	(free(path), free(pipex.envp));
	return (0);
}
