/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:08:46 by isrkik            #+#    #+#             */
/*   Updated: 2024/10/01 22:12:07 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handle_redir(t_list *node, t_list *next_node, t_vars *vars)
{
	if (!node || !next_node)
		return (-1);
	if (next_node->type == AMBIGUOUS)
		return (ft_ambiguos(next_node, vars), -1);
	if (node->type != PIP && node->type != RED_IN)
		vars->pipe = 0;
	if (node->type == RED_OUT)
	{
		if (ft_redout(next_node, vars) == -1)
			return (-1);
	}
	if (node->type == RED_APPEND)
	{
		if (ft_redappend(next_node, vars) == -1)
			return (-1);
	}
	if (node->type == RED_IN)
	{
		if (ft_redin(next_node, vars) == -1)
			return (-1);
	}
	if (node->type == HEREDOC)
		return (ft_redheredoc(next_node, vars));
	return (0);
}
