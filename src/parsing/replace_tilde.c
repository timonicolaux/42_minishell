/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_tilde.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:51:41 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/09 14:31:52 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_tilde(t_minishell *minishell, char *str)
{
	char	*home;
	char	*result;
	int		length;

	if (find_else_tilde(str) == 1)
	{
		home = get_env_value(minishell, "HOME");
		length = ft_strlen(home) + ft_strlen(str) - 1;
		result = malloc(sizeof(char) * (length + 1));
		if (!result)
			free_all_struct(minishell, 1, MALLOC_ERROR);
		replace_tilde_str(home, result, str);
		return (free(str), result);
	}
	else if (find_else_tilde(str) == 2)
	{
		home = get_env_value(minishell, "HOME");
		length = ft_strlen(home) + ft_strlen(str) - 1;
		result = malloc(sizeof(char) * (length + 1));
		if (!result)
			free_all_struct(minishell, 1, MALLOC_ERROR);
		replace_tilde_only(home, result, str);
		return (free(str), result);
	}
	return (str);
}

void	replace_tilde_str(char *home, char *result, char *str)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] && str[i] != '~')
	{
		result[j] = str[i];
		i++;
	}
	if (str[i] == '~')
	{
		while (home[k])
		{
			result[j] = home[k];
			k++;
			j++;
		}
		i++;
	}
	while (str[i])
		result[j++] = str[i++];
	result[j] = '\0';
}

void	replace_tilde_only(char *home, char *result, char *str)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] != '~' && str[i])
	{
		result[j] = str[i];
		i++;
	}
	if (str[i] == '~')
	{
		while (home[k])
		{
			result[j] = home[k];
			k++;
			j++;
		}
		i++;
	}
	result[j] = '\0';
}
