/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:12:52 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/16 17:06:03 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <fcntl.h>

# include "parse.h"

/* ================= ABSTRACT SYNTAX TREE(AST) EXECUTION =================== */
void		ast_depth_search(t_data *data, t_tree_node **node, int *i);
int			exec_ast_cmd(t_data *data, t_tree_node **node, int *i);

/* ============================= REDIRECTIONS ============================== */
int			redir_heredoc(t_data *data, t_word *word);
int			redir_in(t_word *word, t_data *data);
int			redir_out(t_data *data, t_word *word);
void		save_old_in_out(int *old_stdin, int *old_stdout);
void		reset_old_in_out(int old_stdin, int old_stdout);
void		redirect_stdout(int *fd, int i);
void		close_fd(int *fd, int count);

#endif