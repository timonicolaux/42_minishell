/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:04:59 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/15 14:16:14 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*treat_var_result(t_minishell *ms, t_replace_var *r_var, char *command)
{
	int	quote_num_cpy;

	quote_num_cpy = r_var->quote_num;
	if (r_var->result == NULL)
		command = join_cmd_result(ms, r_var, command, &r_var->i);
	else if (ft_strchr(r_var->result, '$'))
		jump_variable(command, &r_var->i, r_var->quote_num, r_var);
	else
	{
		while (r_var->i > 0 && r_var->quote_num)
		{
			r_var->i -= 1;
			if (command[r_var->i] == 34 || command[r_var->i] == 39)
				r_var->quote_num -= 1;
		}
		r_var->quote_num = quote_num_cpy;
		command = join_cmd_result(ms, r_var, command, &r_var->i);
		r_var->quote_num_cpy = r_var->quote_num;
		r_var->quotes = 0;
		r_var->quote_num = 0;
	}
	free(r_var->result);
	r_var->result = NULL;
	return (command);
}

char	*join_cmd_result(t_minishell *ms, t_replace_var *r_var,
		char *command, int *index)
{
	t_join_cmd_result	join;
	int					env_name_len;
	char				*env_name;

	ft_memset(&join, 0, sizeof(t_join_cmd_result));
	env_name = get_env_name(ms, r_var->result);
	env_name_len = ft_strlen(env_name) + 1;
	if (!env_name)
		env_name_len = 0;
	join.length = calc_cmd_result_length(command, r_var->quote_num, index)
		+ ft_strlen(r_var->result) + ft_strlen(command);
	join.str = ft_calloc(sizeof(char), (join.length + 1));
	if (!join.str)
		free_all_struct(ms, 1, MALLOC_ERROR);
	while ((join.i < *index) && command[join.i])
	{
		join.str[join.i] = command[join.i];
		join.i += 1;
	}
	join.k = join.i + env_name_len;
	join_result_cmd_end(ms, command, &join, r_var);
	free(command);
	free(env_name);
	return (join.str);
}

void	join_result_cmd_end(t_minishell *ms, char *cmd,
	t_join_cmd_result *j, t_replace_var *r_var)
{
	t_join_result_cmd_end	join_end;

	init_join_result_cmd_end(ms, &join_end, r_var);
	if (join_end.quote_cpy)
		join_middle(cmd, &join_end, j);
	if (r_var->result)
		while (r_var->result[j->j])
			j->str[j->i++] = r_var->result[j->j++];
	else
		join_result_null_result(j, r_var, &join_end, cmd);
	if (cmd)
	{
		while (cmd[j->k])
		{
			j->str[j->i] = cmd[j->k];
			j->i += 1;
			j->k += 1;
		}
		j->str[j->i] = '\0';
	}
}

void	init_join_result_cmd_end(t_minishell *ms,
	t_join_result_cmd_end *join_end, t_replace_var *r_var)
{
	ft_memset(join_end, 0, sizeof(t_join_result_cmd_end));
	join_end->quote_cpy = r_var->quote_num;
	join_end->q_cpy = join_end->quote_cpy;
	join_end->quotes = r_var->quotes;
	join_end->env_name = get_env_name(ms, r_var->result);
	join_end->env_name_len = ft_strlen(join_end->env_name);
	free(join_end->env_name);
	if (join_end->env_name_len)
		join_end->env_name_len += 1;
}

void	join_middle(char *command, t_join_result_cmd_end *join_end,
	t_join_cmd_result *join)
{
	join_end->i = join->k - join_end->env_name_len;
	while (command[join_end->i] && command[join_end->i] != '$')
	{
		join->str[join->i] = command[join_end->i];
		join_end->i += 1;
		join->i += 1;
	}
	join->str[join->i] = '\0';
	join->k = join_end->i + join_end->env_name_len;
	join_end->quote_cpy = 0;
}
