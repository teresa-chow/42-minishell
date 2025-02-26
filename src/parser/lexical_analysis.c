/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:49:01 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/24 14:49:01 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

void	input_processing(char *input)
{
	lex_analysis(input);
	if (input && *input)
	{
		add_history(input);
		rl_on_new_line();
	}
}

// rl_redisplay(); -- when updating command line prompt (?)