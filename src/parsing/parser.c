/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:01:45 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/16 14:06:38 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(char *input, t_minishell *minishell)
{
	tokenize_input(minishell, input);
	check_for_files(minishell, minishell->token);
	check_files_spaces(minishell, minishell->token);
	check_valid_pipes(minishell, minishell->token);
	create_command_array(minishell, minishell->token);
	clean_command_array(minishell->token, minishell);
	check_for_heredoc(minishell);
	check_special_vars(minishell);
}

void	check_for_files(t_minishell *minishell, t_token *token)
{
	t_token	*token_cpy;
	int		lst_len;

	token_cpy = token;
	lst_len = lst_length(&token);
	if (token)
	{
		while (lst_len)
		{
			token->files = check_infile_outfile(minishell, token);
			if (token->files && token->files[0])
				extract_command(minishell, token);
			else
			{
				token->command = ft_strdup_minishell(minishell, token->token);
				if (token->command == NULL)
					free_all_struct(minishell, 1, MALLOC_ERROR);
			}
			token = token->next;
			lst_len--;
		}
	}
	token = token_cpy;
}

void	check_files_spaces(t_minishell *minishell, t_token *token)
{
	t_token	*token_cpy;
	int		i;
	int		lst_len;

	token_cpy = token;
	i = 0;
	lst_len = lst_length(&token);
	while (lst_len)
	{
		if (token->files)
		{
			while (token->files[i] != NULL)
			{
				token->files[i] = delete_spaces(minishell, token->files[i]);
				i++;
			}
		}
		token = token->next;
		lst_len--;
		i = 0;
	}
	token = token_cpy;
}
