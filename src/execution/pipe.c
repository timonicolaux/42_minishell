/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:09:35 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/11 11:05:21 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_pipe(int *end)
{
	if (end)
	{
		if (end[0] != -1)
			close(end[0]);
		if (end[1] != -1)
			close(end[1]);
	}
}

int	choose_fd_to_redir(int *fds, int *end_in, int *end_out, int *fd_in)
{
	int	fd_out;

	*fd_in = fds[0];
	fd_out = fds[1];
	if (fds[0] == -1 && end_in)
		*fd_in = end_in[0];
	if (fds[1] == -1 && end_out)
		fd_out = end_out[1];
	return (fd_out);
}

void	child_process(t_minishell *data, int *end_in, int *end_out, int index)
{
	int	*fds;
	int	fd_in;
	int	fd_out;

	data->index_pipe = index;
	fds = set_fds(data->exec, index, data);
	fd_out = choose_fd_to_redir(fds, end_in, end_out, &fd_in);
	if (fd_out != -1)
	{
		if (dup2(fd_out, 1) == -1)
			write_error("Error dup2 stdout", strerror(errno), 1);
		if (!is_builtin(data->exec->cmds[index][0]))
			close_pipe(end_out);
	}
	if (fd_in != -1)
	{
		if (dup2(fd_in, 0) == -1)
			write_error("Error dup2 stdin", strerror(errno), 1);
		if (!is_builtin(data->exec->cmds[index][0]))
			close_pipe(end_in);
	}
	close_pipe(fds);
	exec_cmd(data->env_array, data->exec->cmds[index], data, fds);
}

int	**create_pipes(int nb_pipes, t_minishell *minishell)
{
	int	**end;
	int	i;

	i = -1;
	end = NULL;
	if (!nb_pipes)
		return (end);
	end = malloc(nb_pipes * sizeof(int *));
	if (!end)
		free_all_struct(minishell, 1, MALLOC_ERROR);
	while (++i < nb_pipes)
	{
		end[i] = malloc(2 * sizeof(int));
		if (!end[i])
		{
			free_double_array_int(end, i - 1);
			free_all_struct(minishell, 1, MALLOC_ERROR);
		}
	}
	return (end);
}

pid_t	*create_childs(int nb_pipes, t_minishell *minishell)
{
	pid_t	*childs;
	int		i;

	i = 0;
	childs = malloc((nb_pipes + 1) * sizeof(pid_t));
	if (!childs)
		free_all_struct(minishell, 1, MALLOC_ERROR);
	while (nb_pipes >= 0)
	{
		childs[i] = 0;
		nb_pipes--;
		i++;
	}
	return (childs);
}
