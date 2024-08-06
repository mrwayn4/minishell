/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:14:32 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/30 19:14:24 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free(char **str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		free(str[i]);
	free(str);
}

int	ft_strncmp(char *s1, char *s2, int len)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < len)
		i++;
	return (s1[i] - s2[i]);
}

int	flag_check(char *s1)
{
	int	i;

	if (ft_strncmp(s1, "-n", 1))
		return (1);
	i = 2;
	while (s1[i])
	{
		if (s1[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}
