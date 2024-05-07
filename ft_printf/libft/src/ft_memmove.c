/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:18:08 by tnicolau          #+#    #+#             */
/*   Updated: 2024/02/21 10:13:11 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t n)
{
	unsigned char	*csrc;
	unsigned char	*cdest;

	if (src == dest || n == 0)
		return (dest);
	if (dest < src)
	{
		csrc = (unsigned char *)src;
		cdest = (unsigned char *)dest;
		while (n--)
			*cdest++ = *csrc++;
	}
	else
	{
		csrc = (unsigned char *)src + (n - 1);
		cdest = (unsigned char *)dest + (n - 1);
		while (n--)
			*cdest-- = *csrc--;
	}
	return (dest);
}
