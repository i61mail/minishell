/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:28:00 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/01 11:31:40 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_vars *vars, t_env *envir, t_list *comm)
{
	char	*pwd;
	
	while (comm && comm->type != PIP)
		comm = comm->next;
	if (comm && comm->type == PIP)
	{
		ft_run(vars, comm, envir);
		return (0);
	}
	pwd = NULL;
	pwd = getcwd(pwd, PATH_MAX);
	if (!pwd)
		return (perror("getcwd"), errno);
	write(vars->pfd[1], pwd, ft_strlen(pwd));
	ft_putchar_fd('\n', vars->pfd[1]);
	return (0);
}

