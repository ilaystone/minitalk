/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 08:37:20 by ikhadem           #+#    #+#             */
/*   Updated: 2021/09/22 11:09:39 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <string.h>

int	send_null(int pid, char *msg)
{
	static int	i = 0;

	if (i++ != 8)
	{
		kill(pid, SIGUSR1);
		return (0);
	}
	return (1);
}

int		send_bit(int pid, char *str)
{
	static char		*msg = 0;
	static int		s_pid = 0;
	static int		bits = -1;

	if (str)
		msg = strdup(str);
	if (!msg)
		exit (-1);
	if (pid)
		s_pid = pid;
	if (msg[++bits / 8])
	{
		if (msg[bits / 8] & (0x80 >> (bits % 8)))
		{
			kill(s_pid, SIGUSR2);
		}
		else
			kill(s_pid, SIGUSR1);
		return (0);
	}
	if (!send_null(s_pid, msg))
		return (0);
	free(msg);
	return (1);
}

void	handler_sigusr(int signum)
{
	int		end;

	end = 0;
	if (signum == SIGUSR1)
		end = send_bit(0, 0);
	if (end)
	{
		printf("MESSAGE SENT!!\n");
		exit (0);
	}
}

int	main(int ac, char **av)
{
	signal(SIGUSR1, handler_sigusr);
	signal(SIGUSR2, handler_sigusr);
	send_bit(atoi(av[1]), av[2]);
	while (1)
		pause();
	return (0);
}
