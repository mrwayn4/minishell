/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:44:58 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/31 00:26:41 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	trim_line_len(char *line)
{
	int	len;
	int	i;
	int	j;

	len = 0;
	i = 0;
	j = ft_strlen(line) - 1;
	while (line[i] && whitespaces(line[i]))
		i++;
	if (i == ft_strlen(line))
		return (0);
	while (j > 0 && whitespaces(line[j]))
		j--;
	len = j - i + 1;
	return (len);
}

char	*trim_line(char *line)
{
	int		i;
	int		j;
	char	*new_line;
	int		len;

	len = trim_line_len(line);
	if (len == 0)
		return (NULL);
	(1) && (i = 0, j = 0, new_line = NULL);
	new_line = gv_coll(len + 1);
	if (!new_line)
		return (NULL);
	while (line[i] && whitespaces(line[i]))
		i++;
	while (line[i] && j < len)
	{
		new_line[j] = line[i];
		i++;
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	ft_isnum(int n)
{
	if (n >= '0' && n <= '9')
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}
