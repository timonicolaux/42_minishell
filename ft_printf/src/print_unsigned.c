/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:07:57 by tnicolau          #+#    #+#             */
/*   Updated: 2023/11/24 12:34:30 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putunsnbr(unsigned int n)
{
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, 1);
		ft_putnbr_fd(n % 10, 1);
	}
	else
		ft_putchar_fd(n + '0', 1);
}

static unsigned int	unsigned_number_length(unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		i = 1;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

unsigned int	print_unsigned(unsigned int n)
{
	unsigned int	num_length;

	num_length = unsigned_number_length(n);
	ft_putunsnbr(n);
	return (num_length);
}
