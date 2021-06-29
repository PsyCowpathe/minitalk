/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:43:11 by agirona           #+#    #+#             */
/*   Updated: 2021/06/29 17:15:23 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	traduction(int signumber, char *tmp, int print)
{
	static int		i = 0;
	static char		msg = '\0';

	if (i < 8)
	{
		msg = (msg << 1) + (signumber == SIGUSR1);
		i++;
	}
	if (i == 8)
	{
		if (print == 5)
			ft_putchar(msg);
		tmp[0] = msg;
		i = 0;
		msg = '\0';
		return (1);
	}
	return (0);
}

void	handler(int signumber)
{
	static char		client_pid[6] = {'\0'};
	static int		i = 0;
	static int		count = 0;
	char			tmp;
	int				ret;

	ret = traduction(signumber, &tmp, i);
	if (ret == 1 && tmp == '\0')
		count++;
	while (ret == 1 && i >= 0 && i < 5 && ret--)
		client_pid[i++] = tmp;
	if (count == 2)
	{
		ft_putchar('\n');
		kill(ft_atoi(client_pid), SIGUSR1);
		count = 0;
		while (i > 0)
			client_pid[i--] = '\0';
	}
}

int	main(void)
{
	ft_putnbr(getpid());
	ft_putchar(' ');
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
	return (1);
}
