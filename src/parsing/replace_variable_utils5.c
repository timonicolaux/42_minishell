/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable_utils5.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:57:44 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/15 11:33:56 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rep_var_double_quote(char *command, t_replace_var *r_var,
		t_minishell *ms, t_token *token)
{
	t_rep_var_quotes	dq;

	ft_memset(&dq, 0, sizeof(t_rep_var_quotes));
	dq.index = r_var->i_cpy;
	if (r_var->quote_num > 1)
	{
		if (r_var->i_cpy != 0)
			r_var->i_cpy -= 1;
		while (ft_cchr_str(command[r_var->i_cpy], SPACES) && r_var->i_cpy)
			r_var->i_cpy -= 1;
		if (r_var->i_cpy >= 0 && command[r_var->i_cpy] == 39)
		{
			dq.i_cpy = r_var->i_cpy;
			dq.result = send_back_value(ms, command, &dq, r_var);
			return (dq.result);
		}
	}
	dq.result = create_var_quote(command, &r_var->i_cpy, ms, token);
	return (dq.result);
}

char	*rep_var_single_quote(char *command, t_replace_var *r_var,
		t_minishell *ms, t_token *token)
{
	t_rep_var_quotes	sq;

	ft_memset(&sq, 0, sizeof(t_rep_var_quotes));
	sq.index = r_var->i_cpy;
	if (r_var->quote_num > 1)
	{
		if (r_var->i_cpy != 0)
			r_var->i_cpy -= 1;
		while (ft_cchr_str(command[r_var->i_cpy], SPACES) && r_var->i_cpy)
			r_var->i_cpy -= 1;
		if (r_var->i_cpy >= 0 && command[r_var->i_cpy] == 34)
		{
			sq.result = create_var_quote(command, &r_var->i_cpy, ms, token);
			return (sq.result);
		}
	}
	sq.i_cpy = r_var->i_cpy;
	sq.result = send_back_value(ms, command, &sq, r_var);
	return (sq.result);
}

char	*send_back_value(t_minishell *ms, char *command,
		t_rep_var_quotes *q, t_replace_var *r_var)
{
	t_send_back_value	val;
	int					i;

	ft_memset(&val, 0, sizeof(t_send_back_value));
	val.index = q->index;
	i = q->i_cpy;
	val.i_cpy = i;
	while (command[val.i_cpy])
	{
		if (val.i_cpy == q->index)
			val.result = send_back_value_loop(ms, &val, command, r_var);
		if (!command[val.i_cpy])
			break ;
		val.i_cpy += 1;
	}
	return (val.result);
}

char	*send_back_value_loop(t_minishell *ms, t_send_back_value *val,
	char *command, t_replace_var *r_var)
{
	char	*result;

	result = NULL;
	val->i_cpy += 1;
	move_to_value(val, command, r_var);
	result = malloc(sizeof(char) * (val->length + 1));
	if (!result)
		free_all_struct(ms, 1, MALLOC_ERROR);
	while (command[val->index] && !ft_cchr_str(command[val->index], SPACES)
		&& (val->j < val->length))
	{
		result[val->j] = command[val->index];
		val->j += 1;
		val->index += 1;
	}
	result[val->j] = '\0';
	return (result);
}

int	find_questionmark(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '$' && command[i + 1] == '?')
			return (1);
		i++;
	}
	return (0);
}
