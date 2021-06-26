/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:51:16 by agirona           #+#    #+#             */
/*   Updated: 2021/06/26 14:12:29 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_message(int server_pid, char *msg)
{
	int		i;
	int		bits;
	int		len;

	i = 0;
	len = ft_strlen(msg);
	while (i <= (int)ft_strlen(msg))
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
	static int		i = 0;
	static char		msg = 0;

	if (i < 8)
	{
		msg = (msg << 1) + (signumber == SIGUSR1);
		i++;
	}
	if (i == 8)
	{
		ft_putchar(msg);
		i = 0;
		msg = 0;
	}
}

void	send_signal(int server_pid, char *msg)
{
	char	*str;
	int		i;
	int		d;
	char	*mpid;

	i = 0;
	d = 0;
	str = msg;
	mpid = ft_itoa(getpid());
	if (mpid == NULL)
		return ;
	ft_putstr("pid = ");
	ft_putstr(mpid);
	send_message(server_pid, mpid);
	free(mpid);
	send_message(server_pid, msg);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
}

int		main(int argc, char **argv)
{
	if (argc == 3)
		send_signal(ft_atoi(argv[1]), argv[2]);
	else
		ft_putstr("Usage : client <pid> <message>");
}
