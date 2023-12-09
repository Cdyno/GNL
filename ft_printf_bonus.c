/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:27:50 by olmohame          #+#    #+#             */
/*   Updated: 2023/12/10 00:02:16 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include "ft_printf.h"

/*static int	detect_flow(long num, int dig)
{
	//printf("field{%ld}, dig{%d}\n", num, dig);
	if (num > INT_MAX / 10)
		return (1);
	else if (num * 10 > (INT_MAX - dig))
		return (1);
	return (0);
}
*/
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

size_t	ft_strclen(const char *str, const char *condstr)
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

int	ft_write_chars(long *flags, char *c)
{
	int	i;

	i = 0;
	if (flags[0])
	{
		while (i < flags[0])
		{
			if (write(1, c, 1) == -1)
				return (-1);
			i++;
		}
	}
	return (i);
}

int	ft_putchar(char c, long *flags, int count)
{
	int	i;

	i = 0;
	flags[0]--;
	if (flags[1])
		i = ft_write_chars(flags, "0");
	else if (!flags[5])
		i = ft_write_chars(flags, " ");
	if (i == -1)
		return (-1);
	if (write(1, &c, 1) == -1)
		return (-1 * (count + 1));
	if (flags[5])
		i = ft_write_chars(flags, " ");
	if (i == -1)
		return (-1);
	return (i + 1);
}

int	ft_putnstr(const char *str, size_t n, int count)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (*str && i < n)
		{
			if (write(1, str++, 1) == -1)
				return (-1 * (count + 1));
			i++;
		}
	}
	return (i);
}

ssize_t	put_un_nbr(unsigned long nbr, size_t base_radix, char *base)
{
	ssize_t	ret;
	ssize_t	mod;
	ssize_t	sign;

	sign = 0;
	if (base_radix == 10 && nbr < 0)
	{
		sign = write(1, "-", 1);
		nbr = nbr * -1;
	}
	if (sign != -1 && nbr < base_radix)
		return (sign + write(1, &base[nbr], 1));
	else
	{
		if (sign != -1)
			mod = put_un_nbr(nbr / base_radix, base_radix, base);
		if (sign != -1 && mod != -1)
			ret = put_un_nbr(nbr % base_radix, base_radix, base);
	}
	if (sign == -1 || mod == -1 || ret == -1)
		return (-1);
	return (ret + mod + sign);
}

int	ft_putnbr(long nbr, long base_radix, char *base)
{
	int	ret;
	int	mod;
	int	sign;

	sign = 0;
	if (base_radix == 10 && nbr < 0)
		nbr = nbr * -1;
	if (nbr < base_radix)
		return (write(1, &base[nbr], 1));
	else
	{
		mod = ft_putnbr(nbr / base_radix, base_radix, base);
		if (mod != -1)
			ret = ft_putnbr(nbr % base_radix, base_radix, base);
	}
	if (mod == -1 || ret == -1)
		return (-1);
	return (ret + mod);
}

int	count_un_nbr(unsigned long nbr, size_t base_radix, char *base)
{
	int	mod;

	if (base_radix == 10 && nbr < 0)
		return (count_un_nbr(-nbr, base_radix, base));
	if (nbr < base_radix)
		return (1);
	else
	{
		mod = count_un_nbr(nbr / base_radix, base_radix, base);
		return (mod + count_un_nbr(nbr % base_radix, base_radix, base));
	}
}

int	countnbr(long nbr, long base_radix, char *base)
{
	int	mod;

	if (base_radix == 10 && nbr < 0)
		return (countnbr(-nbr, base_radix, base));
	if (nbr < base_radix)
		return (1);
	else
	{
		mod = countnbr(nbr / base_radix, base_radix, base);
		return (mod + countnbr(nbr % base_radix, base_radix, base));
	}
}

int	print_prefix(long *flags, int signed_pos, int hex)
{
	char	*prefix;
	int		i;

	i = 0;
	if (flags[3] > 0)
		prefix = " ";
	if (flags[4] > 0)
		prefix = "+";
	if (!signed_pos)
		prefix = "-";
	if (hex && flags[7])
		prefix = "0X";
	else if (hex && !flags[7])
		prefix = "0x";
	if ((flags[3] + flags[4]) > 0 || !signed_pos || flags[2] * hex)
	{
		if (write(1, prefix, 1 + flags[2] * hex) == -1)
			return (-1);
		i = (1 + flags[2] * hex);
	}
	return (i);
}

long	ft_max(long len, long *flags)
{
	if (flags[8] > len)
		return (flags[8]);
	return (len);
}
int	ft_form(int len, int signed_pos, int hex, long *flags)
{
	int	i;
	int j;
	int	ret;
	int ret_p;

	i = 0;
	j =  0;
	ret_p = 0;
	flags[0] = flags[0] - (ft_max(len, flags) + (flags[3] || flags[4]) \
	* signed_pos + !signed_pos + flags[2] * hex * 2) + flags[6] * flags[9]*!flags[8];
	if (!(flags[1] + flags[5]))
		i = ft_write_chars(flags, " ");
	if (i == -1)
		return (-1);
	ret = print_prefix(flags, signed_pos, hex);
	if (ret == -1)
		return (-1);
	if (flags[1])
		j = ft_write_chars(flags, "0");
	if (j == -1)
		return (-1);
	if (!flags[5])//gjkjhjjb
		flags[0] = 0;
	if (flags[6])
	{
		while (ret_p < (flags[8] - len))
		{
			if (write(1, "0", 1) == -1)
				return (-1);
			ret_p++;
		}
	}
	return (i + j + ret + ret_p);
}

int	ft_putnbr_base(void *ptr, char *base, int sign, long *flags, int count)
{
	int	base_radix;
	int	ret;
	int	ret_f;
	int	ret_s;

	ret = 0;
	base_radix = ft_strclen(base, "\0");
	if (sign == 0)
	{
		flags[9] = (unsigned long)ptr == 0;
		ret_f = ft_form(count_un_nbr((unsigned long)ptr, base_radix, base), \
		(unsigned long)ptr >= 0, (base_radix == 16) \
		&& (unsigned long)ptr != 0, flags);
		if (!(((long)ptr == 0) && (flags[6] + flags[8]) == 1) && ret_f != -1)
			ret = put_un_nbr((unsigned long)ptr, base_radix, base);
		if (ret_f != -1 && ret != -1)
			ret_s = ft_write_chars(flags, " ");
	}
	else
	{
		flags[9] = (long)ptr == 0;
		ret_f = ft_form(countnbr((long)ptr, base_radix, base), \
		(long)ptr >= 0, 0, flags);
		if (!(((long)ptr == 0) && (flags[6] + flags[8]) == 1) && ret_f != -1)
			ret = ft_putnbr((long)ptr, base_radix, base);
		if (ret_f != -1 && ret != -1)
			ret_s = ft_write_chars(flags, " ");
	}
	if (ret_f == -1 || ret == -1 || ret_s == -1)
		return (-1 * (count + 1));
	return (ret_f + ret + ret_s);
}

int	ft_putptr(unsigned long ptr, long *flags, int count)
{
	int	ret;
	int	i;

	i = 0;
	flags[0] = flags[0] - (count_un_nbr(ptr, 16, "0123456789abcdef") + 2);
	if (!(flags[1] + flags[5]))
		i = ft_write_chars(flags, " ");
	if (i == -1)
		return (-1* (count + 1));
	if (write(1, "0x", 2) == -1)
		return (-1 * (count + 1));
	if (flags[1])
		i = ft_write_chars(flags, "0");
	if (i == -1)
		return (-1 * (count +  1));
	ret = put_un_nbr(ptr, 16, "0123456789abcdef");
	if (ret == -1)
		return (-1 * (count + 1));
	if (flags[5])
		i = ft_write_chars(flags, " ");
	if (i == -1)
		return (-1 * (count + 1));
	return (ret + i + 2);
}

long	ft_min(long len, long *flags)
{
	if ((flags[8] + flags[6]) > 0 && flags[8] < len)
		return (flags[8]);
	return (len);
}

int	ft_putstr(char *str, long *flags, int count)
{
	int		i;
	long	len;
	int		ret;

	if (!str)
		len = 6;
	else
		len = ft_strclen(str, "\0");
	i = 0;
	len = ft_min(len, flags);
	flags[0] -= len;
	if (flags[1])
		i = ft_write_chars(flags, "0");
	else if (!flags[5])
		i = ft_write_chars(flags, " ");
	if (i == -1)
		return (-1 * (count + 1));
	if (!str)
		ret = ft_putnstr("(null)", len, count);
	else
		ret = ft_putnstr(str, len, count);
	if (ret == -1)
		return (-1 * (count + 1));
	if (flags[5])
		i = ft_write_chars(flags, " ");
	if (i == -1)
		return (-1 * (count + 1));
	return (i + ret);
}

int	ft_put_cor_str(const char *str, const char *last, long *flags, int count)
{
	int		i;
	int		ret;
	int		len;

	i = 0;
	len = ft_strclen(str, last) + 1;
	flags[0] = flags[0] - 1;
	if (flags[1])
		i = ft_write_chars(flags, "0");
	else if (!flags[5])
		i = ft_write_chars(flags, " ");
	if (i == -1)
		return (-1 * (count + 1));
	ret = ft_putnstr(str, len, count);
	if (flags[5])
		i = ft_write_chars(flags, " ");
	if (i == -1)
		return (-1 * (count + 1));
	return (i + ret);
}

static int in(char c, const char *str)
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

int	match_and_print(va_list *ptr, char spef, long *flags, int count)
{
	if (spef == 'c')
		return (ft_putchar(va_arg(*ptr, int), flags, count));
	if (spef == 's')
		return (ft_putstr(va_arg(*ptr, char *), flags, count));
	if (spef == 'p')
		return (ft_putptr((unsigned long)va_arg(*ptr, void *), flags, count));
	if (spef == 'd')
		return (ft_putnbr_base((void *)(long) \
					va_arg(*ptr, int), "0123456789", 1, flags, count));
	if (spef == 'i')
		return (ft_putnbr_base((void *)(long) \
					va_arg(*ptr, int), "0123456789", 1, flags, count));
	if (spef == 'u')
		return (ft_putnbr_base((void *)(unsigned long) \
					va_arg(*ptr, unsigned int), "0123456789", 0, flags, count));
	if (spef == 'x')
		return (ft_putnbr_base((void *)(unsigned long) \
					va_arg(*ptr, unsigned int), \
					"0123456789abcdef", 0, flags, count));
	if (spef == 'X')
		return (ft_putnbr_base((void *)(unsigned long) \
					va_arg(*ptr, unsigned int), \
					"0123456789ABCDEF", 0, flags, count));
	else
		return (ft_putchar('%', flags, count));
}

int	read_num(const  char *start, long *field)
{
	int	i;

	i = 0;
	*field = 0;
	while (start[i] && ft_isdigit(start[i]))
	{
	/*	if (detect_flow(*field, start[i] - '0'))  //overflow
		{
			printf("over");
			*field = -1;
			i++;
			while (start[i] && ft_isdigit(start[i]))
					i++;
			break ;
		}*/
		*field = *field * 10 + start[i++] - '0';
	}
	return (i);
}

int	store_flags(long *flags, va_list *ptr, const char *c)
{
	if (*c == '*')
		flags[0] = (long)va_arg(*ptr, int);
	else if (*c == '0')
		flags[1] = 1;
	else if (*c == '#')
		flags[2] = 1;
	else if (*c == ' ')
		flags[3] = 1;
	else if (*c == '+')
		flags[4] = 1;
	else if (*c == '-')
		flags[5] = 1;
	else if (*c == '.')
		flags[6] = 1;
	if (c[0] == '.' && c[1] && ft_isdigit(c[1]))//c[1] != '0'
		return (1 + read_num(&c[1], &flags[8]));
	return (1);
}

void	normalize_flags(long *flags, char c)
{
	if (c == 'X')
	{
		flags[7] = 1;
	}
	if (flags[5])
		flags[1] = 0;
	if (flags[6])
	{
		flags[1] = 0;
		//flags[5] = 0;
	}
}
/*
void	prec_normalize_flags(long *flags, char c)
{
	if (c == 'X')
	{
		flags[7] = 1;
	}
	if (flags[5])
		flags[1] = 0;
	if (flags[6])
	{
		//zeroes  = flags[6] - length of the thing;
	}
	if (flags[6] > flags[0])
		flags[0] = 0;//no spaces
}*/

int	validate(va_list *ptr, const char *start, const char *last, int count)
{
	int			i;
	long		fl[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	i = 0;
	while (in(start[i], "*0# +-.") || ft_isdigit(start[i]))
	{
		if (ft_isdigit(start[i]) && start[i] != '0')
			i += read_num(&start[i], &fl[0]);
		else
			i += store_flags(fl, ptr, &start[i]);
	//	if (fl[0] == -1 || fl[8]  == -1)
	//		return (-1);
	}
	//printf("finished flagsf0{%ld}, f8{%ld}", fl[0], fl[8]);
	normalize_flags(fl, start[i]);
	if (!start[i])
		return (0);
	else if (!in(start[i], "cspdiuxX%"))
		return (ft_put_cor_str(&start[i], last, fl, count));
	else
		return (match_and_print(ptr, start[i], fl, count));
}

int	ft_printf(const char *str, ...)
{
	int			count;
	size_t		len;
	const char	*start;
	const char	*last;
	va_list		ptr;

	count = 0;
	va_start(ptr, str);
	while (*str)
	{
		start = ft_strspef(str, "%");
		len = ft_strclen(str, start);
		count += ft_putnstr(str, len, count);
		str += len + 1;
		if (count == -1 || !start)
			break ;
		last = ft_strspef(str, "cspdiuxX%");
		count += validate(&ptr, start + 1, last, count);
		str = last + 1;
		if (count == -1 || !last)
			break ;
	}
	va_end(ptr);
	return (count);
}
/*
int	main(void)
{
	int	num;
	//int	num1;
	//int	width;

	num = 8;
	//num1 = 100;
	//width = 10;
	//printf("%1$*2$d%3$*2$d",num1, width, num);
	//printf("nfgt{%c}donec{%*d}\n", 'o', num, 10203);
	
	num = printf("{ww%*hhdkkkk%cmm}", 5);//, 10, 'c');
	printf("OG count {%d}\n", num);
	
	num = printf("{hey% #y#}");//, 5, 10, 'c');//print y and the second #.
	printf("OG count {%d}\n", num);

	num = ft_printf("{hey%*#}");//, 5, 10, 'c');
	printf("FT count {%d}\n", num);
	
	num = printf("{ww%hh**dkkkk%cmm}", 5, 10, 'c');
	printf("OG count {%d}\n", num);
	
	num = ft_printf("{ww%hh**dkkkk%cmm}", 5, 10, 'c');
	printf("FT count {%d}\n", num);
	//It skips %h regardless of parameters existing or not.
	num = printf("{ww%+  #dkk}", 42, 19);
	printf("OG count {%d}\n", num);

	num = printf("{ww%y+  #dkk}", 42, 19);//If the first chaar after % wasn't a specifier then treat the rest as a normal character
	printf("OG count {%d}\n", num);

	num = printf("{hey%she}\n", (void *)NULL);//, "Hello");
	printf("OG count {%d}\n", num);
	num = ft_printf("{hey%she}\n",(void *)NULL);
	printf("FT count {%d}\n", num);

	num = ft_printf("{ww%+  #dkk}", 42, 19);
	printf("FT count {%d}\n", num);

	num = ft_printf("{ww%y+  #dkk}", 42, 19);//If the first chaar after % wasn't a specifier then treat the rest as a normal character
	printf("FT count {%d}\n", num);
	

//	num = ft_printf("{ww%+  #ydkk}", 42, 19);//#ydkk
//	printf("FT count {%d}\n", num);
	//return (0);
//	num = printf("{hey%she}\n", (void *)NULL);//, "Hello");
//	printf("OG count {%d}\n", num);
//	num = ft_printf("{hey%she}\n",(void *)NULL);
//	printf("FT count {%d}\n", num);

	//int n = printf("OG{%0#5+*c}\n", 4, '2');
	//printf("%d", n);
//	int n = ft_printf("FT{%0#5+*c}\n", -1, '2');
//	printf("%d", n);

//	int n = printf("OG{%#5+*d}\n", 6, 10);//"hey");
//	printf("%d", n);
//	int n1 = ft_printf("FT{%#5+*d}\n", 6, 10);//"hey");
//	printf("%d", n1);

25:     TEST(1, print(" %d ", 0));
49:     TEST(25, print(" %d ", LONG_MIN));
53:     TEST(29, print(" %d %d %d %d %d %d %d", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42));


	char	*str = " {%-2c} ";
	char 	a = '0';
	long 	b = 1;//LONG_MIN;
	long	c = 9;
	int 	n;
	
	n = printf(str, a);
	printf("{%d}\n", n);
	n = ft_printf(str, a);
	printf("{%d}\n", n);

	n = printf(str, b);
	printf("{%d}\n", n);
	n = ft_printf(str, b);
	printf("{%d}\n", n);

	n = printf(str, c);
	printf("{%d}\n", n);
	n = ft_printf(str, c);
	printf("{%d}\n", n);

	int a = 0;
	int b = -3;
	int c = 342;
	printf("{%d}, sign  {%d}, len {%d}\n", a, a < 0, ft_countnbr(a, 10, "0123456789"));
	printf("{%d}, sign  {%d}, len {%d}\n", b, b < 0, ft_countnbr(b, 10, "0123456789"));
	printf("{%d}, sign  {%d}, len {%d}\n", c, c < 0, ft_countnbr(c, 10, "0123456789"));
	char	*str = "%
	return (0);
}

53:     TEST(27, print(" %-11p %-12p ", INT_MIN, INT_MAX));
54:     TEST(28, print(" %-13p %-14p ", ULONG_MAX, -ULONG_MAX));

int main(void)
{
	char	*str = "d15{%0-#15d}";
	//char	*a = "";
	int		n;
	long num = 42;

	n = printf(str, num);//INT_MAX);
	printf("{%d}\n", n);
	n = ft_printf(str, num);//INT_MAX);
	printf("{%d}\n", n);

	str = "X15{%0#-15X}";
	num = 42;

	n = printf(str, num);//INT_MAX);
	printf("{%d}\n", n);
	n = ft_printf(str, num);//INT_MAX);
	printf("{%d}\n", n);

	str = "p15{%0-#15p}";
	char *a = "42";

	n = printf(str, a);//INT_MAX);
	printf("{%d}\n", n);
	n = ft_printf(str, a);//INT_MAX);
	printf("{%d}\n", n);

	str = "s15{%0-#15s}";
	//char *a = "42";

	n = printf(str, a);//INT_MAX);
	printf("{%d}\n", n);
	n = ft_printf(str, a);//INT_MAX);
	printf("{%d}\n", n);

	str = "c15{%0-#15c}";
	char c = '4';

	n = printf(str, c);
	printf("{%d}\n", n);
	n = ft_printf(str, c);
	printf("{%d}\n", n);
	return (0);
}

int main(void)
{
	char	*str = "%-10.4s";//" {%4s}";//" %04yd";//"%-06%";
	char	*a = "hey";
	int		n;
	//int a = 999;

	n = printf(str, a);
	printf("{%d}\n", n);
	n = ft_printf(str, a);
	printf("{%d}\n", n);

	str = "%-10.2s";//"%-06%";

	n = printf(str, a);
	printf("{%d}\n", n);
	n = ft_printf(str, a);
	printf("{%d}\n", n);

	char	*str = "%8.i";//"%10.2s";//"%-06%";
	int	a = 0;
	int n;

	n = printf(str, a);
	printf("{%d}\n", n);
	n = ft_printf(str, a);
	printf("{%d}\n", n);

	return (0);
}*/
