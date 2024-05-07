/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:52:49 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/11 12:37:30 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_structs(t_minishell *minishell)
{
	minishell->index = 0;
	minishell->fd = 0;
	minishell->index_pipe = 0;
	minishell->env_array = NULL;
	minishell->token = NULL;
	minishell->env = NULL;
	minishell->exec = NULL;
	minishell->childs = NULL;
	minishell->input = NULL;
}

void	init_structs_but_env(t_minishell *minishell)
{
	minishell->index = 0;
	minishell->fd = 0;
	minishell->token = NULL;
	minishell->exec = NULL;
}
