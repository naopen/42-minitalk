/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:45:44 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/06 01:44:46 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += ft_format(ap, format[i]);
		}
		else
			count += my_put_char(format[i]);
		i++;
	}
	va_end(ap);
	return (count);
}

int	ft_format(va_list ap, const char format)
{
	if (format == 'c')
		return (my_put_char(va_arg(ap, int)));
	else if (format == 's')
		return (my_put_str(va_arg(ap, char *)));
	else if (format == 'd' || format == 'i')
		return (my_put_nbr(va_arg(ap, int)));
	else if (format == 'u')
		return (my_put_unsigned_nbr(va_arg(ap, unsigned int)));
	else if (format == 'x')
		return (my_put_hex(va_arg(ap, unsigned int), 0));
	else if (format == 'X')
		return (my_put_hex(va_arg(ap, unsigned int), 1));
	else if (format == 'p')
		return (my_put_pointer(va_arg(ap, void *)));
	else if (format == '%')
		return (my_put_percent());
	else
		return (0);
}

int	my_put_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	my_put_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (my_put_str("(null)"));
	while (str[i])
	{
		my_put_char(str[i]);
		i++;
	}
	return (i);
}

int	my_put_nbr(int num)
{
	int	count;

	count = 0;
	if (num == INT_MIN)
		return (my_put_str("-2147483648"));
	if (num < 0)
	{
		my_put_char('-');
		num *= -1;
		count++;
	}
	if (num >= 10)
	{
		count += my_put_nbr(num / 10);
		count += my_put_nbr(num % 10);
	}
	else
		count += my_put_char(num + '0');
	return (count);
}
