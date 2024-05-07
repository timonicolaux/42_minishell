/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable_utils3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:29:12 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/12 14:46:13 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_to_dollar(int *quote_num, int *quotes, int *i, char *command)
{
	*quotes = command[*i];
	*quote_num += 1;
	*i += 1;
	while (command[*i])
	{
		if (command[*i] == 34 || command[*i] == 39)
		{
			if (command[*i] == 34 && !*quotes)
				*quotes = command[*i];
			if (command[*i] == 39 && !*quotes)
				*quotes = command[*i];
			*quote_num += 1;
		}
		if (command[*i] == '$')
			break ;
		if (command[*i] == *quotes && *quote_num == 2)
		{
			*quote_num = 0;
			*quotes = 0;
		}
		*i += 1;
	}
}

int	var_length(char *cmd, int i)
{
	int	length;

	length = 0;
	while (cmd[i] && ft_cchr_str(cmd[i], ALLOWED) && cmd[i] != 34
		&& cmd[i] != 39)
	{
		i++;
		if (!ft_cchr_str(cmd[i], ALLOWED) || cmd[i] == '$'
			|| !cmd[i] || cmd[i] == 34 || cmd[i] == 39)
			break ;
		length++;
	}
	return (length);
}

void	jump_variable(char *cmd, int *i, int quote_num, t_replace_var *r_var)
{
	while (cmd[*i])
	{
		*i += 1;
		if ((cmd[*i] == 34 || cmd[*i] == 39) && quote_num)
		{
			while (cmd[*i] && quote_num)
			{
				if (cmd[*i] == 34 || cmd[*i] == 39)
					quote_num--;
				*i += 1;
			}
			if (!quote_num)
			{
				*i -= 1;
				r_var->quotes = 0;
				r_var->quote_num = 0;
				break ;
			}
		}
		if (cmd[*i] == '$')
		{
			*i -= 1;
			break ;
		}
	}
}

void	calc_var_name_length_end(char *command, int i, int *length,
		int quote_num_cpy)
{
	while (command[i])
	{
		if (command[i] == '$' && !quote_num_cpy)
			break ;
		if (!ft_cchr_str(command[i], ALLOWED))
			break ;
		if (command[i] == 34 || command[i] == 39)
		{
			while (command[i] && quote_num_cpy)
			{
				if (command[i] == 34 || command[i] == 39)
					quote_num_cpy--;
				*length += 1;
			}
			break ;
		}
		i++;
		*length += 1;
	}
}

void	calc_cmd_result_length_end(char *command, int i, int *length,
		int quote_num)
{
	if ((command[i] == 34 || command[i] == 39) && quote_num)
	{
		while (command[i] && quote_num)
		{
			if ((command[i] == 34 || command[i] == 39) && quote_num)
				quote_num--;
			i++;
		}
		while (command[i])
		{
			*length += 1;
			i++;
		}
	}
	else if (command[i] == '$' || !ft_cchr_str(command[i], ALLOWED))
	{
		while (command[i])
		{
			*length += 1;
			i++;
		}
	}
}
