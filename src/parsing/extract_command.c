/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:52:17 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/16 13:10:22 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_command(t_minishell *minishell, t_token *token)
{
	char	*command;
	int		i;

	i = 0;
	command = NULL;
	if (token->files)
	{
		while (token->files[i])
		{
			if (i == 0)
			{
				command = ft_strdup_minishell(minishell, token->token);
				if (command == NULL)
				{
					free(command);
					free_all_struct(minishell, 1, MALLOC_ERROR);
				}
			}
			command = del_str_from_str(minishell, command, token->files[i]);
			i++;
		}
	}
	token->command = command;
}

char	*create_string(char *src, t_del_str_from_str *t_del,
	t_minishell *minishell, int length)
{
	char	*result;
	int		i;
	int		j;
	int		end;

	i = 0;
	j = 0;
	end = t_del->end + t_del->start;
	result = malloc(sizeof(char) * (length + 2));
	if (!result)
		free_str_and_struct(minishell, src);
	while (src[i])
	{
		if (i == t_del->start)
		{
			while (i != end && src[i])
				i++;
		}
		result[j] = src[i];
		j++;
		if (src[i])
			i++;
	}
	result[j] = '\0';
	return (free(src), result);
}

char	*del_str_from_str(t_minishell *minishell, char *src, char *del)
{
	t_del_str_from_str	t_del;

	ft_memset(&t_del, 0, sizeof(t_del_str_from_str));
	if (!src || (!src && !del))
		return (t_del.result);
	if ((ft_strlen(del) > ft_strlen(src)) || !del)
		return (free(src), t_del.result);
	while (src[t_del.start])
	{
		if (src[t_del.start] == '<' || src[t_del.start] == '>')
			while (src[t_del.start + t_del.end] == del[t_del.end]
				&& src[t_del.start + t_del.end] && del[t_del.end])
				t_del.end += 1;
		if (t_del.end == ft_strlen(del))
		{
			t_del.result = create_string
				(src, &t_del, minishell, (ft_strlen(src) - ft_strlen(del)));
			return (t_del.result);
		}
		else
			t_del.end = 0;
		t_del.start += 1;
	}
	free(src);
	return (t_del.result);
}
