/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:51:16 by agirona           #+#    #+#             */
/*   Updated: 2021/06/26 17:28:15 by agirona          ###   ########lyon.fr   */
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
	if (signumber == SIGUSR1)
	{
		ft_putstr("Message recu avec succes");
		ft_putchar('\n');
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_putstr("Message failled");
		ft_putchar('\n');
		exit(EXIT_FAILURE);
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
	send_message(server_pid, mpid);
	free(mpid);
	send_message(server_pid, msg);
}

int		main(int argc, char **argv)
{
	if (argc == 3)
	{
		send_signal(ft_atoi(argv[1]), argv[2]);
		signal(SIGUSR1, handler);
		while (1)
			pause();
	}
	else
		ft_putstr("Usage : client <pid> <message>");
}
