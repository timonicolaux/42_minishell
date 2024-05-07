/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_includes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:57:19 by tnicolau          #+#    #+#             */
/*   Updated: 2024/01/26 10:17:40 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_includes(char *str, char c, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
