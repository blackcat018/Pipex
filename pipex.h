/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:43:44 by moel-idr          #+#    #+#             */
/*   Updated: 2025/02/21 17:47:22 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct t_vabse
{
	int		pipe_fd[2];
	int		infile;
	int		outfile;
	char	*envp;
	int		ac;
	char	**av;
	char	**env;
}			t_vabs;

int			does_it_have_options(char *cmd);
void		free_split(char **array);
void		handle_first_child(t_vabs *pipex);
void		handle_second_child(t_vabs *pipex);
int			open_fds(t_vabs *pipex);
char		**handle_command(char *cmd);
void		norminette_is_a_bitch(t_vabs *pipex);
char		**handle_awk_command(char *cmd);
void		exec_cmd(char **cmd, char **env, char *env_path);

#endif