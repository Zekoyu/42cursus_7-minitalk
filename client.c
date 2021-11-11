/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 22:52:23 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/11 15:12:51 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_atoi(char *str)
{
	int		res;
	int		i;
	long	j;

	res = 0;
	i = 0;
	j = 1;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	while (--i >= 0)
	{
		res += ((str[i] - 48) * j);
		j *= 10;
	}
	return (res);
}

void	send_char(char c, int pid)
{
	unsigned char	i;

	i = 0b10000000;
	while (i != 0b00000000)
	{
		if ((i & c) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i = i >> 1;
		usleep(500);
	}
}

int	main(int argc, char *argv[])
{
	int		pid;
	char	*str;

	if (argc != 3)
		return (EXIT_FAILURE);
	pid = ft_atoi(argv[1]);
	if (pid == -1)
		return (EXIT_FAILURE);
	str = argv[2];
	while (*str)
		send_char(*str++, pid);
}
