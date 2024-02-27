/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 02:30:32 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/28 06:31:59 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include "./libft/ft_printf/ft_printf.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define ACK_RECEIVED 1
# define ACK_NOT_RECEIVED 0

# define CHAR_BIT_COUNT 8
# define ACK_WAIT 10
# define ACK_TIMEOUT 1000000

int	ft_atoi(const char *str);

#endif