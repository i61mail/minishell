/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:15:40 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/31 21:45:30 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_builtin(char *command)
{
	if (!ft_strcmp(command, "cd\0") || !ft_strcmp(command, "echo\0") || !ft_strcmp(command, "env\0") ||
		!ft_strcmp(command, "exit\0") || !ft_strcmp(command, "export\0") ||
		!ft_strcmp(command, "pwd\0") || !ft_strcmp(command, "unset\0"))
		return (1);
	return (0);
}

void	ft_child(t_vars *vars, t_list *comm, t_env *envir)
{
	char	*binary;
	char	**_2denv;

	dup_and_close(vars->pfd[1], 1);
	dup_and_close(vars->old_fd, 0);
	binary = ft_locate_bin(comm->content, getenv("PATH"));
	if (!binary)
	{
		close(vars->pfd[1]);
		close(vars->old_fd);
		printf("minishell: %s: command not found\n", comm->content);
		exit(errno);
	}
	comm->content = binary;
	_2denv = ft_2denv(envir);
	execve(binary, ft_2dcomm(comm), (char *const *)_2denv);
	perror(comm->content);
	vars->exit_status = errno;	
	exit(vars->exit_status);
}

void	ft_builtin(t_list *comm, t_env *envir, t_vars *vars)
{
	if (comm && !ft_strncmp(comm->content, "cd\0", 5))
		ft_cd(vars, comm, envir);
	else if (comm && !ft_strncmp(comm->content, "echo\0", 7))
		ft_echo(comm, vars);
	else if (comm && !ft_strncmp(comm->content, "env\0", 7))
		ft_env(envir, vars);
	else if (comm && !ft_strncmp(comm->content, "exit\0", 7))
		ft_exit(vars);
	else if (comm && !ft_strncmp(comm->content, "export\0", 7))
		ft_export(envir, vars, comm);
	else if (comm && !ft_strncmp(comm->content, "pwd\0", 7))
		ft_pwd(vars, envir);
	else if (comm && !ft_strncmp(comm->content, "unset\0", 7))
		ft_unset(comm, &envir);
	else if (vars->builtin)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(comm->content, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}
void	ft_parent(t_vars *vars, t_list *comm,t_env *envir)
{
	int	pid;
	wait(&pid);
	if (WIFEXITED(pid))
		vars->exit_status = WEXITSTATUS(pid);
	ft_builtin(comm, envir, vars);
	// free child leaks
}
void	ft_handle_redir(t_list *node, t_list *next_node, t_vars *vars)
{
	(void)vars;
	if(!node || !next_node)
	{
		printf("i should'nt get here\n");
		return ;
	}
	//if (next_node->type == AMBIGUOUS)
	//{
	//	printf("minishell: %s: ambiguous redirect", next_node->content);
	//	vars->exit_status =  errno;
	//	return ;
	//}
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

int		ft_isred(int	t)
{
	if (t == RED_IN || t == RED_OUT || t == RED_APPEND)
		return (1);
	return (0);
}
char *ft_check4red(t_list *comm, t_vars *vars)
{
	t_list		*temp;

	temp = comm;
	while (temp)
	{
		if (ft_isred(temp->type))
		{
			ft_handle_redir(temp, temp->next, vars);
			temp = temp->next;
			if(temp)
				temp = temp->next;
			continue;
		}
		temp = temp->next;
	}
	return (NULL);
}

void	ft_exec_command(t_vars *vars, t_list *comm, t_env *envir)
{
	
	if (ft_is_builtin(comm->content))
	{
		vars->builtin = 1;
		exit(vars->exit_status);
	}
	else
		ft_child(vars, comm, envir);
	exit(vars->exit_status);
}

void	ft_run(t_vars *vars, t_list *comm, t_env *envir)
{
	int		id;
	t_list	*new_comm;
	new_comm = NULL;
	int	_stdout = dup(1);
	int	_stdin =  dup(0);
	while (comm)
	{
		vars->pfd[0] = vars->old_fd;
		vars->pfd[1] = 1;
		new_comm = ft_split_pipe(&comm, vars);
		if (vars->pipe)
			pipe(vars->pfd);
		ft_check4red(comm, vars);
		id = fork();
		if (id == -1)
		{
			perror("minishell: fork:");
			return ;
		}
		if (!id)
			ft_exec_command(vars, comm, envir);
		else
			ft_parent(vars, comm, envir);
		if(vars->old_fd)
			close(vars->old_fd);
		vars->old_fd = vars->pfd[0];
		if (vars->pfd[1] != 1)
			close(vars->pfd[1]);
		comm = new_comm;
	}
	// restore stdin and stdout
	//close(vars->pfd[1]);
	//close(vars->pfd[0]);
	//close(vars->old_fd);
	dup_and_close(_stdout, 1);
	dup_and_close(_stdin, 0);
}

void	ft_execute(t_vars *vars, t_list *comm, t_env *envir)
{
	vars->numofpipes = ft_pipe_num(comm);
	vars->builtin = 0;
	vars->old_fd = 0;
	if (!comm)
		return ;
	ft_run(vars, comm, envir);
}

