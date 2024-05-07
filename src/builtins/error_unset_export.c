/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_unset_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:41:20 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/10 13:27:13 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(int type, char *arg)
{
	if (type == 1)
		ft_printf("minishell: export: '%s': not a valid identifier\n", arg);
	if (type == 2)
		ft_printf("minishell: unset: '%s': not a valid identifier\n", arg);
}

int	check_equal_sign(char *arg, int type)
{
	if (arg[0] == '=' && type == 1)
	{
		print_error(type, arg);
		return (-1);
	}
	return (0);
}

int	uns_exp_error(int type, char *arg)
{
	int	i;

	i = -1;
	if (arg[0] >= '0' && arg[0] <= '9')
	{
		print_error(type, arg);
		return (-1);
	}
	while (arg[++i])
	{
		if (check_equal_sign(arg, type) == -1)
			return (-1);
		if (arg[i] == '=' && type == 1)
			return (0);
		if (!((arg[i] >= '0' && arg[i] <= '9') || (arg[i] >= 'A' && \
		arg[i] <= 'Z') || (arg[i] >= 'a' && arg[i] <= 'z') || arg[i] == '_'))
		{
			if ((type == 1 && arg[i] != '=') || (type == 2))
			{
				print_error(type, arg);
				return (-1);
			}
		}
	}
	return (0);
}
