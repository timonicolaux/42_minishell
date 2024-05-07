/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:38:17 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/09 14:53:31 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_already_print(int *array, int index, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (array[i] == index)
			return (-1);
		i++;
	}
	return (0);
}

char	*find_to_test(int i, char **array, int *array_printed)
{
	int	j;

	j = -1;
	while (array[++j])
	{
		if (check_already_print(array_printed, j, array) == 0)
		{
			array_printed[i] = j;
			break ;
		}
	}
	return (array[j]);
}

char	*find_to_print(int i, char **array, int *array_printed, char *var_print)
{
	int	j;

	j = -1;
	while (array[++j])
	{
		if (ft_strncmp(var_print, array[j], ft_strlen(array[j])) > 0 && \
		check_already_print(array_printed, j, array) == 0)
		{
			array_printed[i] = j;
			var_print = array[j];
			j = -1;
		}
	}
	return (var_print);
}

void	print_var(char *str, int *fds, t_env *env)
{
	int		fd;
	t_env	*lst_copy;

	lst_copy = env;
	fd = update_fd(fds);
	while (env)
	{
		if (!ft_strncmp(str, env->name, ft_strlen(env->name)))
			break ;
		env = env->next;
	}
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(env->name, fd);
	if (env->value)
	{
		ft_putchar_fd('=', fd);
		ft_putchar_fd('"', fd);
		ft_putstr_fd(env->value, fd);
		ft_putchar_fd('"', fd);
	}
	ft_putstr_fd("\n", fd);
	env = lst_copy;
}

void	export_print_env(char **array, int *fds, t_minishell *minishell)
{
	int		i;
	char	*var_to_print;
	int		*array_printed;

	array_printed = malloc(ft_strlen_dbl_array(array) * sizeof(int));
	if (!array_printed)
		free_all_struct(minishell, 1, MALLOC_ERROR);
	i = 0;
	while (i < ft_strlen_dbl_array(array))
	{
		array_printed[i] = -1;
		i++;
	}
	i = -1;
	while (array[++i])
	{
		var_to_print = find_to_test(i, array, array_printed);
		var_to_print = find_to_print(i, array, array_printed, var_to_print);
		if (var_to_print[0] != '?' && ft_strncmp(var_to_print, "_=", 2))
			print_var(var_to_print, fds, minishell->env);
	}
	free(array_printed);
}
