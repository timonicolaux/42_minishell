/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_vars_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:47:02 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/12 14:10:24 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_special_vars(t_minishell *minishell, char *env, t_token *token)
{
	char	*result;
	int		j;
	int		k;

	j = 0;
	k = 0;
	result = NULL;
	result = malloc(sizeof(char) * (ft_strlen(env) + 1));
	if (!result)
		free_all_struct(minishell, 1, MALLOC_ERROR);
	while (env[k])
		result[j++] = env[k++];
	result[j] = '\0';
	token->special_vars[minishell->sv_i] = result;
	minishell->sv_i += 1;
}

int	find_special_var_index(char *cmd, char *var)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while ((cmd[i] == var[j]) && cmd[i])
		{
			i++;
			j++;
		}
		if (j == ft_strlen(var))
			return (i - j - 1);
		i++;
	}
	return (-1);
}

char	*find_special_var_value(char *var, t_minishell *ms)
{
	t_env	*env_cpy;
	char	*result;

	env_cpy = ms->env;
	result = NULL;
	while (ms->env)
	{
		if (!ft_strncmp(var, ms->env->name, ft_strlen(var) + 1))
		{
			result = ft_strdup_minishell(ms, ms->env->value);
			break ;
		}
		ms->env = ms->env->next;
	}
	ms->env = env_cpy;
	return (result);
}
