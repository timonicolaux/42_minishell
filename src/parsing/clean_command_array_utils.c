/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_command_array_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:29:51 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/16 14:06:48 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_command_array_loop(t_token *token, t_minishell *ms, int *i)
{
	while (token)
	{
		if (token->cmd_array != NULL)
		{
			create_special_vars_array(ms, token);
			while (token->cmd_array[*i] != NULL)
			{
				clean_cmd_array_functions(token, ms, i);
				*i += 1;
			}
			*i = 0;
		}
		token = token->next;
	}
}

void	clean_cmd_array_functions(t_token *token, t_minishell *ms, int *i)
{
	if (ft_strchr(token->cmd_array[*i], '$'))
		token->cmd_array[*i] = replace_variable(token->cmd_array[*i],
				ms, token);
	token->cmd_array[*i] = check_tilde(ms, token->cmd_array[*i]);
	if (token->cmd_array[*i] && (ft_strchr(token->cmd_array[*i], 34)
			|| ft_strchr(token->cmd_array[*i], 39)))
		token->cmd_array[*i] = clean_quotes(ms, token->cmd_array[*i]);
}

int	find_delete_quotes(char *command, int *i)
{
	int	current_input;
	int	start;

	current_input = command[*i];
	start = *i;
	if (!command[*i])
		return (-1);
	*i += 1;
	while (command[*i] && (command[*i] != current_input))
		*i += 1;
	if (command[*i] == current_input)
		return (start);
	return (-1);
}

void	create_special_vars_array(t_minishell *minishell, t_token *token)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (token->token[i])
	{
		if (token->token[i] == '$')
			length++;
		i++;
	}
	if (length != 0)
	{
		token->special_vars = malloc(sizeof(char *) * (length + 1));
		if (!token->special_vars)
			free_all_struct(minishell, 1, MALLOC_ERROR);
		i = 0;
		while (length >= 0)
		{
			token->special_vars[i] = NULL;
			i++;
			length--;
		}
	}
}
