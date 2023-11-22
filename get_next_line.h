/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 07:16:04 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/22 11:09:50 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# ifndef MAX_FD
#  define MAX_FD 512
# endif

char	*get_next_line(int fd);
size_t	ft_strclen(const char *str, char cond);
void	*ft_memset(void *ptr, int c, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strndup(const char *src, size_t len);

#endif
