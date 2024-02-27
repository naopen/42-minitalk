/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:42:44 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/21 06:00:44 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static const char	*skip_whitespace_and_sign(const char *str, int *sign)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	return (str);
}

static long	parse_long(const char *str, int sign)
{
	long	result;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (result > LONG_MAX / 10 || (result == LONG_MAX / 10 && (*str
					- '0') > LONG_MAX % 10))
		{
			if (sign == -1)
				return (INT_MIN);
			else
				return (INT_MAX);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	str = skip_whitespace_and_sign(str, &sign);
	result = parse_long(str, sign);
	return ((int)(result * sign));
}
