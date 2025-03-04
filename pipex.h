/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:43:44 by moel-idr          #+#    #+#             */
/*   Updated: 2025/02/27 13:28:46 by moel-idr         ###   ########.fr       */
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
#include "Bonus/get_next_line/get_next_line_bonus.h"

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

char		*cmd_is_path(char *str, char *envp);
int			contains_quotes(char *word);
int			is_space(char *str);
void		free_split(char **array);
int			open_fds(t_vabs *pipex);
char		**handle_command(char *cmd, char *envp);
void		exec_cmd(char **cmd, char **env, char *env_path);
void		execute_it(t_vabs *pipex);
char		*add_curr_path(char *envp, char **env);
void		handle_here_doc(t_vabs *pipex);

#endif