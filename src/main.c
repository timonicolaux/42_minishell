/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:49:25 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/16 14:26:59 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_marker;

void	main_process(t_minishell *minishell, char *input)
{
	put_env_in_array(minishell);
	quote_format_checker(minishell, input);
	rafters_checker(minishell, input);
	parser(input, minishell);
	exec_here_docs(minishell);
	update_error_code(parse_before_exec(minishell), minishell);
	add_history(input);
	free_all_but_env(minishell);
	init_structs_but_env(minishell);
}

void	ctrl_d(t_minishell *minishell)
{
	ft_printf("exit\n");
	free_all_struct(minishell, 0, "");
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;

	(void)ac;
	(void)av;
	init_structs(&minishell);
	init_env(env, &minishell);
	while (1)
	{
		signals();
		minishell.input = readline("[Minishell] : ");
		signals_child();
		if (g_sig_marker == 1)
			update_error_code(130, &minishell);
		if (minishell.input && *minishell.input)
			main_process(&minishell, minishell.input);
		if (!minishell.input)
			ctrl_d(&minishell);
		free(minishell.input);
		minishell.input = NULL;
		g_sig_marker = 0;
	}
	free_all_struct(&minishell, 0, "");
	return (0);
}
