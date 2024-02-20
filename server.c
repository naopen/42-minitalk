/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 02:04:58 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/21 04:54:49 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int signum, siginfo_t *info, void *ucontext)
{
	static char	c = 0;
	static int	bit_index = 0;

	if (signum == SIGUSR1)
		c |= (1 << bit_index);
	else if (signum == SIGUSR2)
		c &= ~(1 << bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		ft_printf("%c", c);
		c = 0;
		bit_index = 0;
		kill(info->si_pid, SIGUSR1);
	}
	(void)ucontext;
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	act;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
