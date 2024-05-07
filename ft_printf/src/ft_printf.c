/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:54:08 by tnicolau          #+#    #+#             */
/*   Updated: 2023/11/30 12:19:28 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_format(const char c, va_list args)
{
	int	result;

	result = 0;
	if (c == 'c')
		result += print_char(va_arg(args, int));
	else if (c == 's')
		result += print_str(va_arg(args, char *));
	else if (c == 'p')
		result += print_pointer(va_arg(args, long unsigned int));
	else if (c == 'd')
		result += print_num(va_arg(args, int));
	else if (c == 'i')
		result += print_num(va_arg(args, int));
	else if (c == 'u')
		result += print_unsigned(va_arg(args, unsigned int));
	else if (c == 'x')
		result += print_hex(va_arg(args, unsigned int), c);
	else if (c == 'X')
		result += print_hex(va_arg(args, unsigned int), c);
	else if (c == '%')
		result += print_char('%');
	return (result);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		result;
	va_list	args;

	i = 0;
	result = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			result += check_format(str[i + 1], args);
			i++;
		}
		else
			result += write(1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (result);
}
