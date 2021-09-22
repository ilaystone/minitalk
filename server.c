/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 08:36:53 by ikhadem           #+#    #+#             */
/*   Updated: 2021/09/22 10:53:27 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <string.h>

char	*print_msg(char *msg)
{
	puts(msg);
	free(msg);
	return (NULL);
}

char	*ft_straddc_first(char c)
{
	char	*add;

	add = (char *)malloc(sizeof(char) * 2);
	if (!add)
		return (NULL);
	add[0] = c;
	add[1] = '\0';
	return (add);
}

char	*ft_straddc(char *str, char c)
{
	char	*add;
	int		i;

	if (!c)
		return (NULL);
	if (!str)
		return (ft_straddc_first(c));
	add = (char *)malloc(sizeof(char) * (strlen(str) + 2));
	if (!add)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (str[++i])
		add[i] = str[i];
	free(str);
	add[i++] = c;
	add[i] = '\0';
	return (add);
}

void	handler_sigusr(int signum, siginfo_t *info, void *context)
{
	static char c = 0xFF;
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
		if (c)
			msg = ft_straddc(msg, c);
		else
			msg = print_msg(msg);
		bits = 0;
		c = 0xFF;
	}
	if (kill(pid, SIGUSR1) == -1)
		exit (-1);
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
	printf("PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
