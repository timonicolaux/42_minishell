/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:09:50 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/16 14:07:56 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_spaces(t_minishell *minishell, char *file)
{
	char	*result;

	result = spaces_remover(minishell, file);
	return (result);
}

char	*spaces_remover(t_minishell *minishell, char *str)
{
	t_spaces_remover	s;

	ft_memset(&s, 0, sizeof(t_spaces_remover));
	s.len = final_file_len(str);
	if (s.len == ft_strlen(str))
		return (str);
	s.result = malloc(sizeof(char) * (s.len + 1));
	if (!s.result)
		free_str_and_struct(minishell, str);
	while (str[s.i])
	{
		if (str[s.i] == '<' || str[s.i] == '>')
			spaces_remover_loop(&s, str);
		if (!str[s.i])
			break ;
		s.i += 1;
	}
	free(str);
	s.result[s.j] = '\0';
	return (s.result);
}

int	final_file_len(char *str)
{
	int	i;
	int	quote;
	int	size;

	i = 0;
	quote = 0;
	size = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			size = check_double_rafters(str, &i);
			i++;
			while (str[i])
				if (final_file_len_loop(str, &size, quote, &i) != -1)
					return (size);
			break ;
		}
	}
	return (size);
}

void	free_str_and_struct(t_minishell *minishell, char *str)
{
	free(str);
	free_all_struct(minishell, 1, MALLOC_ERROR);
}
