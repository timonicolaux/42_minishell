/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:52:28 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/11 16:20:27 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**find_all_path(char **envp, t_minishell *minishell)
{
	int		i;
	char	*path_str;
	char	**all_path;

	i = 0;
	path_str = NULL;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			path_str = envp[i];
		i++;
	}
	path_str = ft_substr(path_str, 5, ft_strlen(path_str));
	all_path = ft_split_modified(path_str, ':', minishell);
	if (path_str)
		free (path_str);
	return (all_path);
}

char	*find_valid_path(char **cmd_array, char **all_path, t_minishell *data)
{
	char	*path_cmd;
	int		i;

	i = -1;
	if (!all_path)
		return (ft_strdup_minishell(data, "error"));
	if (all_path)
	{
		while (all_path[++i])
		{
			path_cmd = ft_strjoin(all_path[i], cmd_array[0]);
			if (access(path_cmd, X_OK) == 0)
				return (free_double_array_char(all_path), path_cmd);
			free(path_cmd);
		}
		free_double_array_char(all_path);
	}
	return (cmd_array[0]);
}

int	redir_builtins(char **cmd_array, t_minishell *data, int in_child, int *fd)
{
	int	result;
	int	*fds;

	result = -10;
	fds = NULL;
	if (in_child == 0)
		fds = set_fds(data->exec, 0, data);
	if (!ft_strncmp(cmd_array[0], "echo", 5))
		result = ft_echo(cmd_array, fds);
	if (!ft_strncmp(cmd_array[0], "cd", 3))
		result = ft_cd(data, cmd_array);
	if (!ft_strncmp(cmd_array[0], "pwd", 4))
		result = ft_pwd(data, fds);
	if (!ft_strncmp(cmd_array[0], "export", 7))
		result = ft_export(data, cmd_array, fds);
	if (!ft_strncmp(cmd_array[0], "unset", 6))
		result = ft_unset(data, cmd_array);
	if (!ft_strncmp(cmd_array[0], "env", 4))
		result = ft_env(data, fds);
	close_free_fds(fds);
	if (!ft_strncmp(cmd_array[0], "exit", 5))
		result = ft_exit(data, cmd_array, in_child, fd);
	if (in_child == 1 && result != -10)
		exit_builtin(result, data, fd);
	return (free_exec(data->exec), result);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "cd", 3) || \
	!ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "export", 7) || \
	!ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "env", 4) || \
	!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

void	exec_cmd(char **envp, char **cmd_arr, t_minishell *data, int *fds)
{
	char	*path_cmd;
	int		error_code;

	error_code = 127;
	if (!cmd_arr[0])
		exit_null_cmd(fds, data);
	redir_builtins(cmd_arr, data, 1, fds);
	path_cmd = find_valid_path(cmd_arr, find_all_path(envp, data), data);
	if (cmd_arr[0])
	{
		if (access(cmd_arr[0], X_OK) == 0)
			path_cmd = cmd_arr[0];
	}
	if (execve(path_cmd, cmd_arr, envp) == -1)
	{
		handle_error(cmd_arr, &error_code, path_cmd);
		if (ft_strncmp(path_cmd, cmd_arr[0], ft_strlen(cmd_arr[0]) + 1) != 0)
			free(path_cmd);
		free(fds);
		free_double_array_int(data->exec->pipes, data->exec->nb_pipes - 1);
		free_all_struct(data, 0, "");
	}
	close (0);
	close (1);
	exit(error_code);
}
