/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 05:15:29 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/21 10:36:02 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

static size_t	ft_strclen(const char *str, char cond)
{
	size_t	str_len;

	str_len = 0;
	while (str[str_len] != cond && str[str_len])
		str_len++;
	return (str_len);
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

static char	*extr_line(char **board)//, int fd)
{
	char	cond;
	char	*line;
	char	*tmp;
	size_t	line_len;

	cond = '\n';
	//if (!nbr && *board)
	//	return (NULL);
	//printf("sur nbr check {%d}\n", nbr);
	line_len = ft_strclen(*board, cond) + 1;
   	//if (in('\n', *board))
	//	line_len++;
	line = ft_substr(*board, 0, line_len);
	if (ft_strclen(*board, '\0') > line_len)
	{
		tmp = ft_substr(*board, line_len, ft_strclen(*board, '\0'));
		free(*board);
		*board = tmp;
	}
	else
	{
		free(*board);
		*board = NULL;
	}
	//printf("Line {%s}, Leftovers {%s}.\n",line, *board);
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
	buff = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	nbr = 1;
	while (!board[fd] || (!in('\n', board[fd]) && nbr))
	{
		ft_bzero(buff, BUFFER_SIZE + 1);
		nbr = read(fd, buff, BUFFER_SIZE);
		if (nbr == -1 || (!nbr && !board[fd]))
		{
			//ft_bzero(buff, BUFFER_SIZE + 1);
			free(buff);
			free(board[fd]);
			board[fd] = NULL;
			return (NULL);
		}
		tmp = ft_strjoin(board[fd], buff);
		free(board[fd]);
		board[fd] = tmp;
	}
	//if (!nbr)
	//	printf("Survivedwith board{%s},  last buff was  {%s}.\n", board[fd], buff);
	ft_bzero(buff, BUFFER_SIZE + 1);
	free(buff);
	return (extr_line(&board[fd]));//, fd));
}
/*
int	main(void)
{
	int	fd;

	fd = open("numbers.dict",O_RDWR);
	if (fd == 0)
	{
		printf("0\n");
	}
	else
	{
		printf("not 0\n");
	}
	int count;
	count = 36;
	while (count--)
		printf("NEW LINE:  {%d} {%s}\n\n\n\n\n", count, get_next_line(fd));
	close(fd);
	return (0);
}*/
