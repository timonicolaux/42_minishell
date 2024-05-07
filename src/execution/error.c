/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:49:53 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/16 11:09:01 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_error(char *str1, char *str2, int exit_type)
{
	if (ft_strncmp("command not found", str2, ft_strlen(str2)))
		write(2, "minishell: ", 11);
	write(2, str1, ft_strlen(str1));
	write(2, ": ", 2);
	write(2, str2, ft_strlen(str2));
	write(2, "\n'", 1);
	if (exit_type == 1)
		exit(EXIT_FAILURE);
}

void	write_error_file(char *str1, char *str2, int exit_type, t_minishell *ms)
{
	if (ft_strncmp("command not found", str2, ft_strlen(str2)))
		write(2, "minishell: ", 11);
	write(2, str1, ft_strlen(str1));
	write(2, ": ", 2);
	write(2, str2, ft_strlen(str2));
	write(2, "\n'", 1);
	if (exit_type == 1)
		free_all_struct(ms, 1, "");
}

void	handle_error(char **cmd_arr, int *error_code, char *path_cmd)
{
	if (!ft_strncmp("error", path_cmd, ft_strlen(path_cmd) + 1))
		write_error(cmd_arr[0], "No such file or directory", 2);
	else
	{
		if (access(cmd_arr[0], F_OK) == 0)
		{
			if (ft_strchr(cmd_arr[0], '.'))
				write_error(cmd_arr[0], "Permission denied", 2);
			else
				write_error(cmd_arr[0], "Is a directory", 2);
			*error_code = 126;
		}
		else
			write_error(cmd_arr[0], "command not found", 2);
	}
}

void	exit_null_cmd(int *fds, t_minishell *data)
{
	free(fds);
	free_double_array_int(data->exec->pipes, data->exec->nb_pipes - 1);
	free_all_struct(data, 0, "");
	close (0);
	close (1);
	exit(0);
}
