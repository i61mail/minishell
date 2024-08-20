/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:23:32 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/20 15:11:33 by mait-lah         ###   ########.fr       */
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
	while (comm && comm->type != PIP)
	{
		_2dcomm[i] = comm->content;
		comm = comm->next;
		i++;
	}
	_2dcomm[i] = NULL;
	return (_2dcomm);
}

char	*ft_comm2str(t_list **comm)
{
	char		*str;
	t_list		*temp;
	int 		t;
	
	temp = (*comm);
	str = ft_strdup("");
	while (temp && temp->type != PIP)
	{
		t = temp->type;	
		//if (t == RED_IN || t == RED_OUT || t == RED_APPEND)
		//{
		//	ft_redirect();
		//	continue;
		//}
		str = ft_strjoin(str, " ");
		str = ft_strjoin(str, temp->content);
		temp = temp->next;
	}
	if (temp)
	{
		*comm = temp->next;
	}
	else
		*comm = NULL;
	return (str);
}
