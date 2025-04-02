/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:14:28 by carlaugu          #+#    #+#             */
/*   Updated: 2025/04/01 14:17:14 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/errors.h"
#include "../../include/special_cases.h"

int	get_exp_vars(char *arg, t_data *data)
{
	int	mid_len;
	char	*start;
	char	*end;

	mid_len = ft_strlen(arg) - (ft_strlen(data->exp->bfr) 
		+ ft_strlen(data->exp->aft) + ft_strlen(ft_strchr(arg, '"')));
	data->exp->mid = ft_calloc(mid_len + 1, sizeof(char));
	// if (!data->exp->mid)
	// 	return (free_exp());
	start = ft_strchr(arg, '$');
	end = ft_strchr(get_last_exp(arg), data->exp->no_alnum);
	ft_strlcpy(data->exp->mid, start, (end - start) + 1);
	return (0);
}

char	first_char(char *arg)
{
	while (*arg)
	{
		if (*arg != '"')
			break;
		arg++;
	}
	return (*arg);
}

int	check_bfr_aft_mid(char *arg, t_data *data)
{
	char	*lst_exp;
	int	i;
	char	c;
	
	if (*arg != '$')
	{
		if (*arg == '"')
		{
			c = first_char(arg);
			arg = ft_strchr(arg , c);
		}
		data->exp->bfr = ft_substr(arg , 0, ft_strlen(arg) - ft_strlen(ft_strchr(arg, '$')));
		// if (!data->exp->bfr)
		// 	return (free_exp());		
	}
	lst_exp = get_last_exp(arg);
	data->exp->no_alnum = find_no_alnum(lst_exp);
	if (data->exp->no_alnum)
	{
		i = ft_strlen(lst_exp) - ft_strlen(ft_strchr(lst_exp, data->exp->no_alnum));
		data->exp->aft = ft_substr(lst_exp, i, ft_strlen(ft_strchr(lst_exp, data->exp->no_alnum)) 
									- ft_strlen(ft_strchr(lst_exp, '"')));
		// if (!data->exp->aft)
		// 	return (free_exp());
	}
	if (get_exp_vars(arg, data) == -1)
		return(-1); // return (free_exp()); 
	return (0);
}

char	*get_name(char *s, t_data *data)
{
	char	c;
	int	len;

	if (data->exp->buf)
		free(data->exp->buf);
	if (data->exp->extra)
		free(data->exp->extra);
	data->exp->buf = NULL;
	data->exp->extra = NULL;
	c = find_no_alnum(s);
	if (!c)
		return (s);
	if (c)
	{
		len = ft_strlen(s) - ft_strlen(ft_strchr(s, c));
		data->exp->buf = ft_calloc(len + 1, sizeof(char));
		// if (!data->exp->buf)
		ft_strlcpy(data->exp->buf, s, len + 1);
		len = ft_strlen(ft_strchr(s, c));
		data->exp->extra = ft_calloc(len + 1, sizeof(char));
		// if (!data->exp->buf)
		ft_strlcpy(data->exp->extra, ft_strchr(s, c), len + 1);
	}
	return (data->exp->buf);
}

int	expand_vars(t_data *data)
{
	char	*tmp;
	char	*name;
	t_env_node	*var;
	int	i;

	data->exp->arr = ft_split(data->exp->mid, '$');
	// if (!data->exp->wrds)
	// 	return (free_exp())
	i = -1;
	tmp = NULL;
	free(data->exp->mid);
	data->exp->mid = NULL;
	while (data->exp->arr[++i])
	{
		name = get_name(data->exp->arr[i], data);
		// if (!name)
		var = ft_getenv(data->env, name); //////////////////
		if (var && var->val)
		{
			if (data->exp->mid)
			{
				tmp = data->exp->mid;
				data->exp->mid = ft_strjoin(data->exp->mid, var->val);
				free(tmp);
			}
			else
				data->exp->mid = ft_strdup(var->val);
			// if (!data->exp->mid)
				// return (free_exp())
		}
		if (data->exp->extra)
		{
			if (data->exp->mid)
			{
				tmp = data->exp->mid;
				data->exp->mid = ft_strjoin(data->exp->mid, data->exp->extra);
				free(tmp);
			}
			else
				data->exp->mid = ft_strdup(data->exp->extra);
			// if (!data->exp->mid)
				//return (freE_exp())
		}
	}
	return (0);
}

int	count_quotes(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != '"')
			break;
	}
	return (i);
}
int	has_delimiter(char *arg)
{
	if (!arg)
		return (0);
	while (*arg)
	{
		if (is_delimiter(*arg))
		{
			if ((*arg == ' ' && (is_delimiter(*(arg + 1)))) || *arg != ' ')
				return (1);
		}
		arg++;
	}
	return (0);
}

char	*join_three(char *s1, char *s2, char *s3)
{
	size_t	len;
	char	*dst;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, ft_strlen(s1) + 1);
	ft_strlcat(dst, s2, len + 1);
	ft_strlcat(dst, s3, len + 1);
	return (dst);
}
int	handle_quotes(char *arg, t_data *data)
{
	int	n;
	int	i;
	char	*to_free;

	i = 0;
	n = count_quotes(arg);
	if (n & 1)
		return (0);
	if (has_delimiter(data->exp->mid))
	{
		to_free = data->exp->mid;
		data->exp->words = get_words(data->exp->mid);
		if (!data->exp->words)
			return (-1);// 	return (free_exp());
		data->exp->mid = data->exp->words[0];
		while (data->exp->words[++i])
		{
			data->exp->mid = join_three(data->exp->mid, " ", data->exp->words[i]);
			// if (!data->exp->mid)
			// 	return (free_exp())
			if (to_free)
				free(to_free);
			to_free = data->exp->mid;
		}
	}
	return (0);
}
// bfr mid aft
// bft mid
// bfr aft

// aft mid
//
//
int	join_words(t_data *data, t_word *word)
{
	free(word->word);
	if (data->exp->bfr && data->exp->aft && data->exp->mid)
		word->word = join_three(data->exp->bfr, data->exp->mid, data->exp->aft);
	else if (!data->exp->mid && (data->exp->bfr || data->exp->aft))
		word->word = ft_strjoin(data->exp->bfr, data->exp->aft);
	else if (data->exp->bfr && !data->exp->aft)
		word->word = ft_strjoin(data->exp->bfr, data->exp->mid);
	else if (data->exp->aft && !data->exp->bfr)
		word->word = ft_strjoin(data->exp->mid, data->exp->aft);
	else
		word->word = ft_substr(data->exp->mid, 0, ft_strlen(data->exp->mid) + 1);
	// if (!word->word)
		// return (free_exp())
	return (0);
}

int	expand(t_data *data, t_word *word)
{
// /////////////////////////////////////////////////////////////////	
// 		/////    TESTE    ///////
// 	t_env_node	*var;
// 	t_env_node	*var1;

// 	var = ft_getenv(data->env, "ZZ");
// 	var->val = "Carlos		  Teixeira";
// 	var1 = ft_getenv(data->env, "ZA");
// 	var1->val = "Ana	Silva";
// 	word->word = ft_strdup("ola..?$ZZ..??$ZA...");
// 	// word->word = "\"\"ola..$ZZ..$ZA?\"\"";

// 		/////    TESTE    ///////
// //////////////////////////////////////////////////////////////////
	data->exp = ft_calloc(sizeof(t_expand), sizeof(char));
	if (!data->exp)
		return (error_allocation(data));
	if (check_bfr_aft_mid(word->word, data) == -1)
		return (-1);
	if (expand_vars(data) == -1)
		return (-1);
	if (handle_quotes(word->word, data) == -1)
		return (-1);
	if (join_words(data, word) == -1)
		return (-1);
	return (0);
}
