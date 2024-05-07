/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:38:48 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/15 13:55:06 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_var_quote_manager(char *command, t_minishell *ms,
	t_token *token, t_replace_var *r_var)
{
	r_var->result = replace_var_quotes(command, r_var, ms,
			token);
	command = treat_var_result(ms, r_var, command);
	return (command);
}

char	*replace_var_classic_manager(char *command, t_minishell *ms,
	t_token *token, t_replace_var *r_var)
{
	r_var->result = replace_var_classic(command, r_var->i, ms,
			token);
	command = treat_var_result(ms, r_var, command);
	return (command);
}

char	*replace_variable(char *cmd, t_minishell *ms, t_token *token)
{
	t_replace_var	r_var;

	ft_memset(&r_var, 0, sizeof(t_replace_var));
	r_var.cmd_cpy = ft_strdup_minishell(ms, cmd);
	r_var.result = NULL;
	while (cmd[r_var.i])
	{
		r_var.result = NULL;
		free(r_var.cmd_cpy);
		r_var.cmd_cpy = ft_strdup_minishell(ms, cmd);
		if (cmd && (cmd[r_var.i] == 34 || cmd[r_var.i] == 39))
			move_to_dollar(&r_var.quote_num, &r_var.quotes, &r_var.i, cmd);
		if (cmd && cmd[r_var.i] && cmd[r_var.i] == '$' && r_var.quotes)
			cmd = replace_var_quote_manager(cmd, ms, token, &r_var);
		else if (cmd && cmd[r_var.i] && cmd[r_var.i] == '$' && !r_var.quotes)
			cmd = replace_var_classic_manager(cmd, ms, token, &r_var);
		if (cmd && cmd[r_var.i] && !ft_strncmp(r_var.cmd_cpy, cmd,
				(ft_strlen(cmd) + 1)))
			r_var.i += 1;
	}
	free(r_var.cmd_cpy);
	return (cmd);
}

char	*replace_var_quotes(char *command, t_replace_var *r_var,
		t_minishell *ms, t_token *token)
{
	char	*result;

	r_var->i_cpy = r_var->i;
	result = NULL;
	while (r_var->i_cpy >= 0)
	{
		r_var->i_cpy -= 1;
		while (command[r_var->i_cpy] != r_var->quotes && command[r_var->i_cpy])
			r_var->i_cpy -= 1;
		if (command[r_var->i_cpy] == 34)
		{
			result = rep_var_double_quote(command, r_var, ms, token);
			return (result);
		}
		if (command[r_var->i_cpy] == 39)
		{
			result = rep_var_single_quote(command, r_var, ms, token);
			return (result);
		}
		else
			result = replace_var_classic(command, r_var->i_cpy, ms, token);
	}
	return (ft_strdup_minishell(ms, command));
}

char	*replace_var_classic(char *command, int i, t_minishell *ms,
		t_token *token)
{
	t_rep_var_classic	r_var;

	ft_memset(&r_var, 0, sizeof(t_rep_var_classic));
	r_var.i_cpy = i;
	if (find_questionmark(command))
		return (r_var.var = get_env_value(ms, "?"));
	r_var.length = var_length(command, r_var.i_cpy);
	if (!r_var.length)
		return (NULL);
	r_var.var = malloc(sizeof(char) * (r_var.length + 1));
	if (!r_var.var)
		free_all_struct(ms, 1, MALLOC_ERROR);
	i++;
	while (r_var.length > 0)
	{
		r_var.var[r_var.j] = command[i];
		i++;
		r_var.j += 1;
		r_var.length -= 1;
	}
	r_var.var[r_var.j] = '\0';
	r_var.var = find_var_value(r_var.var, ms, token);
	return (r_var.var);
}
