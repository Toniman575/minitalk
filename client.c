/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:07:30 by asadik            #+#    #+#             */
/*   Updated: 2026/03/29 20:45:06 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "libft/error_handling.h"
#include "libft/ft_printf/ft_printf.h"
#include "libft/libft.h"

#include <signal.h>
#include <stdbool.h>
#include <unistd.h>

static volatile t_state	g_state;

static void	handle_ack(int _)
{
	(void)_;
	g_state.ack = 1;
}

static int	transmit_bit(void)
{
	if (g_state.bit == 0)
		g_state.c = *g_state.str;
	if ((g_state.c >> g_state.bit) & 1)
		kill(g_state.server_pid, SIGUSR2);
	else
		kill(g_state.server_pid, SIGUSR1);
	if (++g_state.bit == 8)
	{
		if (g_state.c == '\0')
			return (1);
		g_state.str++;
		g_state.bit = 0;
	}
	return (0);
}

static void	init_state(int server_pid, char *str)
{
	g_state.server_pid = server_pid;
	g_state.bit = 0;
	g_state.c = 0;
	g_state.str = str;
	g_state.ack = 0;
	transmit_bit();
}

static bool	init(int argc, char **argv)
{
	t_result			server_pid;

	if (argc != 3)
		return (ft_printf("Wrong number of Arguments\n"), false);
	server_pid = ft_atoi(argv[1]);
	if (server_pid.type == INT)
	{
		if (server_pid.value.n <= 0)
			return (ft_printf("Server PID Error: Please enter a PID > 0.\n")
				, false);
		init_state(server_pid.value.n, argv[2]);
	}
	else
		return (ft_printf("Server PID Error: %s\n", server_pid.value.error)
			, false);
	return (true);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	sa.sa_handler = handle_ack;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	if (!init(argc, argv))
		return (1);
	while (1)
	{
		if (g_state.ack)
		{
			g_state.ack = 0;
			if (transmit_bit())
				break ;
		}
		else if (usleep(5000000) == 0)
			return (ft_printf("No response from Server."));
	}
	return (0);
}
