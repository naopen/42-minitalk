/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 04:42:44 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/21 04:50:28 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (result > LONG_MAX / 10 || (result == LONG_MAX / 10 && (*str
					- '0') > LONG_MAX % 10))
		{
			return ((sign == -1) ? INT_MIN : INT_MAX);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (int)(sign * result);
}
