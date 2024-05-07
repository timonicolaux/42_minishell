/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:56:01 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/10 10:13:26 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	int		start;
	int		end;
	char	*result;

	start = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup_lib(s1));
	end = ft_strlen(s1);
	while (s1[start] && ft_strrchr(set, s1[start]))
		start++;
	while (s1[end - 1] && ft_strrchr(set, s1[end - 1]) && end > start)
		end--;
	result = malloc(sizeof(char) * (end - start + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, &s1[start], end - start + 1);
	return (result);
}
