/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:15:40 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/01 12:09:17 by isrkik           ###   ########.fr       */
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
	if (binary == NULL)
	{
		// close(vars->pfd[1]);
		close(vars->old_fd);
		printf("minishell: %s: command not found\n", comm->content);
		vars->exit_status = 127;
		exit(errno);
	}
	comm->content = binary;
	_2denv = ft_2denv(envir);
	execve(binary, ft_2dcomm(comm), (char *const *)_2denv);
	perror(comm->content);
	vars->exit_status = errno;
	exit(vars->exit_status);
}

void	ft_builtin(t_list *comm, t_env **envir, t_vars *vars)
{
	if (comm && !ft_strncmp(comm->content, "cd\0", 5))
		ft_cd(vars, comm, *envir);
	else if (comm && !ft_strncmp(comm->content, "echo\0", 7))
		ft_echo(comm, vars, *envir);
	else if (comm && !ft_strncmp(comm->content, "env\0", 7))
	{
		ft_env(*envir, vars, comm);
	}
	else if (comm && !ft_strncmp(comm->content, "exit\0", 7))
		ft_exit(vars, envir, comm);
	else if (comm && !ft_strncmp(comm->content, "export\0", 7))
		ft_export(envir, vars, comm);
	else if (comm && !ft_strncmp(comm->content, "pwd\0", 7))
		ft_pwd(vars, *envir, comm);
	else if (comm && !ft_strncmp(comm->content, "unset\0", 7))
		ft_unset(comm, envir, vars);
	else
		ft_run(vars, comm, *envir);
}

int	ft_handle_redir(t_list *node, t_list *next_node, t_vars *vars)
{
	(void)vars;
	if(!node || !next_node)
	{
		printf("i should'nt get here\n");
		return (-1);
	}
	if (next_node->type == AMBIGUOUS)
	{
		printf("minishell: %s: ambiguous redirect\n", next_node->content);
		vars->exit_status =  errno;
		return (-1);
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
			return (-1);
			// exit(vars->exit_status);
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
			return (-1);
			// exit(vars->exit_status);	
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
			return (-1);
			// exit(vars->exit_status);
		}
		dup_and_close(fd, 0);
	}
	if(node->type == HEREDOC)
	{
		if(vars->heredoc_fd == -1)
		{
			ft_putstr_fd("minishell: ",2);
			perror(next_node->content);
			vars->exit_status =  errno;
			return (-1);
			// exit(vars->exit_status);
		}
		dup_and_close(vars->heredoc_fd, 0);
	}
	return (0);
}

int		ft_isred(int	t)
{
	if (t == RED_IN || t == RED_OUT || t == RED_APPEND || t == HEREDOC)
		return (1);
	return (0);
}
t_list *ft_check4red(t_list *comm, t_vars *vars)
{
    t_list *temp;
    t_list *prev;
    t_list *first_command;

	prev = NULL;
	first_command = NULL;
    temp = comm;
    while (temp)
    {
        if (ft_isred(temp->type))
        {
            if (ft_handle_redir(temp, temp->next, vars) == -1)
				return (NULL);
            if (prev)
                prev->next = temp->next->next;
            else
                comm = temp->next->next;
            temp = temp->next->next;
            continue;
        }
        if (!first_command)
            first_command = temp;
        prev = temp;
        temp = temp->next;
	}
    return (comm);
}


void ft_exec_command(t_vars *vars, t_list *comm, t_env *envir)
{
    if (!comm || !comm->content)
        return;
    if (ft_is_builtin(comm->content))
    {
        vars->builtin = 1;
        ft_builtin(comm, &envir, vars);
    }
    else
	ft_child(vars, comm, envir);
    exit(vars->exit_status);
}

void ft_run(t_vars *vars, t_list *comm, t_env *envir)
{
    int id;
    t_list *new_comm;
    int _stdout;
    int _stdin;

	new_comm = NULL;
	_stdout = dup(1);
	_stdin = dup(0);
    while (comm)
    {
        vars->pfd[0] = vars->old_fd;
        vars->pfd[1] = 1;
        new_comm = ft_split_pipe(&comm, vars);
        if (vars->pipe)
            pipe(vars->pfd);
        comm = ft_check4red(comm, vars);
        id = fork();
        if (id == -1)
        {
            perror("minishell: fork:");
            return;
        }
        if (!id)
            ft_exec_command(vars, comm, envir);
        if (vars->old_fd)
            close(vars->old_fd);
        vars->old_fd = vars->pfd[0];
        if (vars->pfd[1] != 1)
            close(vars->pfd[1]);
        comm = new_comm;
    }
	int pid = 0;
	wait(&pid);
	if (WIFEXITED(pid))
	vars->exit_status = WEXITSTATUS(pid);
    // Restore stdin and stdout
    dup_and_close(_stdout, 1);
    dup_and_close(_stdin, 0);
}

void	ft_execute(t_vars *vars, t_list *comm, t_env **envir)
{
	vars->numofpipes = ft_pipe_num(comm);
	vars->builtin = 0;
	vars->old_fd = 0;
	vars->pfd[1] = 1;
	if (!comm)
		return ;
	ft_builtin(comm, envir, vars);
	// ft_run(vars, comm, envir);
}
