/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:01:06 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/15 15:06:09 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_for_heredoc(t_minishell *minishell)
{
	t_token	*token_cpy;

	token_cpy = minishell->token;
	while (minishell->token)
	{
		minishell->token->heredoc = NULL;
		if (minishell->token->files)
			find_heredoc(minishell, minishell->token);
		minishell->token = minishell->token->next;
	}
	minishell->token = token_cpy;
}

void	find_heredoc(t_minishell *minishell, t_token *token)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	if (token->files)
	{
		while (token->files[i])
		{
			if (ft_strchr_str(token->files[i], "<<"))
				length++;
			i++;
		}
		create_heredoc_array(minishell, token, length);
		update_files_array(minishell, token, length - 1);
	}
}

void	create_heredoc_array(t_minishell *minishell, t_token *token, int length)
{
	int		i;
	int		j;
	char	**heredoc_str;

	i = 0;
	j = 0;
	heredoc_str = ft_calloc(sizeof(char *), (length + 1));
	if (!heredoc_str)
		free_all_struct(minishell, 1, MALLOC_ERROR);
	while (token->files[i] && length)
	{
		if (ft_strchr_str(token->files[i], "<<"))
		{
			empty_heredoc(minishell, token->files[i], heredoc_str);
			heredoc_str[j] = ft_strdup_minishell(minishell, token->files[i]);
			j++;
			length--;
		}
		i++;
	}
	heredoc_str[j] = NULL;
	token->heredoc = heredoc_str;
}

void	update_files_array(t_minishell *minishell, t_token *token, int length)
{
	int		i;
	int		j;
	int		len;
	char	**files_str;

	i = -1;
	j = 0;
	len = ft_strlen_dbl_array(token->files) - length;
	files_str = malloc(sizeof(char *) * (len + 1));
	if (!files_str)
		free_all_struct(minishell, 1, MALLOC_ERROR);
	while (token->files[++i])
	{
		if (ft_strchr_str(token->files[i], "<<") && length)
			length--;
		else
		{
			files_str[j] = ft_strdup_minishell(minishell, token->files[i]);
			free(token->files[i]);
			j++;
		}
	}
	files_str[j] = NULL;
	free(token->files);
	token->files = files_str;
}

int	ft_strlen_dbl_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
