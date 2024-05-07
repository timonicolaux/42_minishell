/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_handling_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:38:18 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/16 13:26:02 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_empty_cmd(t_minishell *minishell, char *command)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!ft_strlen(command))
		free_all_struct(minishell, 1, "No command\n");
	while (command[i])
	{
		if (!ft_cchr_str(command[i], SPACES))
			count++;
		i++;
	}
}

void	empty_heredoc(t_minishell *ms, char *str, char **here_doc_array)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '<')
		i++;
	if (!str[i])
	{
		free_double_array_char(here_doc_array);
		free_all_struct(ms, 1, SYNTAX_ERROR);
	}
}

void	check_empty_redir(t_minishell *ms, char *str, char **file_array)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>')
		i++;
	while (str[i] && (str[i] == '<' || str[i] == '>'))
		i++;
	while (ft_cchr_str(str[i], SPACES))
		i++;
	if (!str[i])
	{
		free_double_array_char(file_array);
		free_all_struct(ms, 1, SYNTAX_ERROR);
	}
}
