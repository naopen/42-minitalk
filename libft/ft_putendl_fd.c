/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:35:55 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/28 00:22:28 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Outputs the string ’s’ to the given file descriptor, followed by a newline.

void	ft_putendl_fd(char *str, int fd)
{
	if (!str)
		return ;
	ft_putstr_fd(str, fd);
	write(fd, "\n", 1);
}
