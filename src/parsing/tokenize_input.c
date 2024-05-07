/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:27:09 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/09 14:32:21 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_input(t_minishell *minishell, char *input)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			find_delete_quotes(input, &i);
		if (input[i] == '|')
		{
			create_tokens(minishell, start, i, input);
			start = i + 1;
		}
		i++;
	}
	create_tokens(minishell, start, i, input);
}

void	create_tokens(t_minishell *minishell, int start, int end, char *input)
{
	int		i;
	int		length;
	char	*result;

	i = 0;
	length = end - start;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		free_all_struct(minishell, 1, MALLOC_ERROR);
	while (length > 0)
	{
		result[i] = input[start];
		i++;
		start++;
		length--;
	}
	result[i] = '\0';
	add_token_to_list(minishell, result);
}

void	add_token_to_list(t_minishell *minishell, char *result)
{
	t_token	*new_lst;

	new_lst = NULL;
	new_lst = new_token_list(result);
	if (new_lst == NULL)
		free_all_struct(minishell, 1, MALLOC_ERROR);
	lstadd_back_token(&minishell->token, new_lst);
}
