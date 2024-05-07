/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:59:32 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/15 11:20:23 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_minishell *minishell, char **cmd_array)
{
	int	res;

	res = -1;
	if (cmd_array[1])
	{
		if (!ft_strncmp(cmd_array[1], "~", 2))
			res = cd_home(minishell);
		else
			res = cd_path(minishell, cmd_array[1]);
	}
	else if (!cmd_array[1])
		res = cd_home(minishell);
	if (res == -1)
	{
		res = 1;
		ft_printf("minishell: cd: %s: No such file or directory\n", \
		cmd_array[1]);
	}
	return (res);
}

int	cd_home(t_minishell *minishell)
{
	char	*env;
	int		res;
	char	*old_pwd;

	env = getenv("HOME");
	if (!env)
	{
		ft_printf("Error, no path found\n");
		free_all_struct(minishell, 0, "");
	}
	old_pwd = get_pwd(minishell);
	res = chdir(env);
	if (res >= 0)
	{
		store_old_pwd(minishell, old_pwd);
		get_and_store_pwd(minishell);
	}
	free(old_pwd);
	return (res);
}

int	cd_path(t_minishell *minishell, char *path)
{
	int		res;
	char	*old_pwd;

	old_pwd = get_pwd(minishell);
	res = chdir(path);
	if (res >= 0)
	{
		store_old_pwd(minishell, old_pwd);
		get_and_store_pwd(minishell);
	}
	free(old_pwd);
	return (res);
}

void	store_old_pwd(t_minishell *minishell, char *old_pwd)
{
	t_env	*env_cpy;

	env_cpy = minishell->env;
	while (minishell->env)
	{
		if (!ft_strncmp(minishell->env->name, "OLDPWD", 4))
		{
			free(minishell->env->value);
			minishell->env->value = ft_strdup_minishell(minishell, old_pwd);
		}
		minishell->env = minishell->env->next;
	}
	minishell->env = env_cpy;
}

void	get_and_store_pwd(t_minishell *minishell)
{
	char	*pwd;
	int		found;
	t_env	*env_cpy;

	env_cpy = minishell->env;
	found = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		free_all_struct(minishell, 1, NO_PATH);
	while (minishell->env)
	{
		if (!ft_strncmp(minishell->env->name, "PWD", 4))
		{
			found = 1;
			free(minishell->env->value);
			minishell->env->value = ft_strdup_minishell(minishell, pwd);
		}
		minishell->env = minishell->env->next;
	}
	minishell->env = env_cpy;
	if (!found)
		create_pwd_in_env(minishell, pwd);
	free(pwd);
}
