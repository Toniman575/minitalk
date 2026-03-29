/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 16:11:48 by asadik            #+#    #+#             */
/*   Updated: 2026/03/29 21:56:27 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf/ft_printf.h"
#include "libft/libft.h"
#include "server.h"

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

static volatile t_state	g_state;

static void	append_to_buffer(char c)
{
	char	*new_buf;
	int		i;

	if (g_state.index >= g_state.capacity)
	{
		if (g_state.capacity == 0)
			g_state.capacity = 1024;
		else
			g_state.capacity *= 2;
		new_buf = malloc(g_state.capacity);
		if (!new_buf)
			exit(1);
		i = -1;
		while (++i < g_state.index)
			new_buf[i] = g_state.buffer[i];
		free(g_state.buffer);
		g_state.buffer = new_buf;
	}
	g_state.buffer[g_state.index++] = c;
}

static void	signal_handler(int signum, siginfo_t *info, void *_)
{
	(void)_;
	if ((g_state.client_pid != 0 && info->si_pid != g_state.client_pid)
		|| !g_state.idle)
		return ;
	g_state.received_sig = signum;
	g_state.received_pid = info->si_pid;
	g_state.idle = 0;
}

static void	reset_state(int pid)
{
	g_state.buffer = NULL;
	g_state.capacity = 0;
	g_state.index = 0;
	g_state.client_pid = pid;
	g_state.bit = 0;
	g_state.c = 0;
}

static void	process_signal(int sig, int pid)
{
	if (g_state.client_pid == 0)
		g_state.client_pid = pid;
	if (sig == SIGUSR1)
		g_state.c &= ~(1 << g_state.bit);
	else if (sig == SIGUSR2)
		g_state.c |= (1 << g_state.bit);
	if (++g_state.bit == 8)
	{
		append_to_buffer(g_state.c);
		if (g_state.c == '\0' && g_state.buffer)
		{
			ft_putstr_fd(g_state.buffer, 1);
			free(g_state.buffer);
			g_state.buffer = NULL;
			reset_state(0);
		}
		else
		{
			g_state.c = 0;
			g_state.bit = 0;
		}
	}
	g_state.idle = 1;
	g_state.received_sig = 0;
	kill(pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("%d\n", getpid());
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	reset_state(0);
	while (1)
	{
		if (g_state.received_sig != 0)
			process_signal(g_state.received_sig, g_state.received_pid);
		usleep(100);
		if (++g_state.idle > 200000)
		{
			if (g_state.buffer)
				free(g_state.buffer);
			return (0);
		}
	}
}
