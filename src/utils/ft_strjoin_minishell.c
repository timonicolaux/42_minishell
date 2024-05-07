/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_minishell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:32:03 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/09 14:32:28 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_strjoin_shell(t_minishell *minishell, char *s1, char *s2)
{
	char	*new_s;

	if (s1 == NULL && s2 == NULL)
		return (ft_strdup_minishell(minishell, 0));
	if (s1 == NULL)
		return (ft_strdup_minishell(minishell, s2));
	if (s2 == NULL)
		return (ft_strdup_minishell(minishell, s1));
	new_s = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new_s)
		free_all_struct(minishell, 1, MALLOC_ERROR);
	return (concat_str(s1, s2, new_s));
}
