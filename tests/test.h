/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:33:24 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/08 14:05:15 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "../include/builtins.h"
# include "../include/execve.h"
# include "../include/parse.h"
# include "../include/utils.h"

//void	test_builtins(t_data *data, t_word_lst **word_lst, int *i);
void	print_word_lst(char ** cmd_lst, t_word_lst **word_lst);

#endif