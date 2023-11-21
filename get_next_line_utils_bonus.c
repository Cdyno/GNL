/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 05:36:00 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/21 10:38:38 by olmohame         ###   ########.fr       */
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

char	*ft_strcat(char *dest, const char *src)
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
	return (res);
}

char	*ft_strndup(const char *src, size_t len)
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
