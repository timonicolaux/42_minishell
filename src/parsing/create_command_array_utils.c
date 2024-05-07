/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_array_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:37:12 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/09 13:20:17 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calc_cmd_height(t_token *token, char *command)
{
	int	i;
	int	height;

	i = 0;
	height = 0;
	while (command[i])
	{
		while (command[i] && ft_cchr_str(command[i], SPACES))
			i++;
		if (!command[i])
			return (height);
		if (command[i] != 34 && command[i] != 39)
		{
			cmd_length(token, command, &i);
			height++;
		}
		if (command[i] == 34 || command[i] == 39)
		{
			find_delete_quotes(command, &i);
			i++;
			height++;
		}
	}
	return (height);
}

int	cmd_length(t_token *token, char *cmd, int *i)
{
	int	count;
	int	i_cpy;

	count = 0;
	i_cpy = *i;
	while (cmd[*i])
	{
		if (ft_cchr_str(cmd[*i], SPACES))
			break ;
		if (cmd[*i] == 34 || cmd[*i] == 39)
		{
			find_delete_quotes(token->token, i);
			count = *i - i_cpy;
		}
		count++;
		*i += 1;
	}
	return (count);
}
