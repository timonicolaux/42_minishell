/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:25:02 by tnicolau          #+#    #+#             */
/*   Updated: 2023/11/24 12:04:30 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_str(char *str)
{
	int	res;

	res = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[res])
	{
		write(1, &str[res], 1);
		res++;
	}
	return (res);
}
