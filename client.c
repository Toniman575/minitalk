/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:07:30 by asadik            #+#    #+#             */
/*   Updated: 2026/03/24 14:31:33 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "libft/error_handling.h"
#include "libft/ft_printf/ft_printf.h"
#include "libft/libft.h"

#include <signal.h>
#include <unistd.h>

t_state	g_state;

void	send_char(int sig)
{
	int	index;
	int	bit;

	(void)sig;
	index = g_state.index;
	bit = g_state.bit;
	g_state.bit++;
	if (g_state.bit == 8)
	{
		g_state.index++;
		g_state.bit = 0;
	}
	if ((g_state.str[index] >> bit) & 1)
		kill(g_state.server_pid, SIGUSR2);
	else
		kill(g_state.server_pid, SIGUSR1);
}

int	main(int argc, char **argv)
{
	t_result	server_pid;

	signal(SIGUSR1, send_char);
	if (argc != 3)
		return (ft_printf("Wrong number of Arguments"), 0);
	server_pid = ft_atoi(argv[1]);
	if (server_pid.type == INT)
	{
		g_state.server_pid = server_pid.value.n;
		g_state.bit = 0;
		g_state.index = 0;
		g_state.str = argv[2];
		send_char(SIGUSR1);
	}
	else
		return (ft_printf("Server PID Error: %s\n", server_pid.value.error)
			, 0);
	while (g_state.str[g_state.index])
		pause();
}
