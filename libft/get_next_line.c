/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:44:15 by pabalvar          #+#    #+#             */
/*   Updated: 2026/05/19 13:56:13 by pabalvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	refill_buffer(int fd, t_buf *buf)
{
	if (buf->bread <= buf->idx)
	{
		buf->bread = read(fd, buf->data, BUFFER_SIZE);
		buf->idx = 0;
	}
}

static int	read_line(int fd, t_buf *buf, char *line)
{
	int	i;

	i = 0;
	while (1)
	{
		refill_buffer(fd, buf);
		if (buf->bread <= 0)
			break ;
		line[i++] = buf->data[buf->idx++];
		if (line[i - 1] == '\n')
			break ;
	}
	return (i);
}

char	*get_next_line(int fd)
{
	static t_buf	buf;
	char			*line;
	int				len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(10000);
	if (!line)
		return (NULL);
	len = read_line(fd, &buf, line);
	if (len == 0)
	{
		free(line);
		return (NULL);
	}
	line[len] = '\0';
	return (line);
}

/*#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);

	char *lines;
	int fd = open(argv[1], O_RDONLY);

	while ((lines = get_next_line(fd)) != NULL)
	{
		printf("%s", lines);
	}
}*/