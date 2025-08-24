/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgergink <hgergink@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:12:29 by hgergink          #+#    #+#             */
/*   Updated: 2025/08/24 20:21:17 by hgergink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	ft_setnull(char **str);
int		ft_strl(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strchr_zero(char *str, char c);
void	ft_cutstr(char **str, size_t start, size_t len);
char	*get_next_line(int fd);
#endif
