/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 05:15:29 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/20 08:02:27 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	clean_up(char *str)
{
	if (!str)
	{
		free(str);
		str  = NULL;
	}
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

char	*extr_line(char *str)
{
	char	cond;
	char	*line;
	int		line_len;

	//will receive everything read. The function is never  read unless  there is '\n'
	cond = '\n';
	if (!str)
		return (str);
	if(!(line_len = ft_strclen(str, cond)))
			return (NULL);
	if (!(lines = (char *)ft_calloc(2, sizeof(char *))))
		return (NULL);
	//substr add a place for '\0' on it's own. i add +1 for '\n'because strclen stops before it.
	line = ft_substr(str, 0, line_len + 1);
	if (ft_strclen(str,'\0') > ft_strclen(str, cond))
	{
		//move by line length
		board = ft_substr(str, ft_strclen(str, cond) + 1, ft_strclen(str, '\0'));//until i add trim, i will be adding the length instead of 0 in start parameter
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	static char	*board;
	int			nbr;

	if (fd < 0 || fd > || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buff = ft_calloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (!board)
	{

	}
	while (!board || (!in('\n', board) && nbr))
	{
		if ((nbr = read(fd, buff, BUFFER_SIZE)) == -1)// || nbr == 0?
		{
			free(buff);
			//do i need to forget the associated board?
			return (NULL);
		}
		//The case where i have chars from previous read and now it is the EOF, break because join will  try to join an empty string.
		if (!nbr)
			break ;
		tmp = board;
		board = ft_strjoin(board, buff);
		free(tmp);
		tmp = NULL;
		ft_bzero(buff, BUFFER_SIZE + 1);

	}
	if (buff)
	{
		free(buff);
		buff = NULL;
	}
	//if nbr == 0, it means we reached the EOF and we don't need to process the string, we already have the line.
	if (!nbr)
	{
		line = board;
		free(board);
		//board = NULL;
		return (line);
	}
	return (0);//(extr_line(board));
}
