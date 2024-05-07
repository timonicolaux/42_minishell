/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:01:47 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/09 13:27:14 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_var_env(t_minishell *minishell, int i, int fd)
{
	if (ft_strchr(minishell->env_array[i], '='))
	{
		ft_putstr_fd(minishell->env_array[i], fd);
		ft_putstr_fd("\n", fd);
	}
}

int	ft_env(t_minishell *minishell, int *fds)
{
	int		i;
	int		fd;

	fd = 1;
	if (fds != NULL)
	{
		if (fds[1] != -1)
			fd = fds[1];
	}
	i = 0;
	while (minishell->env_array[i])
	{
		if (minishell->env_array[i][0] == '?')
			i++;
		else
		{
			print_var_env(minishell, i, fd);
			i++;
		}
	}
	return (0);
}
