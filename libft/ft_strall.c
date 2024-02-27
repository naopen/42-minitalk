/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 06:21:08 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/28 06:22:25 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Apply the function f to all characters in the string str.

int	ft_strall(const char *str, int (*f)(int))
{
	if (!str || !f)
		return (0);
	while (*str)
	{
		if (!f(*str))
			return (0);
		str++;
	}
	return (1);
}
