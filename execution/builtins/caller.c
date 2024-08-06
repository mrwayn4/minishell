/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caller.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:02:14 by zderfouf          #+#    #+#             */
/*   Updated: 2024/08/04 20:07:08 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	builtins(t_final *lst, t_env **env_list)
{
	if (!lst->final_cmd[0] || !lst->final_cmd[0][0])
		return (false);
	if (!ft_strncmp(lst->final_cmd[0], "echo", 4))
		return (echo(lst), (true));
	if (!ft_strncmp(lst->final_cmd[0], "cd", 2))
		return (cd(lst, *env_list), (true));
	if (!ft_strncmp(lst->final_cmd[0], "pwd", 3))
		return (pwd(), (true));
	if (!ft_strncmp(lst->final_cmd[0], "export", 6))
		return (export_command(lst, env_list), (true));
	if (!ft_strncmp(lst->final_cmd[0], "unset", 5))
		return (unset(lst, env_list), (true));
	if (!ft_strncmp(lst->final_cmd[0], "env", 3))
		return (env(*env_list), (true));
	if (!ft_strncmp(lst->final_cmd[0], "exit", 4))
		return (exit_command(lst->final_cmd), (true));
	return (false);
}
