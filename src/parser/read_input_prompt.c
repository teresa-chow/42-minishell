/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_prompt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:52:59 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/02 12:07:29 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"
#include "../../include/struct.h"

static void	init_prompt(t_prompt *prompt, char *usr);
static void	join_rl_prompt(char **rl_prompt, t_prompt prompt);

char	*get_prompt(t_data *data)
{
	t_env_node	*tmp;
	t_prompt	prompt;
	char		*rl_prompt;

	tmp = data->env;
	ft_bzero(&prompt, sizeof(t_prompt));
	while (tmp) //TODO: see ft_getenv
	{
		if (!ft_strcmp(tmp->key, "USER"))
			init_prompt(&prompt, tmp->val);
		tmp = tmp->next;
	}
	if (!prompt.usr)
		init_prompt(&prompt, "Undefined");
	join_rl_prompt(&rl_prompt, prompt);
	free_prompt(&prompt);
	return (rl_prompt);
}

static void	init_prompt(t_prompt *prompt, char *usr)
{
	prompt->prog = ft_strdup("minishell");
	prompt->usr = ft_calloc(ft_strlen(usr) + 1, sizeof(char));
	prompt->cwd = getcwd(NULL, 0);
	if (!prompt->prog || !prompt->usr || !prompt->cwd)
		return ;
	prompt->usr = usr;
}

static void	join_rl_prompt(char **rl_prompt, t_prompt prompt)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(BG_CYA, prompt.prog);
	tmp2 = ft_strjoin(tmp, NC);
	free(tmp);
	tmp = ft_strjoin(tmp2, BG_MAG);
	free(tmp2);
	tmp2 = ft_strjoin(tmp, "☻ ");
	free(tmp);
	tmp = ft_strjoin(tmp2, prompt.usr);
	free(tmp2);
	tmp2 = ft_strjoin(tmp, NC);
	free(tmp);
	tmp = ft_strjoin(tmp2, BG_YEL);
	free(tmp2);
	tmp2 = ft_strjoin(tmp, "🖿 ");
	free(tmp);
	tmp = ft_strjoin(tmp2, prompt.cwd);
	free(tmp2);
	tmp2 = ft_strjoin(tmp, NC);
	*rl_prompt = ft_strjoin(tmp2, " ");
	free(tmp2);
}
