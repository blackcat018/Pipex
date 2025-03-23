/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:43:44 by moel-idr          #+#    #+#             */
/*   Updated: 2025/03/15 15:41:43 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	get_info(int fd, t_vabs *pipex)
{
	char	*line;
	ssize_t	bytes_written;

	while (1)
	{
		write(1, "here_doc> ", 10);
		line = get_next_line(0);
		if (!line)
			(perror("get_next_line failed"), exit(1));
		if (ft_strncmp(line, pipex->av[2], ft_strlen(pipex->av[2])) == 0
			&& line[ft_strlen(pipex->av[2])] == '\n')
		{
			free(line);
			break ;
		}
		bytes_written = write(fd, line, ft_strlen(line));
		if (bytes_written == -1)
		{
			(perror("write failed"), free(line), close(fd));
			exit(EXIT_FAILURE);
		}
		free(line);
	}
}

void	handle_here_doc(t_vabs *pipex)
{
	int	fd;

	if (!pipex->av[2])
		(perror("Invalid delimiter"), exit(EXIT_FAILURE));
	fd = open("/tmp/here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		(perror("open here_doc"), exit(EXIT_FAILURE));
		exit(EXIT_FAILURE);
	}
	get_info(fd, pipex);
	close(fd);
	pipex->infile = open("/tmp/here_doc", O_RDONLY);
	if (pipex->infile == -1)
	{
		perror("open here_doc for reading");
		exit(EXIT_FAILURE);
	}
}
