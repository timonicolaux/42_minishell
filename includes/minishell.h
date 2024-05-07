/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:38:05 by tnicolau          #+#    #+#             */
/*   Updated: 2024/04/16 14:51:46 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE

# include "../ft_printf/includes/ft_printf.h"

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# ifndef SPACES
#  define SPACES " \t\n\v\r\f\0"
# endif

# ifndef ALLOWED
#  define ALLOWED "$ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghi\
jklmnopqrstuvwxyz0123456789_\0"
# endif

# ifndef NO_PATH
#  define NO_PATH "Error, no path found\n"
# endif

# ifndef MALLOC_ERROR
#  define MALLOC_ERROR "Error during memory allocation\n"
# endif

# ifndef SYNTAX_ERROR
#  define SYNTAX_ERROR "syntax error near unexpected token `newline'\n"
# endif

extern int	g_sig_marker;

typedef struct s_token
{
	char			*token;
	char			**files;
	char			**heredoc;
	char			**special_vars;
	char			*command;
	char			**cmd_array;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_exec
{
	char	***redir;
	char	***cmds;
	int		**pipes;
	int		nb_pipes;
	int		index;
	int		fd;
}	t_exec;

typedef struct s_minishell
{
	t_env	*env;
	t_exec	*exec;
	int		index;
	int		fd;
	char	**env_array;
	int		index_pipe;
	int		sv_i;
	char	*input;
	t_token	*token;
	pid_t	*childs;
}	t_minishell;

/* STRUCTS FOR VARS */

typedef struct s_replace_var
{
	int		i;
	int		i_cpy;
	int		quotes;
	int		quote_num;
	int		quote_num_cpy;
	char	*result;
	char	*cmd_cpy;
}	t_replace_var;

typedef struct s_rep_var_classic
{
	char	*var;
	int		i_cpy;
	int		j;
	int		length;
}	t_rep_var_classic;

typedef struct s_create_var_quote
{
	int		i_cpy;
	int		i_cpycpy;
	int		length;
	int		quote_num;
	int		dollar;
	int		dollar_index;
	char	*var;
}	t_create_var_quote;

typedef struct s_create_var_quote_str
{
	char	*result;
	int		quote_num;
	int		j;
	int		k;
}	t_create_var_quote_str;

typedef struct s_join_cmd_result
{
	char	*str;
	int		length;
	int		i;
	int		j;
	int		k;
}	t_join_cmd_result;

typedef struct s_join_result_cmd_end
{
	int		quote_cpy;
	int		quotes;
	int		q_cpy;
	int		i;
	int		env_name_len;
	char	*env_name;
}	t_join_result_cmd_end;

typedef struct s_rep_special_var
{
	char	*result;
	int		length;
	int		index;
	int		i;
	int		j;
	int		var_len;
}	t_rep_special_var;

typedef struct s_send_back_value
{
	int		length;
	int		j;
	int		i_cpy;
	int		index;
	char	*result;
}	t_send_back_value;

typedef struct s_locate_special_vars
{
	int		length;
	int		k;
	int		l;
	char	*value;
}	t_locate_special_vars;

/* STRUCTS FOR COMMANDS */

typedef struct s_del_str_from_str
{
	int		start;
	int		end;
	char	*result;
}	t_del_str_from_str;

typedef struct s_add_quote_cmd_to_array
{
	int	length;
	int	start;
	int	i_cpy;
}	t_add_quote_cmd_to_array;

/* STRUCTS FOR FILES */

typedef struct s_check_infile_outfile
{
	int		i;
	int		j;
	int		height;
	int		total_size;
	char	**file;
}	t_check_infile_outfile;

typedef struct s_spaces_remover
{
	char	*result;
	int		i;
	int		j;
	int		len;
	int		quote;
}	t_spaces_remover;

/* STRUCTS FOR QUOTES */

typedef struct s_clean_quotes
{
	int	i;
	int	i_cpy;
	int	quote_delete_index;
}	t_clean_quotes;

typedef struct s_delete_quotes
{
	int		i;
	int		j;
	int		end;
	int		length;
	char	*result;
}	t_delete_quotes;

typedef struct s_rep_var_quotes
{
	char	*result;
	int		index;
	int		i_cpy;
}	t_rep_var_quotes;

/* BUILTINS */

int		ft_echo(char **cmd, int *fds);
int		ft_pwd(t_minishell *minishell, int *fds);
char	*get_pwd(t_minishell *minishell);
void	create_pwd_in_env(t_minishell *minishell, char *pwd);
int		ft_cd(t_minishell *minishell, char **cmd_array);
int		cd_home(t_minishell *minishell);
int		cd_path(t_minishell *minishell, char *path);
void	store_old_pwd(t_minishell *minishell, char *old_pwd);
void	get_and_store_pwd(t_minishell *minishell);

int		ft_env(t_minishell *minishell, int *fds);
int		update_fd(int *fds);
int		ft_exit(t_minishell *data, char **cmd, int in_child, int *fds);
int		uns_exp_error(int type, char *arg);
int		ft_export(t_minishell *minishell, char **cmd, int *fds);
void	export_print_env(char **array, int *fds, t_minishell *minishell);
int		ft_unset(t_minishell *minishell, char **args);
int		redir_builtins(char **cmd_array, t_minishell *data,
			int in_child, int *fd);
int		is_builtin(char *cmd);

/* PARSING */

void	parser(char *input, t_minishell *minishell);
void	check_for_files(t_minishell *minishell, t_token *token);
void	check_files_spaces(t_minishell *minishell, t_token *token);

void	tokenize_input(t_minishell *minishell, char *input);
void	create_tokens(t_minishell *minishell, int start, int end, char *input);
void	add_token_to_list(t_minishell *minishell, char *result);

char	**check_infile_outfile(t_minishell *minishell, t_token *token);
void	check_infile_outfile_loop(t_minishell *minishell, t_token *token,
			t_check_infile_outfile *check);
int		calc_file_height(char *token);
void	create_file_str(t_minishell *ms, t_token *token, int i,
			t_check_infile_outfile *check);
int		calc_total_file_size(char *token, int *i);
int		create_file_str_loop(char *token, int *i,
			t_check_infile_outfile *check);
int		create_file_str_copy_loop(char *tok, int *i, int *j,
			t_check_infile_outfile *check);
int		calc_total_file_size_loop(char *token, int *i);

char	*delete_spaces(t_minishell *minishell, char *file);
char	*spaces_remover(t_minishell *minishell, char *str);
void	spaces_remover_loop(t_spaces_remover *s, char *str);
int		final_file_len(char *str);
int		final_file_len_loop(char *str, int *size, int quote, int *i);
void	free_str_and_struct(t_minishell *minishell, char *str);

t_token	*new_token_list(char *token);
void	lstadd_back_token(t_token **lst, t_token *new);
int		lst_length(t_token **lst);
int		lst_length_env(t_env **lst);

void	lstadd_back_env(t_env **lst, t_env *new);

void	extract_command(t_minishell *minishell, t_token *token);
char	*create_string(char *src, t_del_str_from_str *t_del,
			t_minishell *minishell, int length);
char	*del_str_from_str(t_minishell *minishell, char *src, char *del);

void	clean_command_array(t_token *token, t_minishell *ms);
void	create_special_vars_array(t_minishell *minishell, t_token *token);
char	*clean_quotes(t_minishell *ms, char *cmd);
char	*clean_spaced_quotes(t_minishell *ms, char *cmd,
			t_clean_quotes *q_clean);
int		find_delete_quotes(char *command, int *i);
char	*delete_quotes(t_minishell *ms, char *cmd, int start, int *index);
int		delete_quotes_loop(t_delete_quotes *del, int *index,
			int start, char *cmd);

void	clean_command_array_loop(t_token *token, t_minishell *ms, int *i);
void	clean_cmd_array_functions(t_token *token, t_minishell *ms, int *i);

void	create_command_array(t_minishell *minishell, t_token *token);
void	initialize_cmd_array(t_minishell *minishell, t_token *token);
int		calc_cmd_height(t_token *token, char *command);
int		cmd_length(t_token *token, char *cmd, int *i);
void	add_cmd_to_array(t_minishell *minishell, t_token *token,
			int *i, int *j);
void	add_quote_cmd_to_array(t_minishell *minishell, t_token *token,
			int *i, int *j);
int		add_quote_cmd_to_array_loop(t_token *token,
			t_add_quote_cmd_to_array *s_cmd, int *i);

char	*check_tilde(t_minishell *minishell, char *str);
void	replace_tilde_str(char *home, char *result, char *str);
void	replace_tilde_only(char *home, char *result, char *str);

void	store_special_vars(t_minishell *minishell, char *env, t_token *token);
int		check_double_rafters(char *token, int *i);
void	check_double_rafters_str(char *token, int *i, char *result, int *j);

void	check_for_heredoc(t_minishell *minishell);
void	find_heredoc(t_minishell *minishell, t_token *token);
void	create_heredoc_array(t_minishell *minishell,
			t_token *token, int length);
void	update_files_array(t_minishell *minishell, t_token *token, int length);
int		ft_strlen_dbl_array(char **str);

void	check_special_vars(t_minishell *ms);
void	find_special_vars(t_token *token, t_minishell *ms);
void	locate_special_vars(int *i, int *j, t_token *token, t_minishell *ms);
char	*replace_special_vars(t_minishell *ms,
			char *cmd, char *var, char *value);
char	*copy_special_var(char *value, char *cmd, t_rep_special_var	*rsp_var);
int		find_special_var_index(char *cmd, char *var);
char	*find_special_var_value(char *var, t_minishell *ms);
void	print_cmd_array(t_token *token);

/* REPLACE VARIABLE */

char	*replace_var_quote_manager(char *command, t_minishell *ms,
			t_token *token, t_replace_var *r_var);
char	*replace_var_classic_manager(char *command, t_minishell *ms,
			t_token *token, t_replace_var *r_var);
char	*replace_variable(char *cmd, t_minishell *ms, t_token *token);
char	*replace_var_quotes(char *command, t_replace_var *r_var,
			t_minishell *ms, t_token *token);
char	*replace_var_classic(char *command, int i, t_minishell *ms,
			t_token *token);

/* REPLACE VARIABLE UTILS */

char	*create_var_quote(char *command, int *i, t_minishell *ms,
			t_token *token);
char	*store_special_var(t_minishell *ms, t_token *token);
void	check_similar(int *i, int *j, t_token *token,
			t_locate_special_vars *s);
char	*find_var_value(char *var, t_minishell *ms, t_token *token);
void	join_result_null_result(t_join_cmd_result *j, t_replace_var *r_var,
			t_join_result_cmd_end *join_end, char *cmd);

/* REPLACE VARIABLE UTILS 2 */

char	*treat_var_result(t_minishell *minishell,
			t_replace_var *r_var, char *command);
char	*join_cmd_result(t_minishell *minishell, t_replace_var *r_var,
			char *command, int *index);
void	join_result_cmd_end(t_minishell *minishell, char *command,
			t_join_cmd_result *join, t_replace_var *r_var);
void	init_join_result_cmd_end(t_minishell *ms,
			t_join_result_cmd_end *join_end, t_replace_var *r_var);
void	join_middle(char *command, t_join_result_cmd_end *join_end,
			t_join_cmd_result *join);

/* REPLACE VARIABLE UTILS 3 */

void	move_to_dollar(int *quote_num, int *quotes, int *i, char *command);
int		var_length(char *cmd, int i);
void	jump_variable(char *cmd, int *i, int quote_num, t_replace_var *r_var);
void	calc_var_name_length_end(char *command, int i,
			int *length, int quote_num_cpy);
void	calc_cmd_result_length_end(char *command, int i,
			int *length, int quote_num);

/* REPLACE VARIABLE UTILS 4 */

void	move_to_value(t_send_back_value *val, char *command,
			t_replace_var *r_var);
void	count_back_quotes_len(char *command, t_create_var_quote *c_var);
int		calc_cmd_result_length(char *command, int quote_num, int *index);
int		calc_var_name_length(int i, char *command, int quote_num);
int		find_else_tilde(char *str);

/* REPLACE VARIABLE UTILS 5 */

char	*rep_var_double_quote(char *command, t_replace_var *r_var,
			t_minishell *minishell, t_token *token);
char	*rep_var_single_quote(char *command, t_replace_var *r_var,
			t_minishell *minishell, t_token *token);
char	*send_back_value(t_minishell *ms, char *command,
			t_rep_var_quotes *q, t_replace_var *r_var);
char	*send_back_value_loop(t_minishell *ms, t_send_back_value *val,
			char *command, t_replace_var *r_var);
int		find_questionmark(char *command);

/* EXECUTION */

char	**ft_split_modified(char const *s, char c, t_minishell *data);
void	exec_cmd(char **envp, char **cmd_arr, t_minishell *data, int *fds);
void	free_double_array_char(char **array);
int		size_double_array(char **array);
void	free_double_array_int(int **array, int index);
void	write_error(char *str1, char *str2, int exit_type);
void	write_error_file(char *str1, char *str2, int exit_type,
			t_minishell *ms);
void	handle_error(char **cmd_arr, int *error_code, char *path_cmd);
int		*set_fds(t_exec *exec, int idx_pipe, t_minishell *ms);
void	close_pipe(int *end);
void	child_process(t_minishell *data, int *end_in, int *end_out, int index);
int		**create_pipes(int nb_pipes, t_minishell *minishell);
int		parse_before_exec(t_minishell *minishell);
void	free_exec(t_exec *exec);
int		here_doc(char *stopper);
void	exec_here_docs(t_minishell *minishell);
pid_t	*create_childs(int nb_pipes, t_minishell *minishell);
void	exit_builtin(int result, t_minishell *ms, int *fds);
void	close_free_fds(int *fds);
void	exit_null_cmd(int *fds, t_minishell *data);

/* SIGNALS */

void	signals(void);
void	signals_child(void);
void	signal_ctrl_c(void);
void	signal_ctrl_backslash(void);
void	handle_sigint(int signal);
void	signal_child_ctrl_c(void);
void	signal_child_ctrl_backslash(void);
void	handle_sigint_child(int signal);
void	message_sign(int code, t_exec *exec);

/* UTILS */

char	*ft_strdup_minishell(t_minishell *minishell, char *s);
char	*ft_strjoin_shell(t_minishell *minishell, char *s1, char *s2);

/* ERROR HANDLING */

void	quote_format_checker(t_minishell *ms, char *input);
void	quote_format_checker_loop(char *input, int *i,
			int current_input, int *counter);
void	rafters_checker(t_minishell *ms, char *input);
void	too_many_rafters(t_minishell *ms, char *input, int length);
void	check_valid_pipes(t_minishell *minishell, t_token *token);
void	check_empty_cmd(t_minishell *ms, char *command);
void	empty_heredoc(t_minishell *ms, char *str, char **here_doc_array);
void	check_empty_redir(t_minishell *minishell, char *str, char **file_array);

void	free_all_struct(t_minishell *minishell, int error, char *message);
void	free_all_but_env(t_minishell *minishell);
void	free_env(t_env *env);
void	free_token(t_token *token);
void	free_char_array(char **array);

void	init_structs(t_minishell *minishell);
void	init_structs_but_env(t_minishell *minishell);

/*ENVIRONNEMENT*/

void	update_error_code(int code, t_minishell *data);
void	init_env(char **env, t_minishell *minishell);
void	init_env_loop(char **env, char **env_split, t_env *new_lst,
			t_minishell *ms);
char	**split_env(char *env, t_minishell *minishell);
void	put_env_in_array(t_minishell *data);
char	*get_env_value(t_minishell *minishell, char	*find);
char	*get_env_name(t_minishell *minishell, char *find);
void	concat_str_three(char *s1, char *s2, char *s3, char *new_s);
char	*ft_strjoin_three(t_minishell *ms, char *s1, char *s2, char *s3);
int		add_env_var(t_minishell *data, t_env *new_lst, char *s1, char *s2);
void	init_null_env(t_minishell *minishell);
t_env	*new_env_list(t_minishell *minishell, char *name_str, char *value_str);
void	lstadd_back_env(t_env **lst, t_env *new);

#endif
