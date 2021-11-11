/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 22:51:34 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/08 22:51:34 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_bit_char		g_chars;

void	ft_putnbr(int nbr)
{
	char	c;

	if (nbr > 9)
		ft_putnbr(nbr / 10);
	c = (nbr % 10) + 48;
	write(1, &c, 1);
}

// Set the 1 to the desired bit, then invert to clear that specific bit
void	parse_received_bits(int signal)
{
	if (signal == SIGUSR1)
	{
		g_chars.c &= (~((unsigned char) 0b10000000 >> g_chars.index));
		g_chars.index += 1;
	}
	else if (signal == SIGUSR2)
	{
		g_chars.c |= ((unsigned char) 0b10000000 >> g_chars.index);
		g_chars.index += 1;
	}
	if (g_chars.index == 8)
	{
		write(1, &(g_chars.c), 1);
		g_chars.c = (unsigned char) 0b00000000;
		g_chars.index = 0;
	}
}

int	main(int argc, char *argv[])
{
	int		pid;

	(void) argc;
	(void) argv;
	pid = getpid();
	g_chars.c = 0;
	g_chars.index = 0;
	signal(SIGUSR1, parse_received_bits);
	signal(SIGUSR2, parse_received_bits);
	write(1, "\U0001F496\U0001F496\U0001F496\U0001F496\U0001F496\n", 22);
	write(1, "PID: ", 6);
	ft_putnbr(pid);
	write(1, "\n\U0001F496\U0001F496\U0001F496\U0001F496\U0001F496\n", 23);
	while ("Server is alive")
		usleep(100);
}
