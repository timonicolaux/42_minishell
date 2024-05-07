/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:15:48 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/15 15:05:01 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	size_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_double_array_char(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_double_array_int(int **array, int index)
{
	while (index >= 0)
	{
		free(array[index]);
		index--;
	}
	free(array);
}

void	free_exec(t_exec *exec)
{
	if (exec)
	{
		if (exec->cmds != NULL)
		{
			free(exec->cmds);
			exec->cmds = NULL;
		}
		if (exec->redir != NULL)
		{
			free(exec->redir);
			exec->redir = NULL;
		}
		exec = NULL;
	}
}

void	exit_builtin(int result, t_minishell *ms, int *fds)
{
	int	index_pipe;
	int	nb_pipe;
	int	i;

	i = 0;
	nb_pipe = ms->exec->nb_pipes;
	index_pipe = ms->index_pipe;
	while (i <= index_pipe && nb_pipe > 0)
	{
		close_pipe(ms->exec->pipes[i]);
		nb_pipe--;
		i++;
	}
	free(fds);
	free_double_array_int(ms->exec->pipes, ms->exec->nb_pipes - 1);
	free_all_struct(ms, 0, "");
	close(1);
	close(0);
	exit(result);
}
