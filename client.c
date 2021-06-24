/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:51:16 by agirona           #+#    #+#             */
/*   Updated: 2021/06/24 20:32:40 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <stdlib.h>

int		main(int argc, char **argv)
{
	char	*str;
	int		i;
	int		d;

	if (argc == 3)
	{
		i = 0;
		d = 0;
		str = argv[2];
		while (str[d])
		{
			i = 0;
			while (i < 8)
			{
				if ((str[d] >> (7 - i)) & 1)
					kill(atoi(argv[1]), SIGUSR1);
				else
					kill(atoi(argv[1]), SIGUSR2);
				usleep(250);
				i++;
			}
			d++;
		}
	}
	else
		ft_putstr("Usage : client <pid> <message>");
}
