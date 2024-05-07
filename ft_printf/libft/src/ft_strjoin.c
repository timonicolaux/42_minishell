/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timonicolaux <timonicolaux@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:29:27 by tnicolau          #+#    #+#             */
/*   Updated: 2024/03/25 13:20:56 by timonicolau      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*concat_str(char const *s1, char const *s2, char *new_s)
{
	size_t	index;
	size_t	index_s2;

	index = 0;
	index_s2 = 0;
	while (s1[index])
	{
		new_s[index] = s1[index];
		index++;
	}
	while (s2[index_s2])
	{
		new_s[index] = s2[index_s2];
		index++;
		index_s2++;
	}
	new_s[index] = '\0';
	return (new_s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_s;

	if (s1 == NULL && s2 == NULL)
		return (malloc(0));
	if (s1 == NULL)
		return (ft_strdup_lib(s2));
	if (s2 == NULL)
		return (ft_strdup_lib(s1));
	new_s = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new_s)
		return (0);
	return (concat_str(s1, s2, new_s));
}
