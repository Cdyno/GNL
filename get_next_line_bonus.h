/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:02:28 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/22 15:39:30 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# ifndef MAX_FD
#  define MAX_FD 512
# endif

char	*get_next_line(int fd);
char	*clean_up(char **str, char **str2);
size_t	ft_strclen(const char *str, char cond);
void	*ft_memset(void *ptr, int c, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strndup(const char *src, size_t len);

#endif
