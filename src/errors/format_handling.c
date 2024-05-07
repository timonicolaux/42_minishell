/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:46:13 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/15 14:50:30 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_format_checker(t_minishell *ms, char *input)
{
	int	i;
	int	current_input;
	int	counter;

	i = 0;
	current_input = 0;
	counter = 0;
	while (input[i])
		quote_format_checker_loop(input, &i, current_input, &counter);
	if (counter % 2 != 0 || counter == 1)
		free_all_struct(ms, 1, "Quotes not closed\n");
}

void	quote_format_checker_loop(char *input, int *i, int current_input,
	int *counter)
{
	if (input[*i] != 34 && input[*i] != 39)
		*i += 1;
	else
	{
		if (input[*i] == 34 || input[*i] == 39)
		{
			current_input = input[*i];
			*counter += 1;
			*i += 1;
		}
		while ((input[*i] != current_input) && input[*i])
			*i += 1;
		if (input[*i] == current_input)
			*counter += 1;
		*i += 1;
	}
}

void	rafters_checker(t_minishell *ms, char *input)
{
	int	i;
	int	length;
	int	current_input;

	i = 0;
	current_input = 0;
	length = ft_strlen(input);
	too_many_rafters(ms, input, length);
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			find_delete_quotes(input, &i);
		if ((input[i] == '<' || input[i] == '>') && (i + 1 <= length))
		{
			current_input = input[i];
			if ((input[i + 1] == '>' || input[i + 1] == '<')
				&& input[i + 1] != current_input)
			{
				ft_printf("syntax error near unexpected token `%c'\n",
					input[i + 1]);
				free_all_struct(ms, 1, "");
			}
		}
		i++;
	}
}

void	too_many_rafters(t_minishell *ms, char *input, int length)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			find_delete_quotes(input, &i);
		if (input[i] == '<' && (i + 2 <= length))
		{
			if (input[i + 1] == '<' && input[i + 2] == '<')
				free_all_struct(ms, 1, "Triple > or more\n");
		}
		else if (input[i] == '>' && (i + 2 <= length))
		{
			if (input[i + 1] == '>' && input[i + 2] == '>')
				free_all_struct(ms, 1, "Triple > or more\n");
		}
		i++;
	}
}

void	check_valid_pipes(t_minishell *minishell, t_token *token)
{
	t_token	*token_cpy;
	int		lst_len;

	token_cpy = token;
	lst_len = lst_length(&token);
	while (lst_len)
	{
		if (!token->files)
			check_empty_cmd(minishell, token->command);
		token = token->next;
		lst_len--;
	}
	token = token_cpy;
}
