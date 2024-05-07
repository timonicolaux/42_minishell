/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:13:03 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/10 11:26:33 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token_list(char *token)
{
	t_token	*new;

	new = NULL;
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = token;
	new->previous = NULL;
	new->next = NULL;
	new->files = NULL;
	new->heredoc = NULL;
	new->cmd_array = NULL;
	new->command = NULL;
	new->special_vars = NULL;
	return (new);
}

void	lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*temp;

	temp = NULL;
	if (!(*lst))
	{
		*lst = new;
		(*lst)->previous = NULL;
		(*lst)->next = NULL;
	}
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->previous = temp;
	}
}

int	lst_length(t_token **lst)
{
	int		i;
	t_token	*lst_copy;

	lst_copy = NULL;
	if (!lst)
		return (0);
	else if (!(*lst) || !(*lst)->next)
		return (1);
	i = 0;
	lst_copy = *lst;
	while (lst_copy)
	{
		lst_copy = lst_copy->next;
		i++;
	}
	return (i);
}

int	lst_length_env(t_env **lst)
{
	int		i;
	t_env	*lst_copy;

	if (!lst)
		return (0);
	else if (!(*lst) || !(*lst)->next)
		return (1);
	i = 0;
	lst_copy = *lst;
	while (lst_copy)
	{
		lst_copy = lst_copy->next;
		i++;
	}
	return (i);
}
