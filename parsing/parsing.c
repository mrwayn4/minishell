/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:56:52 by ibouram           #+#    #+#             */
/*   Updated: 2024/08/04 15:50:48 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**merg_cmd(t_final	*lst)
{
	int		i;
	char	**full_cmd;

	i = 0;
	while ((lst)->args && ((lst))->args[i])
		i++;
	full_cmd = (char **) gv_coll (sizeof(char *) * (i + 2));
	full_cmd[0] = ft_strdup((lst)->cmd);
	i = 0;
	while ((lst)->args && (lst)->args[i])
	{
		full_cmd[i + 1] = ft_strdup((lst)->args[i]);
		i++;
	}
	full_cmd[i + 1] = NULL;
	return (full_cmd);
}

void	init_final_cmd(t_final ***lst)
{
	char	**str;
	t_final	*tmp;

	tmp = *(*lst);
	while (tmp)
	{
		str = merg_cmd(tmp);
		(tmp)->final_cmd = str;
		(tmp) = (tmp)->next;
	}
}

void	reset_quotes(t_token **token)
{
	t_token	*node;
	int		i;

	node = *token;
	while (node)
	{
		i = 0;
		while (node->token && node->token[i])
		{
			if (node->token[i] == -1)
				node->token[i] = '\'';
			else if (node->token[i] == -2)
				node->token[i] = '\"';
			i++;
		}
		node = node->next;
	}
}

int	parce_line(t_final **final_cmd, t_env *env, char *line)
{
	char	*tmp;
	t_token	*token;
	char	**split;

	(1) && (tmp = NULL, token = NULL, split = NULL);
	if (!check_quotes(line))
	{
		ft_putstr_fd("syntax error related to unclosed quote\n", 2);
		return (-1);
	}
	(1) && (tmp = line, line = trim_line(line));
	if (line == NULL)
		return (-1);
	line = space(line, 0, 0);
	split = split_line(line);
	if (tokenizer(split, &token, env))
	{
		exit_status(258, 1);
		return (-1);
	}
	(read_herdoc(token), token_quotes(&token));
	(1) && (reset_quotes(&token), *final_cmd = struct_init(&token));
	init_final_cmd(&final_cmd);
	return (1);
}

void	read_from_input(t_final *final_cmd, t_env **env_list, char **envp)
{
	int				r;
	struct termios	p;
	char			*line;

	(void)envp;
	tcgetattr(0, &p);
	tcsetattr(0, 0, &p);
	rl_catch_signals = 0;
	init_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line || !isatty(0))
			return (ft_putstr_fd("exit\n", 2), r = exit_status(1, 0), exit (r));
		if (!line[0])
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (parce_line(&final_cmd, *env_list, line) != -1)
			execution(final_cmd, env_list, &p);
		free(line);
	}
}
