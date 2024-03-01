/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 02:04:37 by nkannan           #+#    #+#             */
/*   Updated: 2024/03/01 10:21:56 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "minitalk_bonus.h"

static volatile sig_atomic_t	g_ack_received = ACK_NOT_RECEIVED;

static void	ack_handler(int signo)
{
	(void)signo;
	g_ack_received = ACK_RECEIVED;
}

static void	wait_for_ack(void)
{
	unsigned int	time_waited;

	time_waited = 0;
	while (g_ack_received == ACK_NOT_RECEIVED)
	{
		usleep(ACK_WAIT);
		time_waited += ACK_WAIT;
		if (time_waited >= ACK_TIMEOUT)
		{
			ft_putendl_fd("Error: timeout", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
	g_ack_received = ACK_NOT_RECEIVED;
}

static pid_t	get_server_pid(const char *pid_str)
{
	long	pid;

	if (*pid_str == '\0' || !ft_strall(pid_str, ft_isdigit))
		return (ft_printf("pid: %s\n", pid_str), -1);
	if (ft_strlen(pid_str) >= 10 && pid_str[0] - '0' >= 3)
		return (ft_printf("pid: %s\n", pid_str), -1);
	pid = ft_atoi(pid_str);
	if (pid <= 100 || pid > 99998)
		return (ft_printf("pid: %ld\n", pid), -1);
	return ((pid_t)pid);
}

static void	send_bits_to_server(pid_t server_pid, const char *msg)
{
	unsigned int	i;
	char			ch;
	int				kill_result;

	while (*msg)
	{
		ch = *msg++;
		i = CHAR_BIT_COUNT;
		while (i--)
		{
			if ((ch & (1U << i)) != 0)
				kill_result = kill(server_pid, SIGUSR2);
			else
				kill_result = kill(server_pid, SIGUSR1);
			if (kill_result == -1)
			{
				ft_putendl_fd("Error: failed to send signal", STDERR_FILENO);
				exit(EXIT_FAILURE);
			}
			wait_for_ack();
		}
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
	{
		ft_putendl_fd("Usage: client [server PID] [message]", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	server_pid = get_server_pid(argv[1]);
	if (server_pid == -1)
	{
		ft_putendl_fd("Error: invalid PID", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (signal(SIGUSR1, ack_handler) == SIG_ERR)
	{
		ft_putendl_fd("Error: cannot set signal handler", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	send_bits_to_server(server_pid, argv[2]);
	return (EXIT_SUCCESS);
}
