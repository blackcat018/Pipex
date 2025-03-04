/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:43:44 by moel-idr          #+#    #+#             */
/*   Updated: 2025/02/27 16:56:21 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	handle_here_doc(t_vabs *pipex)
{
	int		fd;
	char	*line;

	fd = open("/tmp/here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		(perror("open here_doc"), exit(EXIT_FAILURE));
	while (1)
	{
		write(1, "here_doc> ", 10);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, pipex->av[2], ft_strlen(pipex->av[2])) == 0
			&& line[ft_strlen(pipex->av[2])] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	pipex->infile = open("/tmp/here_doc", O_RDONLY);
	if (pipex->infile == -1)
		(perror("open here_doc for reading"), exit(EXIT_FAILURE));
}
