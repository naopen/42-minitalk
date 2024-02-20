/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 02:30:32 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/21 04:54:30 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "ft_printf/ft_printf.h"

# define ERROR -1
# define SUCCESS 0

void		send_char_as_bits(int pid, char ch);
void		handler(int signum, siginfo_t *info, void *ucontext);
void		sig_handler(int signum, siginfo_t *info, void *ucontext);

typedef struct s_communication
{
	char	current_char;
	int		bit_index;
	pid_t	client_pid;
}			t_communication;

#endif