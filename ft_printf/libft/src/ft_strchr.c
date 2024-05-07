/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:11:11 by tnicolau          #+#    #+#             */
/*   Updated: 2024/02/21 10:13:07 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	*str;
	char	car;

	i = 0;
	car = (char)c;
	str = (char *)s;
	while (str[i] && str[i] != car)
		i++;
	if (str[i] == car)
		return (&str[i]);
	else
		return (0);
}
