/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 08:36:53 by ikhadem           #+#    #+#             */
/*   Updated: 2021/09/23 15:40:53 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <string.h>

void	error(int pid, char *str)
{
	if (str)
		free(str);
	ft_putstr_fd(2, "SERVER: unexpected error.\n");
	kill(pid, SIGUSR2);
	exit(EXIT_FAILURE);
}

char	*print_msg(char *msg)
{
	ft_putstr_fd(1, msg);
	ft_putstr_fd(1, "\n");
	free(msg);
	return (NULL);
}

void	handler_sigusr(int signum, siginfo_t *info, void *context)
{
	static char	c = 0xFF;
	static int	bits = 0;
	static int	pid = 0;
	static char	*msg = 0;

	(void)context;
	if (info->si_pid)
		pid = info->si_pid;
	if (signum == SIGUSR1)
		c ^= 0x80 >> bits;
	else if (signum == SIGUSR2)
		c |= 0x80 >> bits;
	if (++bits == 8)
	{
		if (c != '\0')
			msg = ft_straddc(msg, c);
		else
			msg = print_msg(msg);
		bits = 0;
		c = 0xFF;
	}
	if (kill(pid, SIGUSR1) == -1)
		error(pid, msg);
}

int	main(void)
{
	struct sigaction	sa_signal;
	sigset_t			mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	sa_signal.sa_handler = 0;
	sa_signal.sa_flags = SA_SIGINFO;
	sa_signal.sa_mask = mask;
	sa_signal.sa_sigaction = handler_sigusr;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	ft_putstr_fd(1, "PID: ");
	ft_putnbr(getpid());
	ft_putstr_fd(1, "\n");
	while (1)
		pause();
	return (0);
}
