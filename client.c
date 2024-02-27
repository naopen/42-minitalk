/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 02:04:37 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/27 12:59:56 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_ack;

void	receive_ack(int signum)
{
	g_ack = 1;
	(void)signum;
}

void	setup_signals(struct sigaction *act)
{
	act->sa_handler = receive_ack;
	sigemptyset(&act->sa_mask);
	act->sa_flags = 0;
	sigaction(SIGUSR1, act, NULL);
	sigaction(SIGUSR2, act, NULL);
}

void	send_char_as_bits(int pid, char ch)
{
	int	bit_index;

	bit_index = 7;
	while (bit_index >= 0)
	{
		if (ch & (1 << bit_index))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit_index--;
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	act;

	if (argc != 3)
		return (ft_printf("Usage: %s [PID] [string]\n", argv[0]), ERROR);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (ft_printf("Invalid PID\n"), ERROR);
	setup_signals(&act);
	while (*argv[2])
	{
		g_ack = 0;
		send_char_as_bits(pid, *argv[2]++);
		while (!g_ack)
			pause();
	}
	send_char_as_bits(pid, '\0');
	while (!g_ack)
		pause();
	return (SUCCESS);
}
