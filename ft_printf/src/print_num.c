/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:46:45 by tnicolau          #+#    #+#             */
/*   Updated: 2023/11/24 12:34:32 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr(int n)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", 1);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', 1);
			n *= -1;
		}
		if (n >= 10)
		{
			ft_putnbr_fd(n / 10, 1);
			ft_putnbr_fd(n % 10, 1);
		}
		else
			ft_putchar_fd(n + '0', 1);
	}
}

static int	number_length(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	print_num(int n)
{
	int	num_length;

	num_length = number_length(n);
	ft_putnbr(n);
	return (num_length);
}
