/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 02:04:37 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/28 06:26:52 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "minitalk.h"

// サーバーからのACKを受け取ったかどうかを示すフラグ
// static: このファイル内でのみ有効
// volatile: コンパイラが最適化を行わないようにする
// sig_atomic_t: シグナルハンドラ内で安全にアクセスできる整数型

static volatile sig_atomic_t	g_ack_received = ACK_NOT_RECEIVED;

// サーバーからのACKシグナルを受け取った際に呼ばれる関数

static void	ack_handler(int signo)
{
	(void)signo;
	g_ack_received = ACK_RECEIVED;
}

// サーバーからのACKが来るまで待機する関数
// 一定時間経過してもACKが来ない場合はエラーを出力して終了
// タイムアウトしなかった場合はACKの受信フラグをリセットし、次のACKを待機する準備をする

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

// 文字列からPIDを解析し、有効なPIDを返す関数
// もしpid_strを全桁チェックし、数字以外の文字が含まれていたらエラーを出力して終了

static pid_t	get_server_pid(const char *pid_str)
{
	long	pid;

	if (*pid_str == '\0' || !ft_strall(pid_str, ft_isdigit))
		return (printf("pid: %s\n", pid_str), -1);
	pid = ft_atoi(pid_str);
	if (pid <= 0 || pid > INT_MAX)
		return (printf("pid: %ld\n", pid), -1);
	return ((pid_t)pid);
}

// サーバーにメッセージのビットを送信する関数
// メッセージの各文字をビットに分解し、左から右へと送信する
// シグナルの送信に失敗した場合はエラーを出力して終了
// 送信したビットごとにACKの受信を待機する

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

// クライアントのメイン関数
// 引数の数が正しくない場合はエラーを出力して終了
// サーバーのPIDを解析し、無効なPIDの場合はエラーを出力して終了
// SIGUSR1シグナルのハンドラを設定し、メッセージをサーバーに送信する

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
