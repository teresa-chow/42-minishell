/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:33:24 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/18 11:44:40 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "../include/builtins.h"
# include "../include/execve.h"
# include "../include/parse.h"
# include "../include/utils.h"

void	test_builtins(t_data *data, t_word_lst *word_lst);
void	print_word_lst(t_word_lst **word_lst);

#endif