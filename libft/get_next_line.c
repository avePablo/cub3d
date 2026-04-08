#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	index_buffer;
	static int	bytes_read;
	int			index;
	char		*lines;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	lines = malloc(10000);
	if (!lines)
		return (NULL);
	index = 0;
	while (1)
	{
		if (bytes_read <= index_buffer)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read <= 0)
				break ;
			index_buffer = 0;
		}
		lines[index++] = buffer[index_buffer++];
		if (lines[index - 1] == '\n')
			break ;
	}
	if (index == 0)
	{
		free(lines);
		return (NULL);
	}
	lines[index] = '\0';
	return (lines);
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