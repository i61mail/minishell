/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:15:40 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/05 07:01:56 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_is_builtin(char *command)
{
	if (!ft_strcmp(command, "cd\0") || !ft_strcmp(command, "echo\0") || !ft_strcmp(command, "env\0") ||
		!ft_strcmp(command, "exit\0") || !ft_strcmp(command, "export\0") ||
		!ft_strcmp(command, "pwd\0") || !ft_strcmp(command, "unset\0"))
		return (1);
	return (0);
}

void ft_child(t_vars *vars, t_list *comm, t_env *envir)
{
	char *binary;
	char **_2denv;

	// ft_putstr_fd("comand id", 2);
	// printf("child pid :  cd /proc/%d/fd/\n",getpid());
	// ft_putstr_fd("IN CHILD ???? \n", 2);
	dup_and_close(vars->pfd[1], 1);
	dup_and_close(vars->old_fd, 0);
	if (vars->pfd[0] != 0 && vars->pfd[0] != 1)
		close(vars->pfd[0]);
	binary = ft_locate_bin(comm->content, getenv("PATH"));
	if (!binary)
	{
		close(vars->pfd[1]);
		close(vars->old_fd);
		ft_putstr_fd("#minishell: ", 2);
		ft_putstr_fd(comm->content, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	comm->content = binary;
	_2denv = ft_2denv(envir);
	execve(binary, ft_2dcomm(comm), (char *const *)_2denv);
	perror(comm->content);
	vars->exit_status = errno;
	exit(vars->exit_status);
}

void ft_builtin(t_list *comm, t_env **envir, t_vars *vars)
{
	if (comm && !ft_strncmp(comm->content, "cd\0", 5))
		ft_cd(vars, comm, *envir);
	else if (comm && !ft_strncmp(comm->content, "echo\0", 7))
		ft_echo(comm, vars);
	else if (comm && !ft_strncmp(comm->content, "env\0", 7))
		ft_env(*envir, vars);
	else if (comm && !ft_strncmp(comm->content, "exit\0", 7))
		ft_exit(comm , vars);
	else if (comm && !ft_strncmp(comm->content, "export\0", 7))
		ft_export(*envir, vars, comm);
	else if (comm && !ft_strncmp(comm->content, "pwd\0", 7))
		ft_pwd(vars, *envir);
	else if (comm && !ft_strncmp(comm->content, "unset\0", 7))
		ft_unset(comm, envir, vars);
}

int	 ft_handle_redir(t_list *node, t_list *next_node, t_vars *vars)
{
	int	fd = -1;
	if (!node || !next_node)
	{
		printf("i should'nt get here\n");
		return (-1);
	}
	 if (next_node->type == AMBIGUOUS)
	{
		ft_putstr_fd("minishell: ", 2); // fix for test (echo a | ls > /dev/stdin )
		ft_putstr_fd(next_node->content, 2);
		ft_putstr_fd("ambiguous redirect\n", 2);
		return (-1);
	 }
	if (node->type != PIP && node->type != RED_IN)
		vars->pipe = 0;
	if (node->type == RED_OUT)
	{
		if (!access(next_node->content, W_OK) && vars->cmd_num)
		{
			ft_putstr_fd("minishell: ", 2); // fix for test (echo a | ls > /dev/stdin )
			ft_putstr_fd(next_node->content, 2);
			ft_putstr_fd("Permission denied\n", 2);
			vars->exit_status = 1;
			return (-1);
		}
		fd = open(next_node->content, O_CREAT | O_WRONLY | O_TRUNC, 0622);
		//printf("outfile: %s\n", next_node->content);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(next_node->content);
			vars->exit_status = 1;
			return (-1);
		}
		if(vars->pfd[1] != 1)
			close(vars->pfd[1]);
		vars->pfd[1] = fd;
	}
	if (node->type == RED_APPEND)
	{
		fd = open(next_node->content, O_WRONLY | O_CREAT | O_APPEND, 0622);
		//printf("file: %s\n", next_node->content);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(next_node->content);
			vars->exit_status = 1;
			return (-1);
		}
		if(vars->pfd[1] != 1)
			close(vars->pfd[1]);
		vars->pfd[1] = fd;
	}
	if (node->type == RED_IN)
	{
		fd = open(next_node->content, O_RDONLY);
		//printf("infile: %s\n", next_node->content);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(next_node->content);
			vars->exit_status = 1;
			return (-1);
		}
		vars->old_fd = fd;
	}
	return (fd);
}

int ft_isred(int t)
{
	if (t == RED_IN || t == RED_OUT || t == RED_APPEND)
		return (1);
	return (0);
}
t_list *ft_check4red(t_list *comm, t_vars *vars)
{
	t_list *temp;
	t_list *new_comm;

	temp = comm;
	new_comm = NULL;
	while (temp)
	{
		if (ft_isred(temp->type))
		{
			if (ft_handle_redir(temp, temp->next, vars) == -1)
				return (NULL);/// need to free new comm at exit
			temp = temp->next;
			if (temp)
				temp = temp->next;
		}
		else
		{
			ft_lstadd_back(&new_comm, ft_lstnew(temp->content, temp->type));
			temp = temp->next;
		}
	}
	return (new_comm);
}

void ft_run(t_vars *vars, t_list *comm, t_env **envir)
{
	int id;
	t_list *new_comm;
	new_comm = NULL;

	id = 0;
	// int _stdout = dup(1);
	while (comm)
	{
		vars->pfd[0] = vars->old_fd;
		vars->pfd[1] = 1;
		new_comm = ft_split_pipe(&comm, vars);
		if (vars->pipe)
			pipe(vars->pfd);
		comm = ft_check4red(comm, vars);
		if (comm)
		{
			if (!ft_is_builtin(comm->content))
			{
				id = fork();
				if (id == -1)
				{
					perror("minishell: fork:");
					return;
				}
				if (!id)
					ft_child(vars, comm, *envir);
			}
			else
				ft_builtin(comm, envir, vars);
		}
		if (vars->old_fd)
			close(vars->old_fd);
		vars->old_fd = vars->pfd[0];
		if (vars->pfd[1] != 1)
			close(vars->pfd[1]);
		comm = new_comm;
		vars->cmd_num++;
		// dup_and_close(_stdout, 1);
	}

	int pid;
	if (waitpid(id, &pid, 0) > 0 && WIFEXITED(pid))
		vars->exit_status = WEXITSTATUS(pid);
	while (wait(NULL) > 0)
		;
}

void ft_execute(t_vars *vars, t_list *comm, t_env **envir)
{
	vars->numofpipes = ft_pipe_num(comm);
	vars->builtin = 0;
	vars->old_fd = 0;
	if (!comm)
		return;
	ft_run(vars, comm, envir);
}
