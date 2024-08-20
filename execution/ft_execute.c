/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:15:40 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/20 14:27:33 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_child(t_vars *vars, t_list *comm, t_env *envir)
{
	char	*command;
	char	**_2dcomm;
	char	**_2denv;

	close(vars->pfd[0]);
	command = ft_locate_bin(comm->content, getenv("PATH"));
	if (!command)
	{
		close(vars->pfd[1]);
		close(vars->old_fd);
		printf("minishell: %s: command not found\n", comm->content);
		exit(127);
	}
	if (vars->i < vars->v)
		dup_and_close(vars->pfd[1], 1);
	if (vars->i > 0)
		dup_and_close(vars->old_fd, 0);
	comm->content = command;
	_2denv = ft_2denv(envir);
	_2dcomm = ft_2dcomm(comm);
	execve(_2dcomm[0], _2dcomm, (char *const *)_2denv);
	perror(comm->content);
	exit(errno);
}

void	ft_parent(t_vars *vars, t_list *comm)
{
	int	pid;

	close(vars->pfd[1]);
	if (vars->old_fd != 0 && vars->old_fd != 1)
		close(vars->old_fd);
	vars->old_fd = vars->pfd[0];
	wait(&pid);
	if (WIFEXITED(pid))
		vars->exit_status = WEXITSTATUS(pid);
	if (comm && !ft_strncmp(comm->content, "exit\0", 5))
		ft_exit(vars->exit_status, (vars->v > 0));
	//free child leaks
}

void	ft_exec_command(t_vars *vars, t_list *comm, t_env *envir)
{
	if (comm && !ft_strncmp(comm->content, "echo\0", 5))
		ft_echo(comm);
	else if (comm && !ft_strncmp(comm->content, "cd\0", 3))
		ft_cd(vars, comm, envir);
	else if (comm && !ft_strncmp(comm->content, "pwd\0", 4))
		ft_pwd();
	else if (comm && ft_strncmp(comm->content, "exit\0", 5))
		ft_child(vars, comm, envir);
	exit(127);
}

void	ft_run(t_vars *vars, t_list *comm, t_env *envir)
{
	int		id;
	t_list	*new_comm;

	new_comm = comm;
	while (comm)
	{
		pipe(vars->pfd);
		id = fork();
		if (id == -1)
		{
			ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n",2);
			return ;
		}
		ft_comm2str(&new_comm);
		if (!id)
			ft_exec_command(vars, comm, envir);
		else
			ft_parent(vars, comm);
		comm = new_comm;
		vars->i++;
	}
}

void	ft_execute(t_vars *vars, t_list *comm, t_env *envir)
{
	if (!comm)
		return ;
	vars->i = 0;
	vars->v = ft_pipe_num(comm);
	ft_run(vars, comm, envir);
	if (vars->old_fd != 0 && vars->old_fd != 1)
		close(vars->old_fd);
	vars->old_fd = 0;
}
