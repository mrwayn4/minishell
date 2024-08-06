/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_helper2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:43:56 by zderfouf          #+#    #+#             */
/*   Updated: 2024/08/04 20:08:08 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	permission_checker(char *cmd)
{
	struct stat	p;

	if (access(cmd, F_OK) == 0
		&& access(cmd, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	stat(cmd, &p);
	if (S_ISDIR(p.st_mode))
	{
		if (ft_strcmp("..", cmd) && ft_strcmp(".", cmd))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": is a directory\n", 2);
			exit(126);
		}
	}
}

char	**join_cmd(char **cmd, char **args)
{
	char	**final_cmd;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (cmd[i])
		i++;
	while (args[k])
		k++;
	final_cmd = (char **) malloc(sizeof (char *) * (i + k + 1));
	(1) && (i = 0, k = 0);
	while (cmd[i])
	{
		final_cmd[i] = ft_strdup(cmd[i]);
		i++;
	}
	while (args[k])
	{
		final_cmd[i] = ft_strdup(args[k]);
		i++;
		k++;
	}
	return (final_cmd[i] = NULL, ft_free(cmd), final_cmd);
}

void	split_cmd(t_final **lst)
{
	char	**cmd;

	cmd = ft_split((*lst)->final_cmd[0], ' ');
	if (!cmd || !cmd[0])
		return (exit(0));
	if (!cmd[1])
		return (ft_free(cmd));
	else
	{
		cmd = join_cmd(cmd, &(*lst)->final_cmd[1]);
		ft_free((*lst)->final_cmd);
		(*lst)->final_cmd = cmd;
	}
}
