/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgergink <hgergink@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:11:27 by hgergink          #+#    #+#             */
/*   Updated: 2025/08/21 16:49:34 by hgergink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_chug_stash(char **stash)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (stash[i])
	{
		if ((*stash[i++]) == '\n')
			break ;
	}
	j = ft_strl(*stash + i);
	if (!j)
	{
		free(*stash);
		*stash = (void *)0;
		return ;
	}
	ft_cutstr(stash, i, j);
}

static char	*ft_line_maker(char *stash)
{
	char	*line;
	size_t	i;

	i = 0;
	while (stash[i])
	{
		if (stash[i++] == '\n')
			break ;
	}
	line = (char *)ft_calloc(i, sizeof(char));
	if (!line)
	{
		free(stash);
		stash = (void *)0;
		return ((void *)0);
	}
	while (i)
	{
		line[i - 1] = stash[i - 1];
		i--;
	}
	return (line);
}

static int	ft_strjoin(char **stash, char *str)
{
	char	*dst;
	size_t	i;
	size_t	j;

	dst = (char *)ft_calloc(ft_strl(*stash) + ft_strl(str) + 1, sizeof(char));
	if (!dst)
	{
		if (*stash)
			free(*stash);
		*stash = (void *)0;
		return (1);
	}
	i = 0;
	while (*stash && (*stash)[i])
	{
		dst[i] = (*stash)[i];
		i++;
	}
	j = 0 - 1;
	while (str[++j])
		dst[i + j] = str[j];
	if (*stash)
		free(*stash);
	*stash = dst;
	return (0);
}

static void	ft_append_stash(int fd, char **stash)
{
	char	*read_str;

	read_str = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!read_str)
	{
		if (*stash)
			free(*stash);
		*stash = (void *)0;
		return ;
	}
	while (ft_strchr_zero(read_str, '\n'))
	{
		if (read(fd, read_str, BUFFER_SIZE) <= 0)
			break ;
		if (ft_strjoin(stash, read_str))
			break ;
	}
	free(read_str);
	return ;
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0)
	{
		if (stash)
		{
			free(stash);
			stash = (void *)0;
		}
		return ((void *)0);
	}
	ft_append_stash(fd, &stash);
	if (!stash)
		return ((void *)0);
	line = ft_line_maker(stash);
	if (!line)
		return ((void *)0);
	ft_chug_stash(&stash);
	return (line);
}
