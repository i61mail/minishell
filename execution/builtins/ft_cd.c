/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:34:46 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/04 18:52:55 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd(t_vars *vars, t_list *comm, t_env *envir)
{
	(void)vars;
	(void)comm;
	(void)envir;
	if(vars->numofpipes)
		return (0);
	if (comm && comm->next)
	{
		comm = comm->next;
		if (chdir(comm->content))
			printf("minishell: cd: %s: No such file or directory\n", comm->content);
	}
	return (0);
}
