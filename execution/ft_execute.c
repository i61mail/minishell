/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:15:40 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/13 17:40:34 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*ft_locate_bin(char *command, char *path)
{
	char	**_path;
	char	*temp;
	char	*temp1;

	_path = ft_split(path, ':');
	while (*_path)
	{
		temp = ft_strjoin(*_path, "/");
		temp1 = ft_strjoin(temp, ft_strdup(command));
		if (!access(temp1, EACCES))
			return (free(command), temp1);
		_path++;
	}
	return (NULL);
}

void	ft_execute(t_vars *vars, t_list *comm, t_env *envir)
{
	char	*command;
	char	**_2dcomm;
	char	**_2denv;
	int		id;

	if (!comm)
		return ;
	if (comm && !ft_strncmp(comm->content, "echo\0", 5))
		ft_echo(comm);
	else if (comm && !ft_strncmp(comm->content, "cd\0", 3))
		ft_cd(vars, comm, envir);
	else if (comm && !ft_strncmp(comm->content, "pwd\0", 4))
		ft_pwd();
	else if (comm && !ft_strncmp(comm->content, "exit\0", 5))
		ft_exit(comm);
	else
	{
		id = fork();
		if (!id)
		{
			command = ft_locate_bin(comm->content, getenv("PATH"));
			comm->content = command;
			_2denv = ft_2denv(envir);
			_2dcomm = ft_2dcomm(comm);
			execve(_2dcomm[0], _2dcomm, (char *const *)_2denv);
			perror(comm->content);
		}
		else
		{
			waitpid(id, NULL, 0);
		}
	}
}
