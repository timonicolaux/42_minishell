/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_rafters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:54:58 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/16 11:00:24 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_double_rafters(char *token, int *i)
{
	int	current_input;
	int	i_cpy;

	current_input = token[*i];
	i_cpy = *i;
	i_cpy++;
	if (token[i_cpy] == current_input)
	{
		*i += 1;
		return (2);
	}
	return (1);
}

void	check_double_rafters_str(char *token, int *i, char *result, int *j)
{
	int	current_input;
	int	i_cpy;

	current_input = token[*i];
	i_cpy = *i;
	i_cpy++;
	if (token[i_cpy] == current_input)
	{
		result[*j] = token[*i];
		*j += 1;
		*i += 1;
	}
}
