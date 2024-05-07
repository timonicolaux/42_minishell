/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:55:17 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/16 13:09:41 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_command_array(t_minishell *minishell, t_token *token)
{
	t_token	*token_cpy;
	int		lst_len;

	token_cpy = token;
	lst_len = lst_length(&token);
	while (lst_len)
	{
		if (token->command)
			initialize_cmd_array(minishell, token);
		else
			token->cmd_array = NULL;
		token = token->next;
		lst_len--;
	}
	token = token_cpy;
}

void	initialize_cmd_array(t_minishell *minishell, t_token *token)
{
	int	i;
	int	j;
	int	height;

	i = 0;
	j = 0;
	height = calc_cmd_height(token, token->command);
	token->cmd_array = malloc(sizeof(char *) * (height + 1));
	if (!token->cmd_array)
		free_all_struct(minishell, 1, MALLOC_ERROR);
	while (token->command[i])
	{
		while (ft_cchr_str(token->command[i], SPACES) && token->command[i])
			i++;
		if (!token->command[i])
			break ;
		if (token->command[i] != 34 && token->command[i] != 39)
			add_cmd_to_array(minishell, token, &i, &j);
		else if (token->command[i] == 34 || token->command[i] == 39)
			add_quote_cmd_to_array(minishell, token, &i, &j);
	}
	token->cmd_array[j] = NULL;
}

void	add_quote_cmd_to_array(t_minishell *minishell, t_token *token,
	int *i, int *j)
{
	t_add_quote_cmd_to_array	s_cmd;
	int							k;
	int							l;

	ft_memset(&s_cmd, 0, sizeof(t_add_quote_cmd_to_array));
	s_cmd.i_cpy = *i;
	s_cmd.length = -1;
	while (42)
		if (add_quote_cmd_to_array_loop(token, &s_cmd, i))
			break ;
	s_cmd.length = *i - s_cmd.start;
	k = s_cmd.start;
	l = 0;
	token->cmd_array[*j] = malloc(sizeof(char) * (s_cmd.length + 1));
	if (!token->cmd_array[*j])
		free_all_struct(minishell, 1, MALLOC_ERROR);
	while (s_cmd.length > 0)
	{
		token->cmd_array[*j][l++] = token->command[k++];
		s_cmd.length -= 1;
	}
	token->cmd_array[*j][l] = '\0';
	*j += 1;
}

int	add_quote_cmd_to_array_loop(t_token *token,
	t_add_quote_cmd_to_array *s_cmd, int *i)
{
	s_cmd->start = find_delete_quotes(token->command, i);
	if (s_cmd->start == -1)
		s_cmd->start = s_cmd->i_cpy;
	if (s_cmd->length != -1)
		s_cmd->start = s_cmd->length;
	if (token->command[*i] == '\0')
		return (1);
	*i += 1;
	if (token->command[*i] == '\0' || ft_cchr_str(token->command[*i], SPACES))
		return (1);
	*i += 1;
	s_cmd->length = s_cmd->start;
	return (0);
}

void	add_cmd_to_array(t_minishell *minishell, t_token *token, int *i, int *j)
{
	int	length;
	int	length_cpy;
	int	k;
	int	l;

	length = cmd_length(token, token->command, i);
	length_cpy = length;
	k = *i - length;
	l = 0;
	token->cmd_array[*j] = ft_calloc(sizeof(char), (length + 2));
	if (!token->cmd_array[*j])
		free_all_struct(minishell, 1, MALLOC_ERROR);
	while (length_cpy > 0)
	{
		token->cmd_array[*j][l++] = token->command[k++];
		length_cpy--;
	}
	token->cmd_array[*j][length] = '\0';
	*j += 1;
}
