/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:13:15 by asadik            #+#    #+#             */
/*   Updated: 2026/03/29 21:52:46 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <signal.h>

typedef struct s_state
{
	char					*str;
	int						bit;
	int						server_pid;
	char					c;
	int						idle;
	volatile sig_atomic_t	ack;
}				t_state;

#endif