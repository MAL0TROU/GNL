/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayache <oayache@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 10:23:24 by oayache           #+#    #+#             */
/*   Updated: 2026/11/12 17:00:00 by oayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_clear_stash(char **stash, char *buff)
{
	free(buff);
	free(*stash);
	*stash = NULL;
	return (NULL);
}

int	ft_is_in(char *buff, int c)
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*ret;
	size_t	i;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	len = 0;
	if (s1)
		len += ft_strlen(s1);
	if (s2)
		len += ft_strlen(s2);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		ret[i++] = *s1++;
	while (s2 && *s2)
		ret[i++] = *s2++;
	ret[i] = '\0';
	return (ret);
}

void	ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst || !src)
		return ;
	if (dst == src)
		return ;
	i = 0;
	while (i < len)
	{
		((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
		i++;
	}
}
