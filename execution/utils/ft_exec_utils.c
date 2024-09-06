/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:19:54 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/06 08:15:56 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env_length(t_env *envir)
{
	int	i;

	i = 0;
	while (envir)
	{
		envir = envir->next;
		i++;
	}
	return (i);
}

int	ft_comm_length(t_list *comm)
{
	int	i;

	i = 0;
	while (comm)
	{
		comm = comm->next;
		i++;
	}
	return (i);
}

int	ft_pipe_num(t_list *comm)
{
	int	n;

	n = 0;
	while (comm)
	{
		if (comm->type == PIP)
			n++;
		comm = comm->next;
	}
	return (n);
}

void	dup_and_close(int oldfd, int newfd)
{
	if(oldfd == newfd)
		return;
	dup2(oldfd, newfd);
	if (oldfd != 0 && oldfd != 1)
		close(oldfd);
}

char	*ft_locate_bin(char *command, char *path)
{
	char	**_path;
	char	*temp;
	char	*temp1;

	if (!command || !(*command))
		return (NULL);
	if (ft_strchr(command, '/'))
	{
		
		return (command);
	}	
	_path = ft_split(path, ':');
	while (_path && *_path)
	{
		temp = ft_strjoin(*_path, "/");
		temp1 = ft_strjoin(temp, ft_strdup(command));
		if (!access(temp1, X_OK | F_OK))
			return (temp1);
		_path++;
	}
	return (NULL);
}
