/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable_utils4.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:38:55 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/10 13:16:01 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_to_value(t_send_back_value *val,
	char *command, t_replace_var *r_var)
{
	while (command[val->i_cpy] && ft_cchr_str(command[val->i_cpy], SPACES))
		val->i_cpy += 1;
	if (r_var->quote_num == 2)
	{
		val->i_cpy += 1;
		while (command[val->i_cpy] && ft_cchr_str(command[val->i_cpy], SPACES))
			val->i_cpy += 1;
	}
	val->index = val->i_cpy;
	while (command[val->i_cpy] && !ft_cchr_str(command[val->i_cpy], SPACES))
	{
		val->i_cpy += 1;
		val->length += 1;
	}
}

void	count_back_quotes_len(char *command, t_create_var_quote *c_var)
{
	int	quote_cpy;

	quote_cpy = c_var->quote_num;
	while (command[c_var->i_cpy] && c_var->quote_num)
	{
		if (command[c_var->i_cpy] == 34 || command[c_var->i_cpy] == 39)
			c_var->quote_num -= 1;
		c_var->i_cpy += 1;
		c_var->length += 1;
		if (command[c_var->i_cpy] == '$' && !c_var->dollar)
		{
			c_var->dollar = 1;
			c_var->dollar_index = c_var->i_cpy;
		}
	}
	c_var->quote_num = quote_cpy;
}

int	calc_var_name_length(int i, char *command, int quote_num)
{
	int	length;
	int	quote_num_cpy;

	length = 0;
	quote_num_cpy = quote_num;
	if (command[i] == '$')
	{
		i++;
		length++;
	}
	while (command[i] && quote_num)
	{
		if (command[i] == 34 || command[i] == 39)
			quote_num--;
		length++;
		i++;
	}
	calc_var_name_length_end(command, i, &length, quote_num_cpy);
	return (length);
}

int	calc_cmd_result_length(char *command, int quote_num, int *index)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (command[i])
	{
		if (i == *index)
		{
			calc_cmd_result_length_end(command, i, &length, quote_num);
			return (length);
		}
		if (command[i] == '\0')
			return (length);
		length++;
		i++;
	}
	return (length);
}

int	find_else_tilde(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i])
		{
			if (!ft_cchr_str(str[i], SPACES) && str[i] == '~')
				break ;
			if (!ft_cchr_str(str[i], SPACES))
				return (0);
			i++;
		}
		if (str[i] == '~' && str[i + 1] == '/')
			return (1);
		else if (str[i] == '~' && str[i + 1] == '\0')
			return (1);
		else if (str[i] == '~' && ft_cchr_str(str[i + 1], SPACES))
			return (2);
		i++;
	}
	return (0);
}
