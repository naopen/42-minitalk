/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 02:04:58 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/28 07:48:23 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "minitalk.h"

// Handler that receives bits sent from the client and
//  assembles them into characters.
// Called every time a bit is received from the client.
// Shifts the received bits to the left and adds the new bit.
// If signo is SIGUSR2, set the least significant bit to 1.
// (For example, the ASCII code for the character 'A' is 01000001.
//  The client sends these 8 bits to the server one by one.)
// (The first bit is 0, so SIGUSR1 is sent.
//  The next bit is 1, so SIGUSR2 is sent.)
// Once all the bits for a character are received,
//  output the character and reset the variables.
// Record the client's PID and notify the client of the successful reception.
// If an error occurs while notifying the client of the successful reception,
//  output the error and terminate.

static void	receive_bit(int signo, siginfo_t *info, void *context)
{
	static char		current_char = 0;
	static int		bits_received = 0;
	static pid_t	client_pid = 0;

	(void)context;
	current_char <<= 1;
	if (signo == SIGUSR2)
		current_char |= 1;
	bits_received++;
	if (bits_received == CHAR_BIT_COUNT)
	{
		write(STDOUT_FILENO, &current_char, 1);
		if (current_char == '\0')
			write(STDOUT_FILENO, "\n", 1);
		current_char = 0;
		bits_received = 0;
	}
	if (info->si_pid != 0)
		client_pid = info->si_pid;
	if (client_pid != 0 && kill(client_pid, SIGUSR1) == -1)
	{
		ft_putendl_fd("Error: failed to send signal", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

// Server's main function.
// Sets up signal handler and waits for signals in an infinite loop.
// First, displays the PID of this process.
// Next, initializes the sigaction structure
//  and sets it to indicate no signals are blocked.
// Sets the SA_SIGINFO flag in sa_flags
//  so the system can pass additional information to the handler function.
// Sets the receive_bit function as the signal handler.
// Actually sets the signal handlers
//  for SIGUSR1 and SIGUSR2 using the sigaction function.

int	main(void)
{
	struct sigaction	act;

	ft_printf("Server PID: %d\n", getpid());
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = receive_bit;
	if (sigaction(SIGUSR1, &act, NULL) == -1 || sigaction(SIGUSR2, &act,
			NULL) == -1)
	{
		ft_putendl_fd("Error: unable to set signal handler", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	return (0);
}
