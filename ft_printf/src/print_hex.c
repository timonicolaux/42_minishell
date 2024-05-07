/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:08:49 by tnicolau          #+#    #+#             */
/*   Updated: 2023/11/28 15:35:38 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*new_string(unsigned int n)
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
		return (0);
	str[i] = '\0';
	return (str);
}

static int	number_length(unsigned int n)
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

int	print_hex(unsigned int n, const char c)
{
	int		i;
	int		result;
	char	*str;

	result = 0;
	if (n == 0)
		return (result += print_char('0'));
	str = new_string(n);
	if (!str)
		return (0);
	i = number_length(n) - 1;
	result = number_length(n);
	while (n > 0)
	{
		if ((n % 16) < 10)
			str[i--] = (n % 16) + 48;
		else if (c == 'x')
			str[i--] = (n % 16) + 87;
		else if (c == 'X')
			str[i--] = (n % 16) + 55;
		n = n / 16;
	}
	print_str(str);
	free(str);
	return (result);
}
