/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 16:11:48 by asadik            #+#    #+#             */
/*   Updated: 2026/03/22 18:06:42 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf/ft_printf.h"

#include <unistd.h>
#include <signal.h>


void signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1)
		ft_printf("Received bit 0 from PID %d\n", info->si_pid);
	else if (signum == SIGUSR2)
		ft_printf("Received bit 1 from PID %d\n", info->si_pid);
}

int main(void)
{
	struct sigaction	sa;
	
	ft_printf("%d\n", getpid());
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;

	
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	
	while (1)
		pause();
	
	return 0;
}