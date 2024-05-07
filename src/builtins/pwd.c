/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:08:22 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/10 14:17:23 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_minishell *minishell, int *fds)
{
	char	*pwd;
	int		fd;

	fd = 1;
	if (fds != NULL)
	{
		if (fds[1] != -1)
			fd = fds[1];
	}
	pwd = get_pwd(minishell);
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	free(pwd);
	return (0);
}

char	*get_pwd(t_minishell *minishell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_printf("Error, no path found\n");
		free_all_struct(minishell, 1, MALLOC_ERROR);
	}
	return (pwd);
}

void	create_pwd_in_env(t_minishell *minishell, char *pwd)
{
	t_env	*new;

	new = new_env_list(minishell, "PWD", pwd);
	if (!new)
		free_all_struct(minishell, 1, MALLOC_ERROR);
	lstadd_back_env(&minishell->env, new);
}
