/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 16:11:48 by asadik            #+#    #+#             */
/*   Updated: 2026/03/24 15:13:44 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf/ft_printf.h"
#include "libft/libft.h"
#include "server.h"

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

t_state	g_state;

void	signal_handler(int signum, siginfo_t *info, void *_)
{
	(void)_;
	if (info->si_pid != g_state.client_pid)
	{
		g_state.client_pid = info->si_pid;
		g_state.bit = 0;
		g_state.c = 0;
	}
	if (signum == SIGUSR1)
		g_state.c = g_state.c & ~(1 << g_state.bit);
	else if (signum == SIGUSR2)
		g_state.c = g_state.c | (1 << g_state.bit);
	g_state.bit++;
	if (g_state.bit == 8)
	{
		ft_putchar_fd(g_state.c, 1);
		g_state.c = 0;
		g_state.bit = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("%d\n", getpid());
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	g_state.bit = 0;
	g_state.c = 0;
	while (1)
		if (!sleep(30))
			exit(0);
	return (0);
}
