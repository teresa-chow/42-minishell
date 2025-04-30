/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:12:52 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/30 16:18:38 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

# include "parse.h"

typedef struct s_pipeline
{
	t_tree_node				*cmd_lst;
	int						n_pipes;
	int						**fd;
	pid_t					*pid;
}	t_pipeline;

/* ================= ABSTRACT SYNTAX TREE(AST) EXECUTION =================== */
void		ast_depth_search(t_data *data, t_tree_node **node, bool pipeline);
int			exec_ast(t_data *data, t_tree_node **node, bool pipeline);
int			exec_ast_cmd(t_data *data, t_tree_node **node, bool pipeline);
void		exec_builtin_cmd(t_data *data, t_word *word);
void		exec_child(t_data *data, t_word *word, bool pipeline);
void		set_exit_status(int *status, t_data *data);

/* ============================== PIPELINE ================================= */
void		ast_handle_pipeline(t_data *data, t_tree_node **node);
void		traverse_pipeline(t_data *data, t_pipeline *pipeline,
				t_tree_node **node);
void		exec_pipeline_child(t_pipeline pipeline, t_data *data,
				t_tree_node *node, int count);

/* =============================== SIGNALS ================================= */
void		set_signals(t_data *data);
void 		handle_signal(int i);

/* ============================= REDIRECTIONS ============================== */
// Heredoc
int			redir_heredoc(t_data *data, t_word *word);
int			build_heredoc_wrd(t_word **doc_word, char *input, t_data *data);
void		print_to_pipe(t_word *doc_word, int *fd);
int	        verify_quotes(char **eof, bool *quotes, t_data *data);
// Input and Output redirection
int 		redir_in_out_check(t_word *word, t_data *data);
int			redir_in(t_word *word, t_data *data);
int			redir_out(t_data *data, t_word *word);
void		save_old_in_out(int *old_stdin, int *old_stdout);
void		reset_old_in_out(int old_stdin, int old_stdout);
void		redirect_stdout(int *fd, int i);
void		close_fd(int *fd, int count);

/* ================================ UTILS ================================== */
int			is_builtin_cmd(t_word *word);
int			cd_arg_check(t_word *word, t_data *data);

#endif