/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:49:01 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/24 14:49:01 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/execve.h"

/* Lexical analysis(1): command identification*/
/*int	is_builtin()
{

}*/

/*
! see quote removal
! see variable expansion
(case: export ARG="ls"; "$ARG" will execute ls normally, everything between
quotes will be a single word)

identify commands:
	ft_strcmp : if builtins --> builtins
	
	else :
		char	*get_path(char **envp);

		split exec dir :

		access :
		- F_OK (file exists)
		- X_OK (is executable)

	after checking all paths, either return is a directory or command not found

	how to handle expansions ??

	xxxnamexxx: command not found
	echo $? 127
 */
