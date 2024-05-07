/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:21:24 by tnicolau          #+#    #+#             */
/*   Updated: 2024/03/08 11:34:25 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char *nptr)
{
	int				i;
	int				sign;
	long long int	result;
	long long int	resultcpy;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		sign *= -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		resultcpy = result;
		result = result * 10 + (nptr[i] - '0') * sign;
		if (result > resultcpy && sign == -1)
			return (0);
		if (result < resultcpy && sign == 1)
			return (-1);
		i++;
	}
	return ((int)result);
}
