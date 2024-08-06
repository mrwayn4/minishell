/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:30:14 by ibouram           #+#    #+#             */
/*   Updated: 2024/08/04 18:31:25 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_file_type(t_token **node, t_final **tmp, int *files_index)
{
	(*tmp)->files[*files_index].file = ft_strdup((*node)->token);
	if ((*node)->type == DELIMITER)
	{
		if ((*node)->flg == 1)
			(*tmp)->files[*files_index].flg = 1;
		else
			(*tmp)->files[*files_index].flg = 0;
	}
	(*tmp)->files[(*files_index)++].type = (*node)->type;
}

void	token_type(t_token **node, t_final **tmp, int *opt_index, int *fl_index)
{
	if (!node || !(*node) || !tmp || !(*tmp))
		return ;
	if ((*node)->type == CMD)
	{
		(*tmp)->cmd = ft_strdup((*node)->token);
		(*tmp)->var_flg = 0;
		if ((*node)->var_flg == 1)
			(*tmp)->var_flg = 1;
	}
	else if ((*node)->type == OPTION)
		(*tmp)->args[(*opt_index)++] = ft_strdup((*node)->token);
	else if ((*node)->type == IN_FILE || (*node)->type == OUT_FILE
		|| (*node)->type == AOUT_FILE || (*node)->type == DELIMITER)
		process_file_type(node, tmp, fl_index);
}

void	node_process(t_token **node, t_final **tmp, int *opt_indx, int *fl_indx)
{
	while (*node && (*node)->type != PIPE)
	{
		token_type(node, tmp, opt_indx, fl_indx);
		*node = (*node)->next;
	}
}

void	move_next_node(t_token **node)
{
	if ((*node)->type == PIPE)
		*node = (*node)->next;
}

t_final	*struct_init(t_token **token)
{
	t_token	*node;
	t_final	*final;
	t_final	*tmp;
	int		opt_index;
	int		files_index;

	(1) && (node = *token, final = NULL, files_index = -1);
	while (node)
	{
		if (node == *token || node->type == PIPE)
		{
			(1) && (opt_index = 0, files_index = 0);
			move_next_node(&node);
			tmp = init_final(&node);
			if (!tmp)
				return (NULL);
			node_process(&node, &tmp, &opt_index, &files_index);
			tmp->next = NULL;
			ft_lstadd_back3_parse(&final, tmp);
		}
		else
			node = node->next;
		post_process_files(&tmp, files_index);
	}
	return (final);
}
