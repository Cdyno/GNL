/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 07:16:04 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/20 06:01:45 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
# endif

#ifndef MAX_FD
# define MAX_FD 512
# endif
int		get_next_line(int fd);

size_t	ft_strclen(const char *s, char  cond);

#endif
