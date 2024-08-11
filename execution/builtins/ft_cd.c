/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:34:46 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/11 18:49:48 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd(t_vars *vars,t_list *comm,t_env *envir)
{
	(void)vars;
	(void)comm;
	(void)envir;
    //char *temp;

	//temp = getcwd(NULL, 0);
	//printf("%s\n",temp);
	if (comm && comm->next)
	{
		comm = comm->next;
		chdir(comm->content);
		printf("%s\n",comm->content);
	}	
	//temp = getcwd(NULL, 0);
	//printf("%s\n",temp);
	return (0);
}