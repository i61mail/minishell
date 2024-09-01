/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:34:46 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/01 01:12:44 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd(t_vars *vars, t_list *comm, t_env *envir)
{
	(void)vars;
	(void)comm;
	(void)envir;
	if (comm && comm->next)
	{
		comm = comm->next;
		if (chdir(comm->content))
			printf("minishell: cd: %s: No such file or directory\n", comm->content);
	}
	return (0);
}
