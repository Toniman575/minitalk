/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:13:15 by asadik            #+#    #+#             */
/*   Updated: 2026/03/24 17:40:41 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

typedef struct s_state
{
	char	*str;
	char	c;
	int		bit;
	int		client_pid;
}				t_state;

#endif