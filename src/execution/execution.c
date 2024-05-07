/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:41:52 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/16 14:52:44 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_childs(pid_t *childs, int nbr_pipes, int *status)
{
	int	i;
	int	j;
	int	last_status;

	j = 0;
	i = nbr_pipes;
	while (j <= nbr_pipes)
	{
		if (waitpid(childs[j], status, 0) == childs[i])
			last_status = *status;
		j++;
	}
	return (last_status);
}

void	loop_scd_child(t_minishell *data, int **end, pid_t *childs)
{
	int	idx_pp;
	int	nb_pipes_copy;

	nb_pipes_copy = data->exec->nb_pipes;
	idx_pp = 0;
	while (nb_pipes_copy > 0)
	{
		if (nb_pipes_copy != 1)
			pipe(end[idx_pp + 1]);
		childs[idx_pp + 1] = fork();
		if (childs[idx_pp + 1] == -1)
			write_error("fork() Error", strerror(errno), 1);
		if (childs[idx_pp + 1] == 0 && nb_pipes_copy > 1)
			child_process(data, end[idx_pp], end[idx_pp + 1], idx_pp + 1);
		else if (childs[idx_pp + 1] == 0 && nb_pipes_copy == 1)
			child_process(data, end[idx_pp], NULL, idx_pp + 1);
		close_pipe(end[idx_pp]);
		idx_pp += 1;
		nb_pipes_copy--;
	}
	if (data->exec->fd != -1)
		close(data->exec->fd);
	if (idx_pp > 0)
		free_double_array_int(end, idx_pp - 1);
}

int	final_exec(t_minishell *minishell)
{
	int		**end;
	int		nbr_pipes;
	int		status;

	minishell->childs = create_childs(minishell->exec->nb_pipes, minishell);
	status = 0;
	nbr_pipes = minishell->exec->nb_pipes;
	end = minishell->exec->pipes;
	if (end)
		pipe(end[0]);
	minishell->childs[0] = fork();
	if (minishell->childs[0] == -1)
		write_error("fork() Error", strerror(errno), 1);
	if (minishell->childs[0] == 0 && minishell->exec->nb_pipes > 0)
		child_process(minishell, NULL, end[0], 0);
	else if (minishell->childs[0] == 0 && !minishell->exec->nb_pipes)
		child_process(minishell, NULL, NULL, 0);
	loop_scd_child(minishell, end, minishell->childs);
	status = wait_childs(minishell->childs, nbr_pipes, &status);
	if (WIFEXITED(status))
		return (free_exec(minishell->exec), WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (message_sign(WTERMSIG(status), minishell->exec), \
		128 + WTERMSIG(status));
	return (free_exec(minishell->exec), 0);
}

void	init_exec(t_minishell *minishell, t_exec *exec)
{
	int	i;

	i = -1;
	exec->index = minishell->index;
	exec->fd = minishell->fd;
	exec->redir = NULL;
	exec->cmds = NULL;
	exec->nb_pipes = lst_length(&minishell->token) - 1;
	exec->pipes = create_pipes(exec->nb_pipes, minishell);
	exec->redir = malloc(lst_length(&minishell->token) * sizeof(char **));
	if (!exec->redir)
		free_all_struct(minishell, 1, MALLOC_ERROR);
	exec->cmds = malloc(lst_length(&minishell->token) * sizeof(char **));
	if (!exec->cmds)
		free_all_struct(minishell, 1, MALLOC_ERROR);
	while (minishell->token)
	{
		exec->redir[++i] = minishell->token->files;
		exec->cmds[i] = minishell->token->cmd_array;
		minishell->token = minishell->token->next;
	}
	minishell->exec = exec;
}

int	parse_before_exec(t_minishell *minishell)
{
	t_exec	exec;
	t_token	*lst_copy;

	lst_copy = minishell->token;
	init_exec(minishell, &exec);
	minishell->token = lst_copy;
	if (minishell->token->cmd_array && minishell->token->cmd_array[0])
	{
		if (lst_length(&minishell->token) == 1 && \
		is_builtin(minishell->token->cmd_array[0]) == 1)
			return (redir_builtins(minishell->token->cmd_array, minishell, 0, \
			NULL));
		else
			return (final_exec(minishell));
	}
	else
		return (final_exec(minishell));
	return (0);
}
