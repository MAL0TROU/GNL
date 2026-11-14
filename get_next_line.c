/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayache <oayache@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 00:00:00 by oayache           #+#    #+#             */
/*   Updated: 2026/11/13 00:00:00 by oayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_clear_stash(char **stash, char *buff)
{
	free(buff);
	free(*stash);
	*stash = NULL;
	return (NULL);
}

static int	ft_is_in(const char *buff, int c)
{
	int	i;

	i = 0;
	if (!buff)
		return (0);
	while (buff[i])
	{
		if (buff[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_line_from_stash(char **stash, int *empty_stash)
{
	int		i;
	char	*line;

	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, *stash, i);
	line[i] = '\0';
	*empty_stash = !(*stash)[i];
	if (!*empty_stash)
		ft_memcpy(*stash, *stash + i, ft_strlen(*stash + i) + 1);
	return (line);
}

static char	*ft_read_to_stash(int fd, char **stash)
{
	char	*buff;
	char	*tmp;
	ssize_t	read_bytes;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (ft_clear_stash(stash, NULL));
	read_bytes = 1;
	while ((!*stash || !ft_is_in(*stash, '\n')) && read_bytes > 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes < 0)
			return (ft_clear_stash(stash, buff));
		buff[read_bytes] = '\0';
		tmp = ft_strjoin(*stash, buff);
		if (!tmp)
			return (ft_clear_stash(stash, buff));
		free(*stash);
		*stash = tmp;
	}
	free(buff);
	if (!(*stash)[0])
		return (ft_clear_stash(stash, NULL));
	return (*stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			empty_stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, NULL, 0) < 0)
		return (ft_clear_stash(&stash, NULL));
	if (!ft_is_in(stash, '\n'))
		stash = ft_read_to_stash(fd, &stash);
	if (!stash)
		return (NULL);
	line = ft_line_from_stash(&stash, &empty_stash);
	if (!line)
		return (ft_clear_stash(&stash, NULL));
	if (empty_stash)
		ft_clear_stash(&stash, NULL);
	return (line);
}
