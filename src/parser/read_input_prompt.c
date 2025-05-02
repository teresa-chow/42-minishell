/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_prompt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:52:59 by tchow-so          #+#    #+#             */
/*   Updated: 2025/04/30 23:27:36 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"
#include "../../include/struct.h"

static void	init_prompt(t_prompt *prompt, char *usr, t_data *data); /// add data
static void	join_rl_prompt(char **rl_prompt, t_prompt prompt, bool env);
static void	join_color(char **rl_prompt, t_prompt prompt);
static void	join_white(char **rl_prompt, t_prompt prompt);

char	*get_prompt(t_data *data, bool env)
{
	t_env_node	*usr;
	t_prompt	prompt;
	char		*rl_prompt;

	ft_bzero(&prompt, sizeof(t_prompt));
	usr = ft_getenv(data->env, "USER");
	if (usr)
		init_prompt(&prompt, usr->val, data);
	else
		init_prompt(&prompt, "Undefined", data);
	join_rl_prompt(&rl_prompt, prompt, env);
	free_prompt(&prompt);
	return (rl_prompt);
}

static void	init_prompt(t_prompt *prompt, char *usr, t_data *data)
{
	char	*cwd;
	char	*dir;
	t_env_node *pwd;

	pwd = ft_getenv(data->env, "PWD"); /// add this to when we delete a folder, when in it
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		if (pwd && pwd->val)
			dir = ft_strdup(pwd->val); //// add
		else
			dir = ft_strdup("/Undefined"); //// add
	}
	else
		dir = ft_strdup(ft_strrchr(cwd, '/'));
	prompt->prog = ft_strdup("minishell");
	prompt->usr = ft_strdup(usr);
	if (ft_strcmp(dir, "/"))
		prompt->cwd = ft_strjoin("~", dir);
	else
		prompt->cwd = ft_strdup(dir);
	free(cwd);
	free(dir);
}

static void	join_rl_prompt(char **rl_prompt, t_prompt prompt, bool env)
{
	if (env)
		join_color(rl_prompt, prompt);
	else
		join_white(rl_prompt, prompt);
}

static void	join_color(char **rl_prompt, t_prompt prompt)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("\001"BG_CYA"\002", prompt.prog);
	tmp2 = ft_strjoin(tmp, "\001"NC"\002");
	free(tmp);
	tmp = ft_strjoin(tmp2, "\001"BG_RED"\002");
	free(tmp2);
	tmp2 = ft_strjoin(tmp, "☻ ");
	free(tmp);
	tmp = ft_strjoin(tmp2, prompt.usr);
	free(tmp2);
	tmp2 = ft_strjoin(tmp, "\001"NC"\002");
	free(tmp);
	tmp = ft_strjoin(tmp2, "\001"BG_YEL"\002");
	free(tmp2);
	tmp2 = ft_strjoin(tmp, "🖿  ");
	free(tmp);
	tmp = ft_strjoin(tmp2, prompt.cwd);
	free(tmp2);
	tmp2 = ft_strjoin(tmp, "\001"NC"\002");
	free(tmp);
	*rl_prompt = ft_strjoin(tmp2, " ");
	free(tmp2);
}

static void	join_white(char **rl_prompt, t_prompt prompt)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(prompt.prog, " ➔ ☻ ");
	tmp2 = ft_strjoin(tmp, prompt.usr);
	free(tmp);
	tmp = ft_strjoin(tmp2, " ➔ 🖿  ");
	free(tmp2);
	tmp2 = ft_strjoin(tmp, prompt.cwd);
	free(tmp);
	*rl_prompt = ft_strjoin(tmp2, " • ");
	free(tmp2);
}
