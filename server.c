/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 02:04:58 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/27 21:41:17 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	sig_handler(int signum, siginfo_t *info, void *ucontext)
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
		if (kill(info->si_pid, SIGUSR1) == -1)
			exit(-1);
		ch = 0;
		bit_index = 0;
	}
	(void)ucontext;
}

static void	exit_handler(int signum)
{
	(void)signum;
	ft_printf("\nServer is shutting down.\n");
	exit(SUCCESS);
}

int	main(void)
{
	struct sigaction	act;
	struct sigaction	act_exit;

	ft_printf("Server PID: %d\n", getpid());
	act.sa_sigaction = sig_handler;
	act.sa_flags = SA_SIGINFO;
	act.sa_flags |= SA_RESTART;
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	act_exit.sa_handler = exit_handler;
	sigaction(SIGINT, &act_exit, NULL);
	while (1)
		pause();
	return (SUCCESS);
}
