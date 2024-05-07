/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:49:24 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/16 11:12:55 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_var_quote(char *command, int *i, t_minishell *ms,
		t_token *token)
{
	t_create_var_quote	c_var;

	ft_memset(&c_var, 0, sizeof(t_create_var_quote));
	c_var.i_cpy = *i;
	c_var.i_cpycpy = c_var.i_cpy;
	c_var.dollar = -1;
	c_var.dollar_index = -1;
	while (command[c_var.i_cpy] != '$')
	{
		if (command[c_var.i_cpy] == 34 || command[c_var.i_cpy] == 39)
			c_var.quote_num += 1;
		c_var.length += 1;
		c_var.i_cpy += 1;
	}
	c_var.var = replace_var_classic(command, c_var.i_cpy, ms, token);
	return (c_var.var);
}

char	*store_special_var(t_minishell *ms, t_token *token)
{
	char	*result;

	result = NULL;
	store_special_vars(ms, ms->env->name, token);
	result = ft_strjoin_shell(ms, "$", ms->env->name);
	return (result);
}

void	check_similar(int *i, int *j, t_token *token,
		t_locate_special_vars *s)
{
	if (ft_strchr(ALLOWED, token->cmd_array[*i][*j])
		&& token->cmd_array[*i][*j] != '$'
		&& token->cmd_array[*i][*j] != '\0')
	{
		*j = *j - s->length;
		s->length = 0;
	}
}

char	*find_var_value(char *var, t_minishell *ms, t_token *token)
{
	t_env	*env_cpy;
	char	*result;

	env_cpy = ms->env;
	result = NULL;
	while (ms->env)
	{
		if (ft_strcmp(var, ms->env->name))
		{
			if (ft_strchr(ms->env->value, 34) || ft_strchr(ms->env->value, 39))
			{
				result = store_special_var(ms, token);
				break ;
			}
			result = ft_strdup_minishell(ms, ms->env->value);
			break ;
		}
		ms->env = ms->env->next;
	}
	ms->env = env_cpy;
	free(var);
	return (result);
}

void	join_result_null_result(t_join_cmd_result *j, t_replace_var *r_var,
		t_join_result_cmd_end *join_end, char *cmd)
{
	j->k += 1;
	while (ft_cchr_str(cmd[j->k], ALLOWED) && cmd[j->k] != '$' && cmd[j->k])
		j->k += 1;
	if (join_end->q_cpy == 2)
	{
		r_var->i += 1;
		while (cmd[r_var->i] && (cmd[r_var->i] != 34 && cmd[r_var->i] != 39)
			&& cmd[r_var->i] != '$')
		{
			r_var->i += 1;
			if (ft_cchr_str(cmd[r_var->i], ALLOWED) && cmd[r_var->i] != '$')
				join_end->env_name_len += 1;
			if (cmd[r_var->i] == 34 || cmd[r_var->i] == 39)
			{
				r_var->i = r_var->i - join_end->env_name_len - 1;
				break ;
			}
		}
	}
}
