/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:55:00 by tnicolau          #+#    #+#             */
/*   Updated: 2023/11/28 15:25:28 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*new_string(long unsigned int n)
{
	char	*str;
	int		i;

	i = 0;
	while (n > 0)
	{
		n = n / 16;
		i++;
	}
	str = ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	return (str);
}

static int	number_length(long unsigned int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

int	print_pointer(long unsigned int n)
{
	int		i;
	int		result;
	char	*str;

	i = 0;
	if (n == 0)
		return (i += print_str("(nil)"));
	str = new_string(n);
	if (!str)
		return (0);
	i = number_length(n) - 1;
	result = number_length(n);
	while (n > 0)
	{
		if ((n % 16) < 10)
			str[i] = (n % 16) + 48;
		else
			str[i] = (n % 16) + 87;
		n = n / 16;
		i--;
	}
	print_str("0x");
	print_str(str);
	free(str);
	return (result + 2);
}
