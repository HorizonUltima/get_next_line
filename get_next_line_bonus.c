/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgergink <hgergink@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:11:27 by hgergink          #+#    #+#             */
/*   Updated: 2025/08/22 16:31:52 by hgergink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_chug_stash(char **stash)
{
	size_t	i;
	size_t	j;

	i = 0;
	while ((*stash)[i])
	{
		if ((*stash)[i++] == '\n')
			break ;
	}
	j = ft_strl(*stash + i);
	if (!j)
	{
		ft_setnull(stash);
		return ;
	}
	ft_cutstr(stash, i, j);
}

static char	*ft_line_maker(char **stash)
{
	char	*line;
	size_t	i;

	i = 0;
	while ((*stash)[i])
	{
		if ((*stash)[i++] == '\n')
			break ;
	}
	line = (char *)ft_calloc(i + 1, sizeof(char));
	if (!line)
	{
		ft_setnull(stash);
		return ((void *)0);
	}
	while (i)
	{
		line[i - 1] = (*stash)[i - 1];
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
		ft_setnull(stash);
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
	ssize_t	check;

	read_str = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!read_str)
	{
		ft_setnull(stash);
		return ;
	}
	while (!ft_strchr_zero(read_str, '\n'))
	{
		check = read(fd, read_str, BUFFER_SIZE);
		if (check <= 0)
		{
			if (check == -1)
				ft_setnull(stash);
			break ;
		}
		if (ft_strjoin(stash, read_str))
			break ;
	}
	free(read_str);
	return ;
}

char	*get_next_line(int fd)
{
	static char	*stash[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return ((void *)0);
	ft_append_stash(fd, stash + fd);
	if (!stash[fd])
		return ((void *)0);
	line = ft_line_maker(stash + fd);
	if (!line)
		return ((void *)0);
	ft_chug_stash(stash + fd);
	return (line);
}
