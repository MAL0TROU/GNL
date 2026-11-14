/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayache <oayache@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 00:00:00 by oayache           #+#    #+#             */
/*   Updated: 2026/11/13 00:00:00 by oayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# ifndef FD_MAX
#  define FD_MAX 1024
# endif

typedef struct s_fdnode
{
	int				fd;
	char			*stash;
	struct s_fdnode	*next;
}	t_fdnode;

char		*get_next_line(int fd);
char		*ft_strjoin(const char *s1, const char *s2);
size_t		ft_strlen(const char *s);
void		ft_memcpy(void *dst, const void *src, size_t len);
t_fdnode	*ft_get_node(t_fdnode **list, int fd);
char		*ft_remove_node(t_fdnode **list, int fd);
int			ft_is_in(char *buff, int c);
char		*ft_clear_stash(char **stash, char *buff);
#endif
