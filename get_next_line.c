/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 05:15:29 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/22 15:09:11 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strclen(const char *str, char cond)
{
	size_t	str_len;

	str_len = 0;
	while (str[str_len] != cond && str[str_len])
		str_len++;
	return (str_len);
}

char	*clean_up(char **str, char **str2)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
	if (*str2 != NULL)
	{
		free(*str2);
		*str2 = NULL;
	}
	return (NULL);
}

static int	in(char c, const char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static char	*extract_line(char **board)
{
	char	cond;
	char	*line;
	char	*tmp;
	size_t	line_len;

	cond = '\n';
	line_len = ft_strclen(*board, cond) + 1;
	line = ft_strndup(*board, line_len);
	if (ft_strclen(*board, '\0') > line_len)
	{
		tmp = ft_strndup(*board + line_len, ft_strclen(*board, '\0'));
		clean_up(board, board);
		*board = tmp;
	}
	else
	{
		clean_up(board, board);
	}
	if (!line)
		return (clean_up(board, board));
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*tmp;
	static char	*board[MAX_FD];
	int			nbr;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (clean_up(&board[fd], &board[fd]));
	nbr = 1;
	while (!board[fd] || (!in('\n', board[fd]) && nbr))
	{
		ft_memset(buff, 0, BUFFER_SIZE + 1);
		nbr = read(fd, buff, BUFFER_SIZE);
		if (nbr == -1 || (!nbr && !board[fd]))
			return (clean_up(&board[fd], &buff));
		tmp = ft_strjoin(board[fd], buff);
		clean_up(&board[fd], &board[fd]);
		if (!tmp)
			return (clean_up(&tmp, &buff));
		board[fd] = tmp;
	}
	clean_up(&buff, &buff);
	return (extract_line(&board[fd]));
}
