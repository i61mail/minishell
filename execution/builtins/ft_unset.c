/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 03:58:14 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/04 11:54:04 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_list *command, t_env **envir, t_vars *vars)
{
	t_env *temp;
	t_env *prev;
	t_env *to_free;
	t_list *comm;

	comm = command;
	while (comm && comm->type != PIP)
		comm = comm->next;
	if (comm && comm->type == PIP)
	{
		ft_run(vars, command, *envir);
		return ;
	}
	if (vars->not_red == 0 || (vars->not_enter == 1 && vars->red_built == 1))
	{
		dup2(1, vars->fd_buil);
	}
	else if (vars->red_built == 1 && vars->numofpipes > 0)
	{
		dup2(vars->pfd[1], vars->fd_buil);
	}
	command = command->next;
	while (command)
	{
		temp = *envir;
		prev = NULL;
		while (temp)
		{
			if (!ft_strcmp(command->content, temp->key))
			{
				if (!prev)
				{
					*envir = temp->next;
					to_free = temp;
				}
				else
				{
					to_free = temp;
					prev->next = temp->next;
				}
				free(to_free->value);
				free(to_free->key);
				free(to_free);
				break;
			}
			prev = temp;
			temp = temp->next;
		}
		command = command->next;
	}
}

