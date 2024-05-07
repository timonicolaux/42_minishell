/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_minishell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:29:04 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/09 14:32:25 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_minishell(t_minishell *minishell, char *s)
{
	char	*str;
	int		i;
	int		size;

	size = ft_strlen(s);
	i = 0;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		free_all_struct(minishell, 1, MALLOC_ERROR);
	while (i < size)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
