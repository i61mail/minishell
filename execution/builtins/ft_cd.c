/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:34:46 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/01 10:54:48 by isrkik           ###   ########.fr       */
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
			ft_run(vars, comm, envir);
			return (0);
		}
		if (chdir(temp->content))
			printf("minishell: cd: %s: No such file or directory\n", comm->content);
	}
	return (0);
}
