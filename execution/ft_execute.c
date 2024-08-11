/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:15:40 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/11 18:29:58 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute(t_vars *vars,t_list *comm,t_env *envir)
{
	(void)vars;
	(void)comm;
	(void)envir;
	//t_list	*temp;
	//temp = comm;
	//while (temp)
	//{
	//	printf("%s      &&    %d\n", temp->content, temp->type);
	//	temp = temp->next;
	//}

	if (comm && !ft_strncmp(comm->content,"echo\0", 5))
		ft_echo(comm);
	else if (comm && !ft_strncmp(comm->content,"cd\0", 3))
		ft_cd(vars, comm, envir);
	else if (comm && !ft_strncmp(comm->content,"pwd\0", 4))
		ft_pwd();
	else
		printf("ERRORRR\n");
	
}