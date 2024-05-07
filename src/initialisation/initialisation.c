/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:03:34 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/11 11:10:10 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shlvl(t_minishell *minishell)
{
	t_env	*lst_copy;
	char	*value;
	int		value_int;

	lst_copy = minishell->env;
	while (minishell->env)
	{
		if (!ft_strncmp(minishell->env->name, "SHLVL", 6))
		{
			value = minishell->env->value;
			value_int = ft_atoi(minishell->env->value);
			minishell->env->value = ft_itoa(value_int + 1);
			value_int += 1;
			free(value);
		}
		minishell->env = minishell->env->next;
	}
	minishell->env = lst_copy;
}

void	init_env(char **env, t_minishell *minishell)
{
	t_env	*new_lst;
	char	**env_split;

	new_lst = NULL;
	env_split = NULL;
	if (env && env[0] != NULL)
		init_env_loop(env, env_split, new_lst, minishell);
	else
		init_null_env(minishell);
	new_lst = new_env_list(minishell, "?", "0");
	lstadd_back_env(&minishell->env, new_lst);
	update_shlvl(minishell);
}

static void	free_split(char **env_split)
{
	free(env_split[0]);
	free(env_split[1]);
	free(env_split);
}

void	init_env_loop(char **env, char **env_split, t_env *new_lst,
	t_minishell *ms)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			env_split = split_env(env[i], ms);
			if (!env_split[0])
			{
				free_split(env_split);
				break ;
			}
			new_lst = new_env_list(ms, env_split[0], env_split[1]);
			if (!new_lst)
			{
				free_all_struct(ms, 1, MALLOC_ERROR);
				free_split(env_split);
				break ;
			}
			lstadd_back_env(&ms->env, new_lst);
			free_split(env_split);
		}
		i++;
	}
}

char	**split_env(char *env, t_minishell *minishell)
{
	int		i;
	int		length;
	char	**result;

	i = 0;
	length = ft_strlen(env);
	result = malloc(sizeof(char *) * 3);
	if (!result)
		free_all_struct(minishell, 1, MALLOC_ERROR);
	while (env[i])
	{
		if (env[i] == '=')
		{
			result[0] = ft_substr(env, (unsigned int)0, (size_t)(i));
			i++;
			result[1] = ft_substr(env, (unsigned int)i, (size_t)(length - i));
			result[2] = NULL;
			return (result);
		}
		i++;
	}
	free(result);
	return (NULL);
}
