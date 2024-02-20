/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 02:04:58 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/21 05:09:47 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int signum, siginfo_t *info, void *ucontext)
{
	static char	ch = 0;
	static int	bit_index = 0;

	if (signum == SIGUSR1)
		ch |= (1 << (7 - bit_index));
	else if (signum == SIGUSR2)
		ch &= ~(1 << (7 - bit_index));
	if (++bit_index == 8)
	{
		ft_printf("%c", ch);
		if (ch == '\0')
			ft_printf("\n");
		ch = 0;
		bit_index = 0;
		kill(info->si_pid, SIGUSR1);
	}
	(void)ucontext;
}

void	exit_handler(int signum)
{
	(void)signum;
	ft_printf("Server is shutting down.\n");
	exit(SUCCESS);
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

	struct sigaction act_exit;
	act_exit.sa_handler = exit_handler;
	sigaction(SIGINT, &act_exit, NULL);

	while (1)
		pause();
	return (SUCCESS);
}
