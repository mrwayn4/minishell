/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 13:32:12 by zderfouf          #+#    #+#             */
/*   Updated: 2024/08/04 18:37:06 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sig_check(void)
{
	if (g_signal)
		return (g_signal = 0, (void) NULL);
}

void	waiter(t_final *lst, t_env **env)
{
	int	status;

	(void)env;
	if (waitpid(lst->pid, &status, 0) > 0)
	{
		if (WIFSIGNALED(status))
			exit_status(WTERMSIG(status) + 128, 1);
		else if (WIFEXITED(status))
			exit_status(WEXITSTATUS(status), 1);
		while (wait(NULL) != -1)
			;
	}
}

void	ft_help(int fds[2][2], t_final **lst, t_env **env)
{
	pipe_cmd(*lst, &fds[0][0], 2);
	if (!(*lst)->next)
		waiter(*lst, env);
	(*lst) = (*lst)->next;
}

void	init_secfds(int *sec_fd, int flag)
{
	if (flag == 0)
	{
		(1 == 1) && (sec_fd[0] = dup(0)) && (sec_fd[1] = dup(1));
		if (sec_fd[0] == -1 || sec_fd[1] == -1)
			error("dup", 1337);
	}
	else
	{
		if (dup2(sec_fd[0], 0) == -1 || dup2(sec_fd[1], 1) == -1)
			error("dup2", 1337);
		return ((void)close(sec_fd[0]), (void)close(sec_fd[1]));
	}
}

void	env_maker(t_env *envp, char ***env)
{
	int		i;
	char	*str;
	t_env	*tmp;

	(1 == 1) && ((tmp = envp) && (i = 0));
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	*env = (char **) gv_coll (sizeof(char *) * (i + 1));
	if (!*env)
		return ;
	(1 == 1) && ((tmp = envp) && (i = 0));
	while (tmp)
	{
		str = ft_strjoin(tmp->key, "=");
		(*env)[i] = ft_strjoin(str, tmp->value);
		free(str);
		tmp = tmp->next;
		i++;
	}
	(*env)[i] = NULL;
}
