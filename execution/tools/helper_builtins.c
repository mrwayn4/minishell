/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:32:58 by zderfouf          #+#    #+#             */
/*   Updated: 2024/08/05 09:49:39 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	builtins_error(char *str, int flag)
{
	if (flag == 1337)
		write(2, "export: `", 9);
	else if (flag == 42)
		write(2, "unset: `", 9);
	ft_putstr_fd(str, 2);
	write(2, "': not a valide identifier\n", 27);
}

int	export_valid_check(char *str, char *arg, t_env ***env)
{
	int	i;

	i = 0;
	(void)env;
	if (!(ft_isalpha(str[0])))
		return (builtins_error(str, 1337), 0);
	while (str[++i])
	{
		if (i == (ft_strlen(str) - 1))
		{
			if (((ft_isalpha(str[i]) || str[i] == '+')
					&& !(str[i] >= '0' && str[i] <= '9')))
			{
				if (str[i] == '+')
					if (!ft_strchr(arg, '='))
						return (builtins_error(str, 1337), 0);
				continue ;
			}
		}
		if (!((ft_isalpha(str[i]) || (str[i] >= '0' && str[i] <= '9'))))
			return (builtins_error(str, 1337), 0);
	}
	return (1);
}

int	unset_valid_check(char *str, t_env ***env)
{
	int	i;

	i = 0;
	(void)env;
	if (!(ft_isalpha(str[0])))
		return (builtins_error(str, 42), 0);
	while (str[++i])
	{
		if (!((ft_isalpha(str[i]) || (str[i] >= '0' && str[i] <= '9'))))
			return (builtins_error(str, 42), 0);
	}
	return (1);
}

void	alpha_arrang(t_env *env)
{
	char	*temp;
	t_env	*tmp;

	tmp = env;
	while (tmp && tmp->next)
	{
		if (tmp->key[0] > tmp->next->key[0])
		{
			temp = tmp->key;
			tmp->key = tmp->next->key;
			tmp->next->key = temp;
			temp = tmp->value;
			tmp->value = tmp->next->value;
			tmp->next->value = temp;
			tmp = env;
		}
		else
			tmp = tmp->next;
	}
}

void	cd_error(char *dir)
{
	write(2, "cd: ", 4);
	ft_putstr_fd(dir, 2);
	write(2, ": No such file or directory\n", 28);
}
