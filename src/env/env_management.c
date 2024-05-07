/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:45:56 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/10 11:32:31 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	put_env_in_array(t_minishell *d)
{
	int		size_array;
	int		i;
	t_env	*env_lst_copy;

	env_lst_copy = d->env;
	if (d->env_array != NULL)
		free_double_array_char(d->env_array);
	i = 0;
	size_array = lst_length_env(&d->env) + 1;
	d->env_array = malloc(size_array * sizeof(char *));
	if (!d->env_array)
		free_all_struct(d, 1, MALLOC_ERROR);
	while (d->env)
	{
		if (d->env->value)
			d->env_array[i] = ft_strjoin_three(d, d->env->name, "=",
					d->env->value);
		else
			d->env_array[i] = ft_strdup_minishell(d, d->env->name);
		i++;
		d->env = d->env->next;
	}
	d->env = env_lst_copy;
	d->env_array[i] = NULL;
}

void	update_error_code(int code, t_minishell *data)
{
	t_env	*env_copy;

	env_copy = data->env;
	while (data->env)
	{
		if (data->env->name[0] == '?')
		{
			free(data->env->value);
			data->env->value = ft_itoa(code);
		}
		data->env = data->env->next;
	}
	data->env = env_copy;
}

char	*get_env_value(t_minishell *minishell, char *find)
{
	t_env	*env_cpy;
	char	*result;

	env_cpy = minishell->env;
	if (!find)
	{
		minishell->env = env_cpy;
		return (NULL);
	}
	while (minishell->env)
	{
		if (!ft_strncmp(minishell->env->name, find, (ft_strlen(find) + 1)))
		{
			result = ft_strdup_minishell(minishell, minishell->env->value);
			minishell->env = env_cpy;
			return (result);
		}
		minishell->env = minishell->env->next;
	}
	minishell->env = env_cpy;
	return (NULL);
}

char	*get_env_name(t_minishell *minishell, char *find)
{
	t_env	*env_cpy;
	char	*result;

	env_cpy = minishell->env;
	if (!find)
	{
		minishell->env = env_cpy;
		return (NULL);
	}
	while (minishell->env)
	{
		if (!ft_strncmp(minishell->env->value, find, 1000))
		{
			result = ft_strdup_minishell(minishell, minishell->env->name);
			minishell->env = env_cpy;
			return (result);
		}
		minishell->env = minishell->env->next;
	}
	minishell->env = env_cpy;
	return (NULL);
}
