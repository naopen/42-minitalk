/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 02:04:37 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/21 04:31:42 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char_as_bits(int pid, char ch)
{
	int	bit_index;

	bit_index = 0;
	while (bit_index < 8)
	{
		if (ch & 0x01)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		ch >>= 1;
		usleep(100);
		bit_index++;
	}
}

void	handler(int signum, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (signum == SIGUSR1)
		return ;
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	act;

	if (argc != 3)
	{
		ft_printf("Usage: %s [PID] [string]\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid < 100)
	{
		ft_printf("Invalid PID\n");
		return (1);
	}
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = SIG_IGN;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (*argv[2])
	{
		send_char_as_bits(pid, *argv[2]++);
		pause();
	}
	send_char_as_bits(pid, '\0');
	pause();
	return (0);
}
