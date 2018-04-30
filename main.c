#include "get_next_line.h"

int	main(int ac, char **av)
{
	char *line;
	int fd;

	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		ft_putstr(line);
		free(line);
	}
	close(fd);
	return (0);
}
