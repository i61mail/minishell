/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:34:46 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/04 11:54:37 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd(t_vars *vars, t_list *comm, t_env *envir)
{
	(void)vars;
	t_list *temp;

	temp = comm;
	if (temp && temp->next)
	{
		temp = temp->next;
		while (comm && comm->type != PIP)
			comm = comm->next;
		if (comm && comm->type == PIP)
		{
			ft_run(vars, temp, envir);
			return (0);
		}
		if (chdir(temp->content))
			printf("minishell: cd: %s: No such file or directory\n", temp->content);
		if (vars->not_red == 0 || (vars->not_enter == 1 && vars->red_built == 1))
		{
			dup2(1, vars->fd_buil);
		}
		else if (vars->red_built == 1 && vars->numofpipes > 0)
		{
			dup2(vars->pfd[1], vars->fd_buil);
		}
	}
	return (0);
}
//needs to function with all possibilities