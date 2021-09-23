/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 08:37:20 by ikhadem           #+#    #+#             */
/*   Updated: 2021/09/23 15:57:10 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <string.h>

void	error(char *msg)
{
	if (msg)
		free(msg);
	ft_putstr_fd(2, "CLIENT: an error has occured!.\n");
	exit(EXIT_FAILURE);
}

int	send_null(int pid, char *msg)
{
	static int	i = 0;

	if (i++ != 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			error(msg);
		return (0);
	}
	return (1);
}

int	send_bit(int pid, char *str)
{
	static char		*msg = 0;
	static int		s_pid = 0;
	static int		bits = 0;

	if (str)
		msg = str;
	if (pid)
		s_pid = pid;
	if (msg[bits / 8])
	{
		if (msg[bits / 8] & (0x80 >> (bits % 8)))
		{
			if (kill(s_pid, SIGUSR2) == -1)
				error(msg);
		}
		else if (kill(s_pid, SIGUSR1) == -1)
			error(msg);
		++bits;
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
	else if (signum == SIGUSR2)
	{
		ft_putstr_fd(2, "CLIENT: server error!.\n");
		exit(EXIT_FAILURE);
	}
	if (end)
	{
		ft_putstr_fd(1, "CLIENT: message was sent successfully!.\n");
		exit (EXIT_SUCCESS);
	}
}

int	main(int ac, char **av)
{
	char	*msg;

	if (ac != 3 || !ft_strisdigit(av[1]))
	{
		ft_putstr_fd(2, "CLIENT: invalid arguments!.\n");
		ft_putstr_fd(2, "\tcorrect formsat : [./client <PID> \"<MSG>\"]\n");
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, handler_sigusr);
	signal(SIGUSR2, handler_sigusr);
	msg = ft_strdup(av[2]);
	if (!msg)
		error(0);
	send_bit(atoi(av[1]), msg);
	while (1)
		pause();
	return (0);
}
