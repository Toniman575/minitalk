/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 16:11:48 by asadik            #+#    #+#             */
/*   Updated: 2026/03/27 19:50:21 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf/ft_printf.h"
#include "libft/libft.h"
#include "server.h"

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

t_state	g_state;

static bool	next_char(void)
{
	char	current[2];
	char	*temp;

	if (!g_state.str)
	{
		g_state.str = ft_calloc(2, sizeof(char));
		if (!g_state.str)
			return (false);
		g_state.str[0] = g_state.c;
		g_state.str[1] = '\0';
		return (true);
	}
	current[0] = g_state.c;
	current[1] = '\0';
	temp = ft_strjoin(g_state.str, current);
	if (!temp)
		return (false);
	free(g_state.str);
	return (g_state.str = temp, true);
}

static void	ft_free(void **p)
{
	free(*p);
	*p = NULL;
}

static void	print(void)
{
	ft_printf("%s", g_state.str);
	ft_free((void **)&g_state.str);
}

static void	signal_handler(int signum, siginfo_t *info, void *_)
{
	(void)_;
	if (info->si_pid != g_state.client_pid)
	{
		g_state.client_pid = info->si_pid;
		g_state.bit = 0;
		g_state.c = 0;
		if (g_state.str)
			ft_free((void **)&g_state.str);
	}
	if (signum == SIGUSR1)
		g_state.c = g_state.c & ~(1 << g_state.bit);
	else if (signum == SIGUSR2)
		g_state.c = g_state.c | (1 << g_state.bit);
	g_state.bit++;
	if (g_state.bit == 8)
	{
		if (!next_char())
			exit(0);
		if (g_state.c == '\0')
			print();
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
	g_state.str = NULL;
	g_state.bit = 0;
	g_state.c = 0;
	while (1)
		if (!sleep(30))
			exit(0);
	return (0);
}
