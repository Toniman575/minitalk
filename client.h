/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:13:15 by asadik            #+#    #+#             */
/*   Updated: 2026/03/29 19:27:29 by asadik           ###   ########.fr       */
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
	volatile sig_atomic_t	ack;
}				t_state;

#endif