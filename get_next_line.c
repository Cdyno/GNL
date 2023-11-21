/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 05:15:29 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/21 03:49:41 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	str_len;

	str_len = 0;
	while (str[str_len])
		str_len++;
	return (str_len);
}

char	*ft_strdup(const char *src)
{
	size_t		src_len;
	char		*replica;
	size_t		i;

	i = 0;
	src_len = ft_strlen(src);
	replica = (char *)malloc((src_len + 1) * sizeof(char));
	if (replica == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		replica[i] = src[i];
		i++;
	}
	replica[i] = '\0';
	return (replica);
}

void	*ft_memset(void *ptr, int c, size_t len)
{
	unsigned char	*p;

	p = (unsigned char *)ptr;
	while (len-- > 0)
	{
		*p = (unsigned char)c;
		p++;
	}
	return (ptr);
}

void	ft_bzero(void *ptr, size_t n)
{
	ft_memset(ptr, 0, n);
}

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*res;
	int		n_bytes;

	n_bytes = nitems * size;
	if (nitems != 0 && n_bytes / nitems != size)
		return (0);
	res = malloc(n_bytes);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, n_bytes);
	return (res);
}
static char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	dest_len;

	i = 0;
	dest_len = ft_strlen(dest);
	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	res = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_strcat(res, s1);
	ft_strcat(res, s2);
	//not in the original implementation.
	free((void *)s1);
	return (res);
}
static char	*ft_strndup(const char *src, size_t len)
{
	unsigned int	src_len;
	char			*replica;
	unsigned int	i;

	i = 0;
	src_len = ft_strlen(src);
	if (len > src_len)
		len = src_len;
	replica = (char *)malloc((len + 1) * sizeof(char));
	if (replica == NULL)
		return (NULL);
	while (src[i] && i < len)
	{
		replica[i] = src[i];
		i++;
	}
	replica[i] = '\0';
	return (replica);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		len = 0;
		start = 0;
	}
	return (ft_strndup(s + start, len));
}

//above will go back to libft

static size_t	ft_strclen(const char *str, char cond)
{
	size_t	str_len;

	str_len = 0;
	while (str[str_len] != cond && str[str_len])
		str_len++;
	return (str_len);
}

static char	*clean_up(char *str)
{
	if (str != NULL)
	{
		printf("Trying to delete {%s}\n", str);
		free(str);
		str  = NULL;
	}
	//maybe return something different if you didn't free it?
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

char	*extr_line(char **board)
{
	char	cond;
	char	*line;
	char	*tmp;
	int		line_len;

	printf("In extr_line\n");

	//will receive everything read. The function is never  read unless  there is '\n'
	cond = '\n';
	line_len = ft_strclen(*board, cond);
	line = ft_substr(*board, 0, line_len + 1);
	if (ft_strclen(*board, '\0') > ft_strclen(*board, cond) + 1)
	{
		printf("Storing a new rem.\n");
		tmp = ft_substr(*board, ft_strclen(*board, cond) + 1, ft_strclen(*board, '\0'));
		//need to free the old board
		//free(board);
		//board = NULL;
		printf(" previous board {%s} & current board (tmp) {%s}\n", *board, tmp);
		//board = NULL;
		*board= tmp;
	}
	else
	{
		//free(board);
		//board = NULL;
		printf("we used all of board. It contained {%s} or what is in tmp {%s}\n", *board, tmp);
	}
	if (board == NULL)
		printf("Done. Board empty\n");
	else
		printf("Done. In board {%s}\n", *board);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	static char	*board[MAX_FD];
	int			nbr;


	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!(buff = ft_calloc(sizeof(char), (BUFFER_SIZE + 1))))
		return (NULL);
	nbr = 1;
	
	printf("checking board before we start\n");
	if (board[fd])
		printf("we remember {%s}.\n", board[fd]);
	else
		printf("Nothing in memory.\n");
	while (!board[fd] || (!in('\n', board[fd]) && nbr))
	{
		printf("We needed extra chars\n");
		ft_bzero(buff, BUFFER_SIZE + 1);
		if ((nbr = read(fd, buff, BUFFER_SIZE)) == -1)
		{
			free(buff);
			return (NULL);
		}
		board[fd] = ft_strjoin(board[fd], buff);
		//free(board[fd]);
		//board[fd] = tmp;
		printf("after join in board {%s}\n", board[fd]);
		printf("char read {%d}\n", nbr);
	}
	printf("finished the while in the main function.\n");
	free(buff);
	if (!nbr)
	{
		printf("nbr was zero, we reached EOF\n");
		line = board[fd];
		if  (!*board[fd])
		{
			free(board[fd]);
			board[fd]  = NULL;
		}
		return (line);
	}
	return (extr_line(&board[fd]));
}

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
	int count = 5;
	while(count--)
		printf("NEW LINE:  {%d} {%s}\n\n\n\n\n", count, get_next_line(fd));
	close(fd);
	return (0);
}
