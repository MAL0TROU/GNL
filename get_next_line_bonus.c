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

#include "get_next_line_bonus.h"

t_fdnode	*ft_get_node(t_fdnode **list, int fd)
{
	t_fdnode	*node;

	node = *list;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	node = (t_fdnode *)malloc(sizeof(t_fdnode));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->stash = NULL;
	node->next = *list;
	*list = node;
	return (node);
}

char	*ft_remove_node(t_fdnode **list, int fd)
{
	t_fdnode	**curr;
	t_fdnode	*tmp;

	curr = list;
	while (*curr && (*curr)->fd != fd)
	{
		curr = &((*curr)->next);
	}
	if (!*curr)
		return (NULL);
	tmp = *curr;
	*curr = tmp->next;
	free(tmp->stash);
	free(tmp);
	return (NULL);
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
	static t_fdnode	*list;
	t_fdnode		*node;
	char			*line;
	int				empty_stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = ft_get_node(&list, fd);
	if (read(fd, NULL, 0) < 0)
		return (ft_remove_node(&list, fd));
	if (!ft_is_in(node->stash, '\n'))
		node->stash = ft_read_to_stash(fd, &(node->stash));
	if (!(node->stash))
		return (NULL);
	line = ft_line_from_stash(&(node->stash), &empty_stash);
	if (!line)
		return (ft_remove_node(&list, fd));
	if (empty_stash)
		ft_clear_stash(&(node->stash), NULL);
	return (line);
}
