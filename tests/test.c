/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:00:39 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/03 14:21:32 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "../include/expand.h"
#include "../include/errors.h"

int	is_valid_dollar(char *s)
{
	if (*(s + 1) == '?' || ft_isalnum(*(s + 1)))
		return (1);
	return (0);
}

void	check_special_char(char *s, t_data *data)
{
	while (*s)
	{
		if (*s == '\'')
			data->exp->has_sing++;
		else if (*s == '"')
			data->exp->has_dbl++;
		else if (*s == '$' && is_valid_dollar(s))
			data->exp->has_exp++;
		s++;
	}
}

int	exit_status_len(t_data *data)
{
	int	i;

	i = 0;
	if (!data->exit_status)
		return (1);
	while (data->exit_status)
	{
		i++;
		data->exit_status /= 10;
	}
	return (i);
}

char	*find_inval(char *s)
{
	while (*s)
	{
		if (!ft_isalnum(*s))
			break;
		s++;
	}
	return (s);
}

int	var_val_len(char *s, t_data *data, char **bgn)
{
	t_env_node	*var;
	char	*inval_char;
	char	box;
	int	len;

	len = 0;
	inval_char = find_inval(s);
	box = *inval_char;
	*inval_char = 0;
	var = ft_getenv(data->env, s);
	if (var)
		len = ft_strlen(var->val);
	*inval_char = box;
	*bgn = inval_char;
	return (len);
}

int	get_len(char *bgn, char *end, int to_exp, t_data *data)
{
	int	len;

	if (!to_exp)
		return (end - bgn);
	len = 0;
	while (bgn != end)
	{
		if (*bgn == '$' && is_valid_dollar(bgn))
		{
			if (*(bgn + 1) == '?')
			{
				len += exit_status_len(data);
				bgn += 2;
			}
			else
				len += var_val_len(bgn + 1, data, &bgn);
		}
		else
		{
			len++;
			bgn++;
		}
	}
	return (len);
}

char	*get_next_qt(char *s, t_data *data)
{
	while (*s)
	{
		if (*s == '\'' && data->exp->in_sing)
			break;
		if (*s == '"' && data->exp->in_dbl)
			break;
		s++;
	}
	return (s);
}

void	update_quotes_status(char *ptr, t_data *data, bool *to_exp)
{
	if (*ptr == '\'')
	{
		data->exp->in_sing = !data->exp->in_sing;
		*to_exp =false;
	}
	else if (*ptr == '"')
	{
		data->exp->in_dbl = !data->exp->in_dbl;
		if (data->exp->in_dbl)
			*to_exp = true;
		else
			*to_exp = false;
	}
}

int	fill_with_sing_quotes(t_data *data, char *bgn, char *end, int len)
{
	int	total;
	char	*to_free;

	if (!data->exp->new)
	{
		data->exp->new = ft_calloc(len + 1, sizeof(char));
		if (!data->exp->new)
			return (-1);
		add_chars(bgn, end, data->exp->new);
	}
	else
	{
		total = ft_strlen(data->exp->new) + len + 1;
		to_free = data->exp->new;
		data->exp->new = ft_calloc(total, sizeof(char));
		if (!data->exp->new)
			return (-1);
		ft_strlcpy(data->exp->new, to_free, total);
		add_chars(bgn, end, ft_strchr(data->exp->new, 0));
		free(to_free);
	}
	return (0);
}

// int	fill_with_dbl_quotes()
// {

// }

int	handle_exp_qts(char **ptr, t_data *data)
{
	bool	to_exp;
	int	i;
	int	len;
	char	*end;

	update_quotes_status(*ptr, data, &to_exp);
	end = get_next_qt(*ptr + 1, data);
	len = get_len(*ptr + 1, end, to_exp, data);
	if (!to_exp)
		i = fill_with_sing_quotes(data, *ptr + 1, end, len);
	// else
	// 	 i = fill_with_dbl_quotes();
	if (i == -1)
		return (-1);
	update_quotes_status(end, data, &to_exp);
	*ptr = end + 1; ///// this is equal to others ---handle_normal();
	return (0);
}

int	handle_arg(t_word *word, t_data *data)
{
	char	*ptr;
	int	i;

	ptr = word->word;
	while (*ptr)
	{
		if (*ptr == '\'' || *ptr == '"')
			i = handle_exp_qts(&ptr, data);
		// else
		// 	handle_normal();
		if (i == -1)
			return (-1);
	}
	return (0);
}

int	analyze_args(t_word *word, t_data *data)
{
	data->exp = ft_calloc(sizeof(t_expand), sizeof(char));
	if (!data->exp)
		return (error_allocation(data));
	while (word)
	{
		check_special_char(word->word, data);
		if (data->exp->has_dbl || data->exp->has_sing || data->exp->has_exp)
		{
			if (handle_arg(word, data) == -1)
				return (-1);// return(free_exp);
		}
		word = word->next;
	}
	return (0);
}

/*****************************************************************************\
|                            BUILTINS TEST FUNCTIONS                          |
\*****************************************************************************/

void	test_builtins(t_data *data, t_word_lst **word_lst, int *i)
{ /// has pelicas???????
   	if (ft_strcmp((*word_lst)->word->word, "echo") == 0)
	{
		(*word_lst)->word->next->word = ft_strdup("\'ola\'\"TESTEE\"$HOME\'");
		if (analyze_args((*word_lst)->word->next, data) == -1)
			return ;
		echo((*word_lst)->word, data);
	}
	else if (ft_strcmp((*word_lst)->word->word, "cd") == 0)
	{
		if ((*word_lst)->word->next && (*word_lst)->word->next->next)
		{
				cd_error(NULL, data, 0);
				return ;
		}
		cd((*word_lst)->word, data);
	}
	else if (ft_strcmp((*word_lst)->word->word, "pwd") == 0)
		pwd(data);	
	else if (ft_strcmp((*word_lst)->word->word ,"export") == 0)
		export(data, (*word_lst)->word);
	else if (ft_strcmp((*word_lst)->word->word,"unset") == 0)
		unset(data, (*word_lst)->word->next);
	else if (ft_strcmp((*word_lst)->word->word,"env") == 0)
		env_cmd(data->env, data);
	else if (!ft_strcmp((*word_lst)->word->word, "exit"))
		check_exit_args(data, word_lst, i); /// in the future, the argument is the tree and then
							    /// we have to free the tree
	else
		exec(data, (*word_lst)->word);
}
/*****************************************************************************\
|                             PARSER TEST FUNCTIONS                           |
\*****************************************************************************/
void	print_word_lst(char **cmd_lst, t_word_lst **word_lst)
{
	int			i = 0;
	int			cmd_n = 0;
	t_word		*word_ptr;
	t_word_lst	*lst_ptr;

	lst_ptr = *word_lst;
	word_ptr = (*word_lst)->word;
	if (cmd_lst == NULL)
		return ;
	ft_printf("--------------------------------------\n");
	while (cmd_lst[i])
	{
		ft_printf("cmd: %s\n", cmd_lst[i]);
		i++;
	}
	ft_printf("--------------------------------------\n");
	while (lst_ptr)
	{
		ft_printf("## cmd no.: %d\n", cmd_n);
		word_ptr = lst_ptr->word;
		while (word_ptr)
		{
			ft_printf("word: %s\n", word_ptr->word);
			word_ptr = word_ptr->next;
		}
		lst_ptr = lst_ptr->next;
		cmd_n++;
		ft_printf("------------------\n");
	}
	ft_printf("\n\n--------------------------------------\n");
}