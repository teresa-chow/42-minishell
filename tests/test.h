/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:33:24 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/11 10:33:24 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "../include/builtins.h"
# include "../include/execve.h"
# include "../include/parse.h"
# include "../include/utils.h"

void	test_builtins(t_word_lst *word_lst, t_env_node **env_lst);
void	print_word_lst(t_data *data, t_word_lst *word_lst);

#endif