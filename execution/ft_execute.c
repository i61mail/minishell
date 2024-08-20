/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: i61mail <i61mail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:15:40 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/20 23:18:08 by i61mail          ###   ########.fr       */
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
	while (comm && comm->type != PIP)
	{
		_2dcomm[i] = comm->content;
		comm = comm->next;
		i++;
	}
	_2dcomm[i] = NULL;
	return (_2dcomm);
}
char	*ft_comm2str(t_list **comm, int *fd)
{
	char *str;
	t_list *temp = (*comm);

	str = ft_strdup("");
	while(temp && temp->type != PIP)
	{
		//printf("%s\n",temp->content);
		str = ft_strjoin(str, " ");
		str = ft_strjoin(str, temp->content);	
		temp = temp->next;
	}
	if(temp)
	{
		*comm = temp->next;
	}
	else
	{
		(void)fd;
		//fd[0] = 0;
		//fd[1] = 1;
		*comm =NULL;
	}
	return (str);
}

char	*ft_locate_bin(char *command, char *path)
{
	char	**_path;
	char	*temp;
	char	*temp1;

	if(!command)
		return (NULL);
	//if given an absolute path or a absolue path
	if (ft_strchr(command, '/'))
		return(command);
	
	// if given a realative path to a command that does not exist in the current dir.
	_path = ft_split(path, ':');
	while (*_path)
	{
		temp = ft_strjoin(*_path, "/");
		temp1 = ft_strjoin(temp, ft_strdup(command));
		if (!access(temp1, X_OK | F_OK))
			return (temp1);
		_path++;
	}
	return (NULL);
}

void	ft_execute(t_vars *vars, t_list *comm, t_env *envir)
{
	char	*command;
	char	**_2dcomm;
	char	**_2denv;
	char 	*str_com;
	t_list 	*new_comm;
	int		id;
	static int		exit_status = 0;
	int		pfd[2];
	new_comm = comm;
	if (!comm)
		return ;
	pipe(pfd);
	while(comm)
	{
		str_com = ft_comm2str(&new_comm,pfd);
		if (comm && !ft_strncmp(comm->content, "echo\0", 5))
			ft_echo(comm);
		else if (comm && !ft_strncmp(comm->content, "cd\0", 3))
			ft_cd(vars, comm, envir);
		else if (comm && !ft_strncmp(comm->content, "pwd\0", 4))
			ft_pwd();
		else if (comm && !ft_strncmp(comm->content, "exit\0", 5))
			ft_exit(exit_status);
		else
		{
			id = fork();
			if(id == -1)
			{
				printf("minishell: fork: Resource temporarily unavailable\n");
				return ;
			}
			if (!id)
			{
				close(pfd[1]);
				command = ft_locate_bin(comm->content, getenv("PATH"));
				if (!command)
				{
					printf("minishell: %s: command not found\n", comm->content);
					exit(127);
				}
				comm->content = command;
				_2denv = ft_2denv(envir);
				_2dcomm = ft_2dcomm(comm);
				
				execve(_2dcomm[0], _2dcomm, (char *const *)_2denv);
				perror(comm->content);
			}
			else
			{
				close(pfd[0]);
				int	pid;
				wait(&pid);
				if(WIFEXITED(pid))
				{
					exit_status = WEXITSTATUS(pid);
					//printf("process exited with %d \n",exit_status);
				}
				close(pfd[1]);
				//free child leaks
			}
		}
		//printf("comm :%s\n", str_com);
		comm = new_comm;
	}
	}
