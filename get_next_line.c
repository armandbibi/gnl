/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiestro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 12:51:09 by abiestro          #+#    #+#             */
/*   Updated: 2018/04/25 12:47:32 by abiestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_reader		*ft_get_reader(int fd, t_reader *save)
{
	t_reader	*reader;
	t_reader	*s;

	s = save;
	while (s)
	{
		if (s->fd == fd)
		{
			printf("founded\n");
			return (s);
		}
		s = s->next;
	}
	if (!(reader = (t_reader *)malloc(sizeof(*reader))))
		return (0);
	reader->new_line = NULL;
	reader->rest = NULL;
	reader->fd = fd;
	reader->next = save;
	save = reader;
	return (save);
}

static int				ft_build_line(t_reader *reader, int fd)
{
	char *tmp;
	int size;
	char *tmp2;

	if (reader->rest)
	{
		reader->new_line = ft_strdup(&reader->rest[1]);
		ft_strdel(&reader->rest);
		if (ft_strchr(reader->new_line, END_LINE))
			return (1);
	}
	if (!(tmp = ft_strnew(BUFF_SIZE)))
		return (0);
	while (!(ft_strchr(reader->new_line, END_LINE)) && (size = read(fd, tmp, BUFF_SIZE)) > 0)
	{
		if (!reader->new_line)
			reader->new_line = ft_strnew(1);
		tmp2 = ft_strnew(ft_strlen(reader->new_line) + ft_strlen(tmp));
		ft_strcpy(tmp2, reader->new_line);
		ft_strcat(tmp2, tmp);
		free(reader->new_line);
		reader->new_line = tmp2;
		ft_strclr(tmp);
	}
	if (size == -1)
		return (-1);
	tmp2 = NULL;
	ft_strdel(&tmp);
	if (reader->new_line)
	   return (1);
	return (0);	
}

int					get_next_line(const int fd, char **line)
{
	static t_reader *reader = NULL;		//saved fd
	int				value;				//value helping for the errors
	size_t			limit;				//where to cut the string

	if (!(reader = ft_get_reader(fd, reader)))
		return (-1);
	if ((value = ft_build_line(reader, fd)) == -1)
		return (-1);
	if (!reader->new_line || !*reader->new_line)
	{
		*line = NULL;
		return (0);
	}
	limit = ft_strlen(reader->new_line) - ft_strlen(ft_strchr(reader->new_line, END_LINE));
	*line = ft_strnew(limit + 1);
	*line = ft_strncpy(*line, reader->new_line, limit);
	reader->rest = ft_strdup(&reader->new_line[limit]);
	ft_strclr(reader->new_line);
	reader->new_line = NULL;
	return (1);
}

int     main(int ac, char **av)
{
	ac = 0;
	int fd = open(av[1], O_RDONLY);
	char *s = NULL;
	int i;
	int j = 0;
	while ((i = get_next_line(fd, &s)) > 0 || j++ < 1)
	{
		printf("\n---i = %d, s = %s---\n", i, s);
	}
	printf("\n\n--------------\n\n");
	while (1);
}
