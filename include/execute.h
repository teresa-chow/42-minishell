/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:12:52 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/27 18:31:23 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <fcntl.h>

# include "parse.h"

typedef struct s_pipeline
{
	t_word_lst				*cmd_lst;
	int						n_pipes;
	int						**fd;
	pid_t					*pid;
}	t_pipeline;

/* ================= ABSTRACT SYNTAX TREE(AST) EXECUTION =================== */
void		ast_depth_search(t_data *data, t_tree_node **node);
int			exec_ast_cmd(t_data *data, t_tree_node **node);
void		exec_builtin_cmd(t_data *data, t_word *word);
void		exec_child(t_data *data, t_word *word);

/* ============================== PIPELINE ================================= */
void		ast_handle_pipeline(t_data *data, t_tree_node **node);
void		traverse_pipeline(t_data *data, t_pipeline *pipeline,
				t_tree_node **node);
void		exec_pipeline_child(t_pipeline pipeline, t_data *data,
				t_word *word, int count);

/* ============================= REDIRECTIONS ============================== */
int			redir_heredoc(t_data *data, t_word *word);
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