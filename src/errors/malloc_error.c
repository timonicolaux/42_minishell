/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:04:39 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/12 11:29:45 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_struct(t_minishell *minishell, int error, char *message)
{
	if (minishell && minishell->env_array != NULL)
		free_char_array(minishell->env_array);
	if (minishell && minishell->env != NULL)
		free_env(minishell->env);
	if (minishell && minishell->token != NULL)
		free_token(minishell->token);
	if (minishell && minishell->exec != NULL)
		free_exec(minishell->exec);
	if (minishell && minishell->childs != NULL)
		free(minishell->childs);
	if (minishell && minishell->input != NULL)
		free(minishell->input);
	minishell->fd = -1;
	minishell->exec = NULL;
	minishell->index = -1;
	minishell->sv_i = 0;
	rl_clear_history();
	if (error == 1)
	{
		ft_printf("%s", message);
		exit(EXIT_FAILURE);
	}
}

void	free_all_but_env(t_minishell *minishell)
{
	if (minishell && minishell->token != NULL)
		free_token(minishell->token);
	if (minishell && minishell->childs != NULL)
	{
		free(minishell->childs);
		minishell->childs = NULL;
	}
	minishell->fd = -1;
	minishell->index = -1;
	minishell->sv_i = 0;
}

void	free_env(t_env *env)
{
	t_env	*env_next;

	env_next = NULL;
	if (!env)
		return ;
	while (env)
	{
		env_next = env->next;
		if (env->name)
			free(env->name);
		if (env->value)
			free(env->value);
		free(env);
		env = env_next;
	}
}

void	free_token(t_token *token)
{
	t_token	*token_next;

	token_next = NULL;
	if (!token)
		return ;
	while (token != NULL)
	{
		token_next = token->next;
		if (token->token || token->token != NULL)
			free(token->token);
		if (token->command || token->command != NULL)
			free(token->command);
		free_char_array(token->files);
		free_char_array(token->heredoc);
		free_char_array(token->cmd_array);
		free_char_array(token->special_vars);
		free(token);
		token = NULL;
		token = token_next;
	}
}

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}
