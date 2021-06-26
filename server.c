/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:43:11 by agirona           #+#    #+#             */
/*   Updated: 2021/06/26 14:12:27 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		traduction(int signumber, char *tmp)
{
	static int		i = 0;
	static char		msg = 0;

	if (i < 8)
	{
		msg = (msg << 1) + (signumber == SIGUSR1);
		i++;
	}
	if (i == 8)
	{
		i = 0;
		tmp[0] = msg;
		msg = 0;
		return (1);
	}
	return (0);
}

void	send_message(int server_pid, char *msg)
{
	int		i;
	int		bits;

	i = 0;
	while (msg[i])
	{
		bits = 0;
		while (bits < 8)
		{
			if ((msg[i] >> (7 - bits)) & 1)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			usleep(256);
			bits++;
		}
		i++;
	}
}

void	handler(int signumber)
{
	static char		client_pid[6] = {'\0'};
	static int		i = 0;
	static int		count = 0;
	char			tmp;
	int				ret;

	tmp = '\0';
	ret = traduction(signumber, &tmp);
	while (ret == 1 && i >= 0 && i < 5)
	{
		if (ret == 1)
			client_pid[i++] = tmp;
		if (ret == 1 && tmp == '\0')
		{
			count++;
			i = 5;
		}
		ret = 0;
	}
	if (i == 5)
		i = -1;
	else if (i == -1)
	{
		if (ret == 1 && tmp == '\0')
			count++;
		ft_putchar(tmp);
	}
	if (count == 2)
	{
		send_message(ft_atoi(client_pid), "Message correctement recu !");
		i = 0;
		count = 0;
		while (i < 6)
			client_pid[i++] = '\0';
		i = 0;
	}
}

int		main(void)
{
	int		end;
	pid_t	pid;

	end = 0;
	pid = getpid();
	ft_putnbr(pid);
	ft_putchar(' ');
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
	return (1);
}
