/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:26:10 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/16 15:06:21 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**check_infile_outfile(t_minishell *minishell, t_token *token)
{
	t_check_infile_outfile	check;

	ft_memset(&check, 0, sizeof(t_check_infile_outfile));
	check.height = calc_file_height(token->token);
	if (!check.height)
		return (NULL);
	check.file = ft_calloc(sizeof(char *), (check.height + 1));
	if (!check.file)
		free_all_struct(minishell, 1, MALLOC_ERROR);
	while (token->token[check.i])
		check_infile_outfile_loop(minishell, token, &check);
	check.file[check.j] = NULL;
	if (check.j == 0)
	{
		free(check.file);
		check.file = NULL;
	}
	return (check.file);
}

void	check_infile_outfile_loop(t_minishell *minishell, t_token *token,
		t_check_infile_outfile *check)
{
	int	i_cpy;

	i_cpy = check->i;
	if (token->token[check->i] == 34 || token->token[check->i] == 39)
		check->height = find_delete_quotes(token->token, &check->i);
	if (token->token[check->i] == '<' || token->token[check->i] == '>')
	{
		i_cpy = check->i;
		check_empty_redir(minishell, token->token, check->file);
		check->total_size = calc_total_file_size(token->token, &check->i);
		create_file_str(minishell, token, i_cpy, check);
		check->j += 1;
	}
	else
		check->i += 1;
}

int	calc_file_height(char *token)
{
	int	i;
	int	height;

	i = 0;
	height = 0;
	while (token[i])
	{
		if (token[i] == 34 || token[i] == 39)
			find_delete_quotes(token, &i);
		if (token[i] == '<' || token[i] == '>')
		{
			calc_total_file_size(token, &i);
			height++;
			if (!token[i])
				break ;
		}
		else
			i++;
	}
	return (height);
}

void	create_file_str(t_minishell *ms, t_token *token, int i,
	t_check_infile_outfile *check)
{
	int	i_cpy;

	i_cpy = i;
	check->file[check->j] = malloc(sizeof(char) * (check->total_size + 1));
	if (!check->file[check->j])
		free_all_struct(ms, 1, MALLOC_ERROR);
	while (token->token[i_cpy])
		if (!create_file_str_loop(token->token, &i_cpy, check))
			break ;
}

int	calc_total_file_size(char *token, int *i)
{
	int	size;
	int	i_cpy;

	size = 0;
	i_cpy = 0;
	while (token[*i])
	{
		if (token[*i] == '<' || token[*i] == '>')
		{
			size = check_double_rafters(token, i);
			*i += 1;
			i_cpy = *i;
			while (token[*i])
			{
				if (!calc_total_file_size_loop(token, i))
					break ;
			}
			size = size + (*i - i_cpy);
			break ;
		}
	}
	return (size);
}
