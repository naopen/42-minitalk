/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 02:04:37 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/21 05:21:30 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char_as_bits(int pid, char ch)
{
	int	bit_index;

	bit_index = 7; // 最上位ビットから開始
	while (bit_index >= 0)
	{
		if (ch & (1 << bit_index)) // 最上位ビットをチェック
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit_index--; // 次のビットへ
	}
}

// void send_utf8_as_bits(int pid, char *str)
// {
// 	while (*str)
// 		send_char_as_bits(pid, *str++);
// 	send_char_as_bits(pid, '\0');
// }

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
		return (ERROR);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf("Invalid PID\n");
		return (ERROR);
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
	return (SUCCESS);
}
