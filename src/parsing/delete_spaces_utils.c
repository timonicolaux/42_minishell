/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_spaces_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:38:36 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/16 14:07:22 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	spaces_remover_loop(t_spaces_remover *s, char *str)
{
	check_double_rafters_str(str, &s->i, s->result, &s->j);
	s->result[s->j++] = str[s->i++];
	while (str[s->i])
	{
		while (ft_cchr_str(str[s->i], SPACES))
			s->i++;
		if ((str[s->i] != 34 && str[s->i] != 39)
			&& !ft_cchr_str(str[s->i], SPACES))
			s->result[s->j++] = str[s->i++];
		if (str[s->i] == 34 || str[s->i] == 39)
		{
			s->quote = str[s->i];
			s->i++;
			while (str[s->i] && str[s->i] != s->quote)
				s->result[s->j++] = str[s->i++];
			s->i++;
		}
		if (ft_cchr_str(str[s->i], SPACES))
			break ;
	}
	s->result[s->j] = '\0';
	return ;
}

int	final_file_len_loop(char *str, int *size, int quote, int *i)
{
	while (ft_cchr_str(str[*i], SPACES))
		*i += 1;
	if ((str[*i] != 34 && str[*i] != 39) && !ft_cchr_str(str[*i], SPACES))
	{
		*i += 1;
		*size += 1;
	}
	if (str[*i] == 34 || str[*i] == 39)
	{
		quote = str[*i];
		*i += 1;
		while (str[*i] && str[*i] != quote)
		{
			*i += 1;
			*size += 1;
		}
		*i += 1;
	}
	if (ft_cchr_str(str[*i], SPACES))
		return (*size);
	return (-1);
}
