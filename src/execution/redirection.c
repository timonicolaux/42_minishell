/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:50:12 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/16 14:11:28 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*initialize_fds(void)
{
	int	*fds;

	fds = NULL;
	fds = malloc(2 * sizeof(int));
	if (!fds)
		return (NULL);
	fds[0] = -1;
	fds[1] = -1;
	return (fds);
}

int	open_infile(int *fds, char *file, int index_pipe, t_minishell *minishell)
{
	int	fd;

	fd = fds[0];
	if (file[0] == '<' && index_pipe == minishell->exec->index)
	{
		if (fd != -1)
			close (fd);
		fd = minishell->exec->fd;
	}
	else if (file[0] != '<')
	{
		if (fd != -1)
			close (fd);
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			free(fds);
			write_error_file(file, strerror(errno), 1, minishell);
		}
	}
	return (fd);
}

int	open_outfile(int *fds, char *file, t_minishell *minishell)
{
	int	fd;

	fd = fds[1];
	if (fd != -1)
		close (fd);
	if (file[0] == '>')
		fd = open(file + 1, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(fds);
		write_error_file(file, strerror(errno), 1, minishell);
	}
	return (fd);
}

int	*set_fds(t_exec *exec, int idx_pipe, t_minishell *ms)
{
	int		*fds;
	int		i;
	char	**files;

	i = 0;
	fds = initialize_fds();
	if (!fds)
		free_all_struct(ms, 1, MALLOC_ERROR);
	files = exec->redir[idx_pipe];
	if (files && files[0] != NULL)
	{
		while (files[i] != NULL)
		{
			if (files[i][0] == '<')
				fds[0] = open_infile(fds, files[i] + 1, idx_pipe, ms);
			if (files[i][0] == '>')
				fds[1] = open_outfile(fds, files[i] + 1, ms);
			i++;
		}
	}
	return (fds);
}
