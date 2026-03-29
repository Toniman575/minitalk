/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:07:30 by asadik            #+#    #+#             */
/*   Updated: 2026/03/29 17:51:04 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "libft/error_handling.h"
#include "libft/ft_printf/ft_printf.h"
#include "libft/libft.h"

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static t_state	g_state;

static void	send_char(int sig)
{
	(void)sig;
	if (g_state.bit == 0)
		g_state.c = *g_state.str;
	if ((g_state.c >> g_state.bit) & 1)
		kill(g_state.server_pid, SIGUSR2);
	else
		kill(g_state.server_pid, SIGUSR1);
	g_state.bit++;
	if (g_state.bit == 8)
	{
		if (g_state.c == '\0')
			exit(0);
		g_state.str++;
		g_state.bit = 0;
	}
}

int	main(int argc, char **argv)
{
	t_result	server_pid;

	signal(SIGUSR1, send_char);
	if (argc != 3)
		return (ft_printf("Wrong number of Arguments\n"), 0);
	server_pid = ft_atoi(argv[1]);
	if (server_pid.type == INT)
	{
		g_state.server_pid = server_pid.value.n;
		if (g_state.server_pid <= 0)
			return (ft_printf("Server PID Error: Please enter a PID > 0.\n"));
		g_state.bit = 0;
		g_state.c = 0;
		g_state.str = argv[2];
		send_char(SIGUSR1);
	}
	else
		return (ft_printf("Server PID Error: %s\n", server_pid.value.error), 0);
	while (1)
		if (!sleep(2))
			return (ft_printf("No response from Server."));
	return (0);
}
