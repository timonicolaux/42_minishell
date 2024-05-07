/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:07:40 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/11 15:39:25 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_node(t_env *env, t_env *node_to_delete)
{
	t_env	*env_temp;

	env_temp = node_to_delete->next;
	free(node_to_delete->name);
	if (node_to_delete->value)
		free(node_to_delete->value);
	free(node_to_delete);
	env->next = env_temp;
}

void	find_and_delete_var(t_env *env, char *name)
{
	t_env	*env_copy;
	int		length_to_comp;

	env_copy = env;
	if (ft_strchr(name, '='))
		length_to_comp = ft_strlen(env->name) - 1;
	else
		length_to_comp = ft_strlen(env->name);
	if (!ft_strncmp(name, env->name, length_to_comp))
		delete_node(env, env);
	env_copy = env;
	while (env->next)
	{
		if (!ft_strncmp(name, env->next->name, length_to_comp))
			delete_node(env, env->next);
		env = env->next;
		if (!env)
			break ;
	}
	env = env_copy;
}

int	ft_unset(t_minishell *minishell, char **cmd)
{
	t_env	*lst_env;
	char	**args;
	int		i;
	int		error_marker;

	args = cmd + 1;
	error_marker = 0;
	i = 0;
	lst_env = minishell->env;
	while (args[i])
	{
		if (!args[i][0])
			i++;
		else
		{
			if (uns_exp_error(2, args[i]) == -1)
				error_marker = -1;
			else
				find_and_delete_var(lst_env, args[i]);
			i++;
		}
	}
	if (error_marker == -1)
		return (1);
	return (0);
}
