/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_prompt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:52:59 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/09 14:25:58 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"
#include "../../include/struct.h"

static void	init_prompt(t_prompt *prompt, char *usr);
static void	join_rl_prompt(char **rl_prompt, t_prompt prompt);

char	*get_prompt(t_data *data)
{
	t_env_node	*usr;
	t_prompt	prompt;
	char		*rl_prompt;

	ft_bzero(&prompt, sizeof(t_prompt));
	usr = ft_getenv(data->env, "USER");
	if (usr)
		init_prompt(&prompt, usr->val);
	else
		init_prompt(&prompt, "Undefined");
	join_rl_prompt(&rl_prompt, prompt);
	free_prompt(&prompt);
	return (rl_prompt);
}

static void	init_prompt(t_prompt *prompt, char *usr)
{
	prompt->prog = ft_strdup("minishell");
	prompt->usr = ft_strdup(usr);
	prompt->cwd = getcwd(NULL, 0);
}

static void	join_rl_prompt(char **rl_prompt, t_prompt prompt)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(BG_CYA, prompt.prog);
	tmp2 = ft_strjoin(tmp, NC);
	free(tmp);
	tmp = ft_strjoin(tmp2, BG_RED);
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
