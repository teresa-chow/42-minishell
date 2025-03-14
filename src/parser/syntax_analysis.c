/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:19:00 by tchow-so          #+#    #+#             */
/*   Updated: 2025/03/12 16:19:00 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"
#include "../../include/errors.h"

static int	check_first_word(t_word *word);
static int	check_op_syntax(char *word);

int	syntax_analysis(t_word_lst *word_lst)
{
	t_word_lst	*tmp_lst;
	t_word		*tmp_word;

	tmp_lst = word_lst;
	tmp_word = word_lst->word;
	if (check_first_word(tmp_word) != 0)
		return (ERR_BI);
	while (tmp_lst)
	{
		tmp_word = tmp_lst->word;
		while (tmp_word)
		{
			if (is_operator(tmp_word->word[0]) || is_redirection(tmp_word->word[0]))
			{
				if (check_op_syntax(tmp_word->word) != 0)
					return (ERR_BI);
			}
			tmp_word = tmp_word->next;
		}
		tmp_lst = tmp_lst->next;
	}
	return (0);
}

static int	check_first_word(t_word *word)
{
	char		token[3];

	if (is_operator(word->word[0]))
	{
		if (ft_strlen(word->word) == 1)
			return (err_syntax(&word->word[0]));
		else
		{
			token[0] = word->word[0];
			token[1] = word->word[1];
			token[2] = '\0';
			return (err_syntax(token));
		}
	}
	return (0);
}

/*static int	check_logical_op(t_word_lst *word_lst, t_word_lst *tmp_lst) //if first or next == NULL
{
	if (is_operator(tmp_lst->word->word[0]))
	{
		if (tmp_lst == word_lst)
		{
			tmp_lst->word->word;
		}
		if (tmp_lst->word->next == NULL)
	}
	return (0);
}*/
/* >&& token & ; >&&& token && ; >|| token | ; >||| token ||*/

static int	check_op_syntax(char *word) // if (is_operator())
{
	if (ft_strlen(word) > 2)
	{
		if (word[0] == '<')
			return (err_syntax("<"));
		else if (word[0] == '>')
			return (err_syntax(">"));
		else if (word[0] == '|')
			return (err_syntax("||"));
		else if (word[0] == '&')
			return (err_syntax("&&"));
	}
	return (0);
}

/* Operators in simple commands (not cmd groups) are always the first word in
a word list: check the first node of a word_lst, if is_operator strlen > 2 */

/*
If beginning of first command (word_lst->word->word) and no subsequent arg:
>, <, >>, << : syntax error near unexpected token `newline'
>>> : syntax error near unexpected token `>'
<<< (herestring) : token would be newline, but ms will handle as <

Redirection operators are ok in the beginning of a command,
as long as they have a following word
> followed by word will create a file
< will check if file exists or not

These cannot be in the beginning of a cmd at all times
& : syntax error near unexpected token `&'
&&, &&+ : syntax error near unexpected token `&&'

| : syntax error near unexpected token `|'
||, ||+ : syntax error near unexpected token `||'
*/


/*
&
[ ] Beginning of command -> token &

&&
[ ] Beginning of command -> token &&
[ ] Beginning of command &&+ -> token && (as well as with mixed ops &&>, &&|)
[ ] Middle of command &&& -> token &
[ ] Middle of command &&&+ -> token &&

|
[ ] Beginning of command -> token |

||
[ ] If beginning of command -> token = ||
[ ] Middle of command only ||| -> token = |
[ ] Middle of command |||+ -> token = ||

>>+
token >

<<< (herestring is valid in bash, but unhandled in minishell)
token <
*/