/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:57:24 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/12 10:40:11 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_exit_no_args(t_minishell *data, int *fds, int in_child)
{
	if (lst_length(&data->token) == 1)
		ft_printf("exit\n");
	if (in_child == 1)
		exit_builtin(0, data, fds);
	free_all_struct(data, 0, NULL);
	exit(0);
}

void	clean_exit_one_arg(char *arg, t_minishell *data, int *fds, int in_child)
{
	int	result;

	result = (unsigned char)ft_atoi(arg);
	if (lst_length(&data->token) == 1)
		ft_printf("exit\n");
	if (in_child == 1)
		exit_builtin(result, data, fds);
	free_all_struct(data, 0, NULL);
	exit(result);
}

void	exit_non_num(char *arg, t_minishell *data, int *fds, int in_child)
{
	if (lst_length(&data->token) == 1)
		ft_printf("exit\nminishell: exit: %s: numeric argument \
		required\n", arg);
	else
	{
		write(2, "minishell: exit: ", 17);
		write(2, arg, ft_strlen(arg));
		write(2, ": numeric argument required\n", 28);
	}
	if (in_child == 1)
		exit_builtin(2, data, fds);
	free_all_struct(data, 0, NULL);
	exit(2);
}

void	exit_too_many_args(t_minishell *data, int in_child, int *fds)
{
	if (lst_length(&data->token) == 1)
		ft_printf("exit\nminishell: exit: too many arguments\n");
	else
		write(2, "minishell: exit: too many arguments\n", 36);
	if (in_child == 1)
		exit_builtin(1, data, fds);
}

int	ft_exit(t_minishell *data, char **cmd, int in_child, int *fds)
{
	char	**args;
	int		nb_args;

	args = cmd + 1;
	if (!cmd[1])
		clean_exit_no_args(data, fds, in_child);
	else
	{
		nb_args = size_double_array(args);
		if (ft_atoi(args[0]) == 0 && ft_strncmp(args[0], "0", 2) && \
		ft_strncmp(args[0], "+0", 3) && ft_strncmp(args[0], "-0", 3))
			exit_non_num(args[0], data, fds, in_child);
		else if (ft_atoi(args[0]) != 0 || !ft_strncmp(args[0], "0", 2) || \
		!ft_strncmp(args[0], "+0", 3) || !ft_strncmp(args[0], "-0", 3))
		{
			if (nb_args == 1)
				clean_exit_one_arg(args[0], data, fds, in_child);
			else
				exit_too_many_args(data, in_child, fds);
		}
	}
	return (1);
}
