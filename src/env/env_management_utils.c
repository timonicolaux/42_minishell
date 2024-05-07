/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:29:14 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/10 11:33:09 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	concat_str_three(char *s1, char *s2, char *s3, char *new_s)
{
	size_t	index;
	size_t	index_s2;
	size_t	index_s3;

	index = 0;
	index_s2 = 0;
	index_s3 = 0;
	while (s1[index])
	{
		new_s[index] = s1[index];
		index++;
	}
	while (s2[index_s2])
		new_s[index++] = s2[index_s2++];
	while (s3[index_s3])
		new_s[index++] = s3[index_s3++];
	new_s[index] = '\0';
}

char	*ft_strjoin_three(t_minishell *ms, char *s1, char *s2, char *s3)
{
	char	*new_s;

	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (ft_strdup_minishell(ms, 0));
	new_s = malloc((ft_strlen(s1)
				+ ft_strlen(s2) + ft_strlen(s3) + 1) * sizeof(char));
	if (!new_s)
		free_all_struct(ms, 1, MALLOC_ERROR);
	concat_str_three(s1, s2, s3, new_s);
	return (new_s);
}
