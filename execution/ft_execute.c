/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:15:40 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/29 04:42:00 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_child(t_vars *vars, t_list *comm, t_env *envir)
{
	char	*binary;
	char	**_2denv;

	close(vars->pfd[0]);
	binary = ft_locate_bin(comm->content, getenv("PATH"));
	if (!binary)
	{
		close(vars->pfd[1]);
		close(vars->old_fd);
		printf("minishell: %s: command not found\n", comm->content);
		exit(errno);
	}
	if (vars->pipe)
		dup_and_close(vars->pfd[1], 1);
	dup_and_close(vars->old_fd, 0);
	comm->content = binary;
	_2denv = ft_2denv(envir);
	execve(binary, ft_2dcomm(comm), (char *const *)_2denv);
	perror(comm->content);
	vars->exit_status = errno;
	exit(vars->exit_status);
}

void	ft_parent(t_vars *vars, t_list *comm,t_env *envir)
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
		ft_exit(vars->exit_status, vars->numofpipes);
	else if (comm && !ft_strncmp(comm->content, "export\0", 7))
	{
		ft_export(envir, comm);
	}
	else if (comm && !ft_strncmp(comm->content, "unset\0", 7))
		ft_unset(comm,envir);
	//free child leaks
}
void	ft_handle_redir(t_list *node, t_list *next_node, t_vars *vars)
{
	(void)vars;
	if(!node || !next_node)
	{
		printf("i should'nt get here\n");
		return ;
	}
	if(node->type != PIP && node->type != RED_IN)
		vars->pipe = 0;
	if(node->type == RED_OUT)
	{
		int fd = open(next_node->content, O_WRONLY  | O_CREAT | O_TRUNC, 0644);
		if(fd == -1)
		{
			ft_putstr_fd("minishell: ",2);
			perror(next_node->content);
			vars->exit_status =  errno;
			exit(vars->exit_status);
		}
		dup_and_close(fd, 1);
	}
	if(node->type == RED_APPEND)
	{
		int fd = open(next_node->content, O_WRONLY  | O_CREAT | O_APPEND, 0644);
		if(fd == -1)
		{
			ft_putstr_fd("minishell: ",2);
			perror(next_node->content);
			vars->exit_status =  errno;
			exit(vars->exit_status);	
		}
		dup_and_close(fd, 1);
	}
	if(node->type == RED_IN)
	{
		int fd = open(next_node->content, O_RDONLY);
		if(fd == -1)
		{
			ft_putstr_fd("minishell: ",2);
			perror(next_node->content);
			vars->exit_status =  errno;
			exit(vars->exit_status);
		}
		dup_and_close(fd, 0);
	}
}
//char *ft_command(t_list *comm, t_vars *vars)
//{
//	char		*str;
//	t_list		*temp;

//	temp = comm;
//	str = ft_strdup("");
//	while (temp && temp->type != PIP)
//	{
//		if (temp != comm && !temp->type)
//			str = ft_strjoin(str, " ");
//		if (temp->type)
//		{
//			ft_handle_redir(temp, temp->next, vars);
//			temp = temp->next;
//			if(temp)
//				temp = temp->next;
//			continue;
//		}
//		str = ft_strjoin(str, temp->content);
//		temp = temp->next;
//	}
//	return (str);
//} to be deleted later

void	ft_exec_command(t_vars *vars, t_list *comm, t_env *envir)
{
	if (comm && !ft_strncmp(comm->content, "echo\0", 5))
		ft_echo(comm);
	else if (comm && !ft_strncmp(comm->content, "cd\0", 3))
		ft_cd(vars, comm, envir);
	else if (comm && !ft_strncmp(comm->content, "pwd\0", 4))
		ft_pwd();
	else if (comm && !ft_strncmp(comm->content, "export\0", 7))
		exit(5);
	else if (comm && !ft_strncmp(comm->content, "unset\0", 7))
		exit(5);
	else if (comm && !ft_strncmp(comm->content, "env\0", 7))
		ft_env(envir);
	else if (comm && ft_strncmp(comm->content, "exit\0", 5))
		ft_child(vars, comm, envir);
	//printf("%d\n", vars->exit_status);
	exit(vars->exit_status);
}

void	ft_run(t_vars *vars, t_list *comm, t_env *envir)
{
	int		id;
	t_list	*new_comm;

	new_comm = NULL;
	while (comm)
	{
		pipe(vars->pfd);
		new_comm = ft_split_pipe(&comm, vars);
		id = fork();
		if (id == -1)
		{
			ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
			return ;
		}
		if (!id)
			ft_exec_command(vars, comm, envir);
		else
			ft_parent(vars, comm, envir);
		comm = new_comm;
	}
}

void	ft_execute(t_vars *vars, t_list *comm, t_env *envir)
{
	vars->old_fd = 0;
	vars->numofpipes = ft_pipe_num(comm);
	
	if (!comm)
		return ;
	ft_run(vars, comm, envir);
	if (vars->old_fd != 0 && vars->old_fd != 1)
		close(vars->old_fd);
	vars->old_fd = 0;
}
