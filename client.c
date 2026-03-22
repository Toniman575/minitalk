/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:07:30 by asadik            #+#    #+#             */
/*   Updated: 2026/03/22 18:02:57 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

int	main(int argc, char **argv)
{
	int	server_pid;

	(void)argc;
	server_pid = ft_atoi(argv[1]).value.n;
	kill(server_pid, SIGUSR1);
	kill(server_pid, SIGUSR2);
}