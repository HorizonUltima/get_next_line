/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgergink <hgergink@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:10:56 by hgergink          #+#    #+#             */
/*   Updated: 2025/08/24 20:21:00 by hgergink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_setnull(char **str)
{
	if (*str)
		free(*str);
	*str = (void *)0;
}

int	ft_strl(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	unsigned char	*b;
	size_t			n;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return ((void *)0);
	b = ptr;
	n = nmemb * size;
	while (0 < n--)
		b[n] = 0;
	return (ptr);
}

int	ft_strchr_zero(char *str, char c)
{
	int	eof;

	eof = 0;
	while (*str)
	{
		if (*str == c)
			eof = 1;
		*str = 0;
		str++;
	}
	return (eof);
}

void	ft_cutstr(char **str, size_t start, size_t len)
{
	char	*trimmed_str;
	size_t	i;

	trimmed_str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!trimmed_str)
	{
		ft_setnull(str);
		return ;
	}
	i = 0;
	while ((*str)[start] && len--)
	{
		trimmed_str[i++] = (*str)[start++];
	}
	free(*str);
	*str = trimmed_str;
}
