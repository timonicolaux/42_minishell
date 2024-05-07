/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:01:03 by tnicolau          #+#    #+#             */
/*   Updated: 2024/02/26 13:16:16 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_str(char *str, char *cmp)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (!cmp[y] || !str[i])
		return (0);
	if (ft_strlen(cmp) > ft_strlen(str))
		return (0);
	while (str[i])
	{
		while (str[i + y] == cmp[y] && str[i + y] && cmp[y])
			y++;
		if (y == (ft_strlen(cmp)))
			return (1);
		else
			y = 0;
		i++;
	}
	return (0);
}
