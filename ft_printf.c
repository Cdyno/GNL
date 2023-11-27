/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:27:50 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/27 17:50:44 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

size_t	ft_strclen(const char *str, const char  *condstr)
{
	size_t	str_len;
	char	cond;

	str_len = 0;
	if (!condstr)
		cond = '\0';
	else
		cond = *condstr;
	while (str[str_len] != cond && str[str_len])
		str_len++;
	return (str_len);
}

int	ft_putchar_fd(char c, int fd, int count)
{
	if (write(fd, &c, 1)  == -1)
		return (-1 * (count + 1));
	return (1);
}

int	ft_putnstr_fd(const char *str, int fd, size_t n, int count)
{
	int		i;
	size_t	fail;

	i = 0;
	fail = 0;
	if (str)
	{
		while (*str && i < n)
		{
			if (write(fd, str++, 1) == -1)
			{
				fail = 1;
				i--;
			}
			i++;
		}
	}
	if (fail)
		return (-1 * (count + 1));
	//printf("the number of chars printed {%d} start {%s}\n", i, str);
	return (i);
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

const char	*ft_strspef(const char *str, const char *spef)
{
	while (*str)
	{
		if (in(*str, spef))
			return (str);
		str++;
	}
	return (0);
}

int	validate_and_write(const char *start, const char *last, size_t count)
{
	int	len;
	int			i;
	const char	*flags;
	const char	*spef;

	i = 1;
	flags = "*-0.# +";
	spef = "cspdiuxX%";
	//printf("the starting count {%d}\n", count);
	//len = ft_strclen(start, last);
	//if ()
	//printf("val|s{%s}, l{%s}, c{%zu}|\n", start, last, count);
	//printf("the start {%s}, last {%s}\n", start, last);
	while (in(start[i], flags))//i can start marking them on a list of available flags.
	{
		//printf("i{%d}, str{%c}.\n", i, start[i]);
		i++;
	}
	//read as much digits as possible and set it as width.
	//i++;
	while (in(start[i], flags))//i can start marking them on a list of available flags.
	{
		//printf("i{%d}, str{%c}.\n", i, start[i]);
		i++;
	}
	if (!in(start[i], spef))//width will be neglected if it occured without a specifier.
	{
		printf("start count {%d} from {%c}\n", count, start[i]);
		len = ft_strclen(&start[i], last) + 1;//if last was null we don't need +1
		if (!last)
			len--;
		printf("len {%d}\n", len);
		count = ft_putnstr_fd(&start[i], 1, len, count);
		printf("count after printing  {%d}\n",  count);
		return (count);
	}
//	else//valid flags followed by a specifier
//	{
//	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int			count;
	int			len;
	int			fail;
	const char	*spef;
	const char	*start;
	const char	*last;

	spef = "cspdiuxX%";
	count = 0;
	fail = 0;
	if (!str)
		return (0);
	while (*str)
	{
		start = ft_strspef(str, spef + 8);
		len = ft_strclen(str, start);
		//count += len;
		count += ft_putnstr_fd(str, 1, len, count);//ft_strclen(str, start));
		//printf("still in root\n");
		if (!start)//If no specifiers left in the string, print the chars then return count.
			return (count);
		str += len + 1;
		if (!*str)//If the first char after the specifier we found is the '\0' then stop the execution
			break ;
		if (count == -1)
			fail  =  1;
		if (*str == '%')
		{
			count  += ft_putchar_fd('%', 1, count);
			str++;
		}
		else
		{
		last = ft_strspef(str, spef);
		//if (!last)//"hey%y"
		//	continue ;
		//validate the specifier you found, from start till last (inclusive to both). 
		//printf("before val\n");
		count += validate_and_write(start, last, count);
		str += ft_strclen(start, last);//+ 1;
		}
		//printf("w{%d}, s{%s}\n", count, str);
		if (count == -1)
			fail = 1;
	}
	if (fail)
		count = -1;
	return (count);
}
int	main(void)
{
	int	num;
	int	num1;
	int	width;

	num = 8;
	num1 = 100;
	width = 10;
	//printf("%1$*2$d%3$*2$d",num1, width, num);
	//printf("nfgt{%c}donec{%*d}\n", 'o', num, 10203);
	/*
	num = printf("{ww%*hhdkkkk%cmm}", 5);//, 10, 'c');
	printf("OG count {%d}\n", num);*/
	
	/*num = printf("{hey% #y#}");//, 5, 10, 'c');//print y and the second #.
	printf("OG count {%d}\n", num);

	num = ft_printf("{hey%*#}");//, 5, 10, 'c');
	printf("FT count {%d}\n", num);*/
	/*
	num = printf("{ww%hh**dkkkk%cmm}", 5, 10, 'c');
	printf("OG count {%d}\n", num);
	
	num = ft_printf("{ww%hh**dkkkk%cmm}", 5, 10, 'c');
	printf("FT count {%d}\n", num);*/
	//It skips %h regardless of parameters existing or not.
/*	num = printf("{ww%+  #dkk}", 42, 19);
	printf("OG count {%d}\n", num);*/

/*	num = printf("{ww%y+  #dkk}", 42, 19);//If the first chaar after % wasn't a specifier then treat the rest as a normal character
	printf("OG count {%d}\n", num);*/

	num = printf("{%d}");//, "Hello");
	printf("OG count {%d}\n\n\n\n\n", num);

/*	num = ft_printf("{ww%+  #dkk}", 42, 19);
	printf("FT count {%d}\n", num);*/

/*	num = ft_printf("{ww%y+  #dkk}", 42, 19);//If the first chaar after % wasn't a specifier then treat the rest as a normal character
	printf("FT count {%d}\n", num);*/

//	num = ft_printf("{ww%+  #ydkk}", 42, 19);//#ydkk
//	printf("FT count {%d}\n", num);
	return (0);

	return (0);
}
