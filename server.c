/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 02:04:58 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/28 05:31:25 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "minitalk.h"

// クライアントから送られてくるビットを受け取り、文字を組み立てるハンドラ
// クライアントからのビットを受け取るたびに呼ばれる
// 受信したビットを左にシフトして、新しいビットを加える
// もしsignoがSIGUSR2なら最下位ビットを1に設定
// （たとえば、文字 'A' のASCIIコードは 01000001 です。クライアントは、この8ビットのシーケンスを一つずつサーバーに送信します。）
// （最初のビットは 0 なので、SIGUSR1 が送信されます。次のビットは 1 なので、SIGUSR2 が送信されます。）
// 1文字分のビットを受信したら、文字を出力し、変数をリセットする
// クライアントのPIDを記録し、クライアントに受信完了を通知する
// クライアントに受信完了を通知する際にエラーが発生したら、エラーを出力して終了
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

// サーバーのメイン関数
// シグナルハンドラを設定し、無限ループでシグナルを待機する
// まず、このプロセスのPIDを表示
// 次に、sigaction構造体を初期化し、ブロックするシグナルはないということを設定
// システムがシグナルに関する追加情報をハンドラ関数に渡せるように、sa_flags に SA_SIGINFO フラグを設定
// シグナルハンドラとして、receive_bit 関数を設定
// 実際にシグナル SIGUSR1 と SIGUSR2 に対するシグナルハンドラを、sigaction 関数で設定

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
