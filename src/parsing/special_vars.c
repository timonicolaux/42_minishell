/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:59:01 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/12 14:19:57 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_special_vars(t_minishell *ms)
{
	t_token	*token_cpy;

	token_cpy = ms->token;
	while (ms->token)
	{
		if (ms->token->special_vars && ms->token->special_vars[0] != NULL)
			find_special_vars(ms->token, ms);
		ms->token = ms->token->next;
	}
	ms->token = token_cpy;
}

void	find_special_vars(t_token *token, t_minishell *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token->cmd_array[i] != NULL)
	{
		while (token->cmd_array[i][j])
		{
			if (token->cmd_array[i][j] == '$')
			{
				j++;
				locate_special_vars(&i, &j, token, ms);
				if (!token->cmd_array[i][j])
					break ;
			}
			else
				j++;
		}
		j = 0;
		i++;
	}
}

void	locate_special_vars(int *i, int *j, t_token *token, t_minishell *ms)
{
	t_locate_special_vars	s;

	ft_memset(&s, 0, sizeof(t_locate_special_vars));
	while (token->special_vars[s.k] != NULL)
	{
		while (token->cmd_array[*i][*j] && token->special_vars[s.k][s.l]
			&& (token->cmd_array[*i][*j] == token->special_vars[s.k][s.l]))
		{
			s.length += 1;
			*j += 1;
			s.l += 1;
		}
		check_similar(i, j, token, &s);
		*j = *j - s.length;
		if (s.length == ft_strlen(token->special_vars[s.k]) && s.length)
		{
			s.value = find_special_var_value(token->special_vars[s.k], ms);
			token->cmd_array[*i] = replace_special_vars(ms,
					token->cmd_array[*i], token->special_vars[s.k], s.value);
			return ;
		}
		s.k += 1;
		s.length = 0;
		s.l = 0;
	}
}

char	*replace_special_vars(t_minishell *ms, char *cmd,
	char *var, char *value)
{
	t_rep_special_var	rsp_var;
	int					var_len;

	var_len = ft_strlen(var);
	ft_memset(&rsp_var, 0, sizeof(t_rep_special_var));
	rsp_var.length = (ft_strlen(cmd) + (ft_strlen(value) - (var_len + 1)));
	rsp_var.var_len = var_len;
	rsp_var.result = malloc(sizeof(char) * (rsp_var.length + 1));
	if (!rsp_var.result)
		free_all_struct(ms, 1, MALLOC_ERROR);
	rsp_var.index = find_special_var_index(cmd, var);
	if (rsp_var.index == -1)
		return (NULL);
	while (rsp_var.length)
	{
		if (rsp_var.j == rsp_var.index)
		{
			rsp_var.result = copy_special_var(value, cmd, &rsp_var);
			free(cmd);
			return (rsp_var.result);
		}
		rsp_var.result[rsp_var.i++] = cmd[rsp_var.j++];
		rsp_var.length--;
	}
	return (NULL);
}

char	*copy_special_var(char *value, char *cmd, t_rep_special_var	*rsp_var)
{
	int	j;

	j = 0;
	while (value[j])
	{
		rsp_var->result[rsp_var->i] = value[j];
		rsp_var->i += 1;
		j++;
	}
	while (cmd[rsp_var->index] && (rsp_var->var_len + 1))
	{
		rsp_var->index += 1;
		rsp_var->var_len -= 1;
	}
	while (cmd[rsp_var->index] && rsp_var->var_len)
	{
		rsp_var->result[rsp_var->i] = cmd[rsp_var->index];
		rsp_var->index += 1;
		rsp_var->i += 1;
	}
	rsp_var->result[rsp_var->i] = '\0';
	return (rsp_var->result);
}
