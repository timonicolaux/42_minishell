/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_command_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:43:10 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/10 14:18:04 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_command_array(t_token *token, t_minishell *ms)
{
	t_token	*token_cpy;
	int		i;

	token_cpy = token;
	i = 0;
	clean_command_array_loop(token, ms, &i);
	token = token_cpy;
}

char	*clean_quotes(t_minishell *ms, char *cmd)
{
	t_clean_quotes	q_clean;

	ft_memset(&q_clean, 0, sizeof(t_clean_quotes));
	q_clean.quote_delete_index = -1;
	while (cmd[q_clean.i])
	{
		if (cmd[q_clean.i] && (cmd[q_clean.i] == 34 || cmd[q_clean.i] == 39)
			&& ((q_clean.i + 1) != ft_strlen(cmd))
			&& (cmd[q_clean.i] == cmd[q_clean.i + 1]))
		{
			q_clean.i_cpy = q_clean.i;
			q_clean.i++;
			cmd = delete_quotes(ms, cmd, q_clean.i_cpy, &q_clean.i);
			q_clean.i = q_clean.i_cpy - 1;
		}
		else
		{
			cmd = clean_spaced_quotes(ms, cmd, &q_clean);
			if (!cmd[q_clean.i] || (q_clean.i + 1) == ft_strlen(cmd))
				break ;
		}
		q_clean.i += 1;
	}
	return (cmd);
}

char	*clean_spaced_quotes(t_minishell *ms, char *cmd,
		t_clean_quotes *q_clean)
{
	char	*result;

	result = cmd;
	if (cmd[q_clean->i] == 34 || cmd[q_clean->i] == 39)
	{
		q_clean->i_cpy = q_clean->i;
		q_clean->quote_delete_index = find_delete_quotes(cmd, &q_clean->i);
	}
	if (q_clean->quote_delete_index != -1)
	{
		result = delete_quotes(ms, cmd,
				q_clean->quote_delete_index, &q_clean->i);
		if ((q_clean->i + 1) == ft_strlen(result))
			return (result);
		q_clean->i = q_clean->i_cpy;
		q_clean->quote_delete_index = -1;
	}
	return (result);
}

char	*delete_quotes(t_minishell *ms, char *cmd, int start, int *index)
{
	t_delete_quotes	del;

	ft_memset(&del, 0, sizeof(t_delete_quotes));
	del.length = ft_strlen(cmd) - 2;
	del.end = *index;
	del.result = malloc(sizeof(char) * (del.length + 1));
	if (!del.result)
	{
		free(cmd);
		free_all_struct(ms, 1, MALLOC_ERROR);
	}
	while (cmd[del.i])
		if (delete_quotes_loop(&del, index, start, cmd))
			break ;
	while (del.j < del.length)
	{
		del.result[del.j] = cmd[del.i];
		del.j += 1;
		del.i += 1;
	}
	del.result[del.j] = '\0';
	free(cmd);
	return (del.result);
}

int	delete_quotes_loop(t_delete_quotes *del, int *index, int start, char *cmd)
{
	if (del->i == del->end)
	{
		del->i += 1;
		*index -= 2;
		return (1);
	}
	if (del->i != start && del->i != del->end)
	{
		del->result[del->j] = cmd[del->i];
		del->j += 1;
	}
	del->i += 1;
	if (!cmd[del->i])
		return (1);
	else
		return (0);
}
