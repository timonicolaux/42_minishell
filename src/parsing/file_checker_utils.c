/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:26:31 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/16 13:33:54 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_file_str_loop(char *token, int *i, t_check_infile_outfile *check)
{
	int	j;

	j = 0;
	if (token[*i] == '<' || token[*i] == '>')
	{
		check_double_rafters_str(token, i, check->file[check->j], &j);
		check->file[check->j][j] = token[*i];
		*i += 1;
		j++;
		while (token[*i])
		{
			if (!create_file_str_copy_loop(token, i, &j, check))
				break ;
		}
		check->file[check->j][j] = '\0';
		return (0);
	}
	*i += 1;
	return (1);
}

int	create_file_str_copy_loop(char *tok, int *i, int *j,
	t_check_infile_outfile *check)
{
	int	quote;

	quote = 0;
	while (ft_cchr_str(tok[*i], SPACES))
		check->file[check->j][(*j)++] = tok[(*i)++];
	if ((tok[*i] != 34 && tok[*i] != 39) && !ft_cchr_str(tok[*i], SPACES))
		check->file[check->j][(*j)++] = tok[(*i)++];
	if (tok[*i] == 34 || tok[*i] == 39)
	{
		quote = tok[*i];
		check->file[check->j][(*j)++] = tok[(*i)++];
		while (tok[*i] && tok[*i] != quote)
			check->file[check->j][(*j)++] = tok[(*i)++];
		check->file[check->j][(*j)++] = tok[(*i)++];
	}
	if (ft_cchr_str(tok[*i], SPACES))
		return (0);
	return (1);
}

int	calc_total_file_size_loop(char *token, int *i)
{
	int	quote;

	quote = 0;
	while (ft_cchr_str(token[*i], SPACES))
		*i += 1;
	if ((token[*i] != 34 && token[*i] != 39)
		&& !ft_cchr_str(token[*i], SPACES))
		*i += 1;
	if (token[*i] == 34 || token[*i] == 39)
	{
		quote = token[*i];
		*i += 1;
		while (token[*i] && token[*i] != quote)
			*i += 1;
		*i += 1;
	}
	if (ft_cchr_str(token[*i], SPACES))
		return (0);
	return (1);
}
