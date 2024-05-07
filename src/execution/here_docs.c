/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:40:27 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/15 14:56:23 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	here_doc(char *stopper)
{
	char	*input;
	int		pp[2];

	input = NULL;
	pipe(pp);
	while (1)
	{
		input = readline("< ");
		if (input && !ft_strncmp(input, stopper, ft_strlen(stopper) + 1))
		{
			free(input);
			close(pp[1]);
			return (pp[0]);
		}
		if (!input)
		{
			ft_printf("minishell: warning: here-document ");
			ft_printf("delimited by end-of-file (wanted `%s')\n", stopper);
			return (free(input), -1);
		}
		write(pp[1], input, ft_strlen(input));
		write(pp[1], "\n", 1);
		free(input);
	}
	return (-1);
}

void	exec_here_docs(t_minishell *minishell)
{
	t_token	*lst;
	int		i;
	int		index;
	int		fd;

	index = -1;
	fd = -1;
	i = -1;
	lst = minishell->token;
	while (++index < lst_length(&minishell->token))
	{
		if (lst->heredoc)
		{
			while (lst->heredoc[++i])
			{
				minishell->index = index;
				if (fd != -1)
					close(fd);
				fd = here_doc(lst->heredoc[i] + 2);
			}
			i = -1;
		}
		lst = lst->next;
	}
	minishell->fd = fd;
}
