/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 02:04:37 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/28 07:53:16 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "minitalk.h"

// Flag indicating whether an ACK from the server has been received.
// static: Valid only within this file.
// volatile: Prevents the compiler from performing optimizations.
// sig_atomic_t:
//  An integer type that can be safely accessed within a signal handler.

static volatile sig_atomic_t	g_ack_received = ACK_NOT_RECEIVED;

// Function called when an ACK signal is received from the server.

static void	ack_handler(int signo)
{
	(void)signo;
	g_ack_received = ACK_RECEIVED;
}

// Function that waits for an ACK from the server.
// If the ACK does not arrive after a certain period of time,
//  outputs an error and terminates.
// If there is no timeout,
//  resets the ACK received flag and prepares to wait for the next ACK.

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

// Function that parses a PID from a string and returns a valid PID.
// If non-numeric characters are found upon checking all digits of pid_str,
//  outputs an error and terminates.
// If pid_str is empty, or if the converted PID is below 100 or above 99998,
//  outputs an error and terminates.

static pid_t	get_server_pid(const char *pid_str)
{
	long	pid;

	if (*pid_str == '\0' || !ft_strall(pid_str, ft_isdigit))
		return (printf("pid: %s\n", pid_str), -1);
	pid = ft_atoi(pid_str);
	if (pid <= 100 || pid > 99998)
		return (printf("pid: %ld\n", pid), -1);
	return ((pid_t)pid);
}

// Function to send the bits of a message to the server.
// Decomposes each character of the message into bits
//  and transmits them from left to right.
// (<< is the left shift operator, which moves bits to the left.)
// (For example, 1U << 2 takes binary 1, which is 0001,
//  and shifts it two bits to the left to become 0100.)
// (It determines
//  whether the i-th bit of ch is 1 by taking the bitwise AND with each bit.)
// (If the i-th bit of ch is 1, it sends SIGUSR2 (binary 1),
//  if it's 0, it sends SIGUSR1 (binary 0).)
// If the signal transmission fails, outputs an error and terminates.
// Waits for the reception of an ACK for each transmitted bit.

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

// Client's main function.
// If the number of arguments is incorrect, outputs an error and terminates.
// Parses the server's PID and if it's an invalid PID,
//  outputs an error and terminates.
// Sets the handler for the SIGUSR1 signal and sends the message to the server.

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
	signal(SIGUSR1, ack_handler);
	send_bits_to_server(server_pid, argv[2]);
	return (EXIT_SUCCESS);
}
