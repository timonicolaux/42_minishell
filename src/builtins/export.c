/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:33:26 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/11 11:09:59 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_var_exist(char **split_var, t_minishell *data, char *name_var)
{
	t_env	*env;
	char	*name;

	if (name_var)
		name = name_var;
	else
		name = split_var[0];
	env = data->env;
	while (env)
	{
		if (!ft_strncmp(name, env->name, ft_strlen(name) + 1))
		{
			if (!name_var)
			{
				if (env->value)
					free(env->value);
				env->value = ft_strdup_minishell(data, split_var[1]);
			}
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	add_var_no_equal(int i, t_env *nw_node, char **arg, t_minishell *data)
{
	nw_node = new_env_list(data, arg[i], NULL);
	if (!nw_node)
		return (-1);
	lstadd_back_env(&(data->env), nw_node);
	return (0);
}

int	check_add_var(char *arg, t_env *nw_node, t_minishell *data)
{
	char	**split_var;

	split_var = NULL;
	split_var = split_env(arg, data);
	if (check_var_exist(split_var, data, NULL) == 0)
	{
		nw_node = new_env_list(data, split_var[0], split_var[1]);
		if (!nw_node)
			return (free(split_var), -1);
		lstadd_back_env(&data->env, nw_node);
	}
	free(split_var[0]);
	free(split_var[1]);
	free(split_var);
	return (0);
}

int	export_loop(char **args, t_env *nw_node, t_minishell *data)
{
	int	i;
	int	error_marker;

	error_marker = 0;
	i = -1;
	while (args[++i])
	{
		if (uns_exp_error(1, args[i]) == -1)
			error_marker = -1;
		else
		{
			if (ft_strchr(args[i], '='))
			{
				if (check_add_var(args[i], nw_node, data) == -1)
					return (-1);
			}
			else if (check_var_exist(NULL, data, args[i]) == 0)
			{
				if (add_var_no_equal(i, nw_node, args, data) == -1)
					return (-1);
			}
		}
	}
	return (error_marker);
}

int	ft_export(t_minishell *minishell, char **cmd, int *fds)
{
	t_env	*new_node;

	new_node = NULL;
	if (cmd[1])
	{
		if (export_loop(cmd + 1, new_node, minishell) == -1)
			return (1);
	}
	else
		export_print_env(minishell->env_array, fds, minishell);
	return (0);
}
