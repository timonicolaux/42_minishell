/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:09:24 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/09 14:27:14 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_option(char *str)
{
	int	i;

	i = 1;
	if (str)
	{
		if (str[0] != '-')
			return (0);
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	close_free_fds(int *fds)
{
	close_pipe(fds);
	if (fds != NULL)
		free(fds);
}

int	update_fd(int *fds)
{
	int	fd;

	fd = 1;
	if (fds != NULL)
	{
		if (fds[1] != -1)
			fd = fds[1];
	}
	return (fd);
}

int	ft_echo(char **cmd, int *fds)
{
	int		i;
	int		fd;
	char	**args;

	fd = update_fd(fds);
	args = cmd + 1;
	i = 0;
	if (args[0] != NULL)
	{
		while (check_option(args[i]) == 1)
			i++;
		while (args[i])
		{
			ft_putstr_fd(args[i], fd);
			if (args[i + 1])
				ft_putstr_fd(" ", fd);
			i++;
		}
	}
	if (check_option(args[0]) == 0)
		ft_putstr_fd("\n", fd);
	return (0);
}
