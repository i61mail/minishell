/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:19:54 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/28 20:06:40 by mait-lah         ###   ########.fr       */
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

void	dup_and_close(int oldfd, int newfd)
{
	if (oldfd == newfd)
		return ;
	dup2(oldfd, newfd);
	// if (oldfd != 0 && oldfd != 1)
	// 	close(oldfd);
}

int	ft_isalldots(char *str)
{
	while (str && *str)
	{
		if (*str != '.')
			return (0);
		str++;
	}
	return (1);
}

char	*ft_locate_bin(char *command, char *path)
{
	char	**_path;
	char	*temp;
	char	*temp1;
	char	*bin;
	int		i;

	i = 0;
	bin = NULL;
	if (!command || !(*command) || ft_isalldots(command))
		return (NULL);
	if (ft_strchr(command, '/'))
		return (command);
	_path = ft_split_char(path, ':');
	while (_path && _path[i])
	{
		temp = ft_strjoin(ft_strdup(_path[i]), "/");
		temp1 = ft_strjoin(temp, command);
		if (!access(temp1, X_OK | F_OK))
			bin = ft_strdup(temp1);
		free(temp1);
		i++;
	}
	ft_free_2d_array(&_path);
	return (bin);
}
