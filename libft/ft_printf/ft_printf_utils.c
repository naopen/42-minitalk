/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 01:44:12 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/06 01:46:01 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	my_put_unsigned_nbr(unsigned int num)
{
	int	count;

	count = 0;
	if (num >= 10)
	{
		count += my_put_unsigned_nbr(num / 10);
		count += my_put_unsigned_nbr(num % 10);
	}
	else
		count += my_put_char(num + '0');
	return (count);
}

int	my_put_hex(unsigned long num, int cap)
{
	int	count;

	count = 0;
	if (num >= 16)
	{
		count += my_put_hex(num / 16, cap);
		count += my_put_hex(num % 16, cap);
	}
	else
	{
		if (num < 10)
			count += my_put_char(num + '0');
		else
		{
			if (cap == 0)
				count += my_put_char(HEXADECIMAL[num % 16]);
			else
				count += my_put_char(HEXADECIMAL_CAP[num % 16]);
		}
	}
	return (count);
}

int	my_put_pointer(void *ptr)
{
	int	count;

	count = 0;
	count += my_put_str("0x");
	count += my_put_hex((unsigned long)ptr, 0);
	return (count);
}

int	my_put_percent(void)
{
	my_put_char('%');
	return (1);
}
