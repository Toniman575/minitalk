/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:13:15 by asadik            #+#    #+#             */
/*   Updated: 2026/03/29 21:43:22 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <signal.h>

typedef struct s_state
{
	char					*buffer;
	int						capacity;
	int						index;
	char					c;
	int						bit;
	int						client_pid;
	volatile sig_atomic_t	received_sig;
	volatile sig_atomic_t	received_pid;
	volatile sig_atomic_t	idle;
}				t_state;

#endif