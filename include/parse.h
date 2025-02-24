/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:49:05 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/15 21:49:05 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

/* The basic data structure the bash shell uses to pass information from one
stage to the next, and to operate on data units within each processing stage,
is the WORD_DESC */
typedef struct s_word_desc
{
	char	*word;
	int		flags;
}	t_word_desc;

/* A command is a word list, the result of expansion is a word list, and the
built-in commands each take a word list of argumenst */
typedef struct s_word_list
{
	struct s_word_list	*next;
	struct s_word_desc	*word;
	
}	t_world_list;

void	input_processing(char *input);

#endif
