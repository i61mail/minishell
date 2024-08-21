/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:23:32 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/21 20:23:56 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_2denv(t_env *envir)
{
	char	**_2denv;
	char	*temp;
	char	*temp1;
	int		i;

	i = 0;
	_2denv = malloc(sizeof(char *) * (ft_env_length(envir) + 1));
	if (!_2denv)
		return (NULL);
	while (envir)
	{
		temp = ft_strjoin(ft_strdup(envir->key), "=");
		temp1 = ft_strjoin(temp, envir->value);
		_2denv[i] = temp1;
		envir = envir->next;
		i++;
	}
	_2denv[i] = NULL;
	return (_2denv);
}

char	**ft_2dcomm(t_list *comm)
{
	char	**_2dcomm;
	int		i;

	i = 0;
	_2dcomm = malloc(sizeof(char *) * (ft_comm_length(comm) + 1));
	if (!_2dcomm)
		return (NULL);
	while (comm)
	{
		_2dcomm[i] = comm->content;
		comm = comm->next;
		i++;
	}
	_2dcomm[i] = NULL;
	return (_2dcomm);
}

t_list	*ft_split_pipe(t_list **new_comm, t_vars *vars)
{
	t_list		*temp;

	temp = (*new_comm);
	while (temp && temp->type != PIP)
		temp = temp->next;
	if (temp)
	{
		vars->pipe = 1;
		return (temp->next);
	}
	else
	{
		vars->pipe = 0;
		return (NULL);
	}	
}
