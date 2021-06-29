/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:43:11 by agirona           #+#    #+#             */
/*   Updated: 2021/06/29 18:21:58 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

int	main(void)
{
	ft_putnbr(getpid());
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
	return (1);
}
