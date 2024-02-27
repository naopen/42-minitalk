/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:23:55 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/28 00:26:38 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <limits.h>

size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);

#endif