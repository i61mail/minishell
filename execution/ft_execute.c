/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:15:40 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/04 17:47:47 by isrkik           ###   ########.fr       */
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

	if (vars->not_red == 1 && vars->not_enter == 2)
	{
		dup2(vars->fd_buil, 1);
	}
	if (vars->pipe == 1 || vars->old_pipe == 2)
	{
		close(vars->pfd[0]);
	}
	else
	{
		dup2(vars->pfd[1], vars->_stdout);
		dup2(vars->old_fd, vars->_stdin);
	}
	binary = ft_locate_bin(comm->content, getenv("PATH"));
	if (binary == NULL)
	{
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
	if (ft_strncmp(comm->content, "cd\0", 3) == 0)
		ft_cd(vars, comm, *envir);
	else if (ft_strncmp(comm->content, "echo\0", 5) == 0)
		ft_echo(comm, vars, *envir);
	else if (ft_strncmp(comm->content, "env\0", 4) == 0)
		ft_env(*envir, vars, comm);
	else if (ft_strncmp(comm->content, "exit\0", 5) == 0)
		ft_exit(vars, envir, comm);
	else if (ft_strncmp(comm->content, "export\0", 7) == 0)
		ft_export(envir, vars, comm);
	else if (ft_strncmp(comm->content, "pwd\0", 4) == 0)
		ft_pwd(vars, *envir, comm);
	else if (ft_strncmp(comm->content, "unset\0", 6) == 0)
		ft_unset(comm, envir, vars);
	else
		ft_run(vars, comm, *envir);
	return ;
}

int	ft_handle_redir(t_list *node, t_list *next_node, t_vars *vars)
{
	if (!node || !next_node)
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
	if (node->type == RED_OUT)
	{
		int fd = open(next_node->content, O_WRONLY  | O_CREAT | O_TRUNC, 0644);
		if(fd == -1)
		{
			ft_putstr_fd("minishell: ",2);
			perror(next_node->content);
			vars->exit_status =  errno;
			return (-1);
		}
		if (vars->not_red == 1)
			vars->fd_buil = 1;
		dup2(fd, vars->fd_buil);
		close(fd);
	}
	if (node->type == RED_APPEND)
	{
		int fd = open(next_node->content, O_WRONLY  | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ",2);
			perror(next_node->content);
			vars->exit_status = errno;
			return (-1);
		}
		if (vars->not_red == 1)
			vars->fd_buil = 1;
		dup2(fd, vars->fd_buil);
		close(fd);
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
		}
		vars->red_built = 1;
		dup2(fd, 0);
		close(fd);
	}
	if(node->type == HEREDOC)
	{
		if(vars->heredoc_fd == -1)
		{
			ft_putstr_fd("minishell: ",2);
			perror(next_node->content);
			vars->exit_status =  errno;
			return (-1);
		}
		vars->fd_buil = 1;
		dup2(vars->heredoc_fd, 0);
		close(vars->heredoc_fd);
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
			if (temp->type == RED_OUT)
				vars->not_enter = 2;
			vars->not_red = 1;
            if (ft_handle_redir(temp, temp->next, vars) == -1)
			{
				return (NULL);
			}
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
		vars->not_red = 0;
	}
    return (comm);
}

int ft_exec_command(t_vars *vars, t_list *comm, t_env *envir)
{
	t_list *command;

	command = NULL;
    if (!comm || !comm->content)
        return (-1);
	if (vars->not_enter == 0)
	{
		command = ft_check4red(comm, vars);
		if (!command)
		{
			return (-1);
		}
		if (command)
			comm = command;
	}
    if (ft_is_builtin(comm->content))
    {
        ft_builtin(comm, &envir, vars);
        exit(vars->exit_status); 
    }
    else
    {
		ft_child(vars, comm, envir);
    }
    exit(vars->exit_status);
}

int ft_run(t_vars *vars, t_list *comm, t_env *envir)
{
    int id;
    t_list *new_comm;

    vars->_stdout = dup(1);
    vars->_stdin = dup(0);
    while (comm)
    {
        vars->pfd[0] = vars->old_fd;
        if (vars->pipe == 1)
        {
            vars->old_pipe = vars->pipe;
        }
        new_comm = ft_split_pipe(&comm, vars);
        if (vars->pipe == 1)
        {
            if (pipe(vars->pfd) == -1)
            {
                perror("minishell: pipe:");
                return(-1);
            }
        }
        id = fork();
        if (id == -1)
        {
            perror("minishell: fork:");
            return(-1);
        }
        if (id == 0)
        {
            if (vars->pipe && vars->fd_buil == 0)
            {
                dup2(vars->pfd[1], 1);
            }
            if (vars->old_fd != 0)
            {
                dup2(vars->old_fd, 0);
            }
            if (ft_exec_command(vars, comm, envir) == -1)
				return -1;
        }
        else
        {
            if (vars->pipe)
            {
                close(vars->pfd[1]);
            }
            if (vars->old_fd)
            {
                close(vars->old_fd);
            }
            vars->old_fd = vars->pfd[0];
            comm = new_comm;
        }
    }
    while (wait(NULL) > 0)
        ;
    dup2(vars->_stdout, 1);
    dup2(vars->_stdin, 0);
    close(vars->_stdout);
    close(vars->_stdin);
	return (0);
}

void	ft_execute(t_vars *vars, t_list *comm, t_env **envir)
{
	vars->numofpipes = ft_pipe_num(comm);
	vars->builtin = 0;
	vars->old_fd = 0;
	vars->old_pipe = 0;
	vars->pfd[1] = 1;
	vars->_stdout = 1;
    vars->_stdin = 0;
    vars->not_red = 0;
	vars->fd_buil = 0;
	vars->not_enter = 0;
	vars->red_built = 0;
	// int	restore = 0;
	if (!comm)
		return ;
	t_list *command = NULL;
	if (vars->numofpipes == 0 && (ft_is_builtin(comm->content) || ft_isred(comm->type)))
	{
		vars->not_enter = 1;
		command  = ft_check4red(comm, vars);
		if (command)
			comm = command;
		else if (!command)
		{
			dup2(1, vars->fd_buil);
			return ;
		}
	}
	if (ft_is_builtin(comm->content) && vars->numofpipes == 0)
	{
		ft_builtin(comm, envir, vars);
		dup2(1, vars->fd_buil);
		return ;
	}
	else
	{
		ft_run(vars, comm, *envir);
		dup2(1, vars->fd_buil);
		return ;
	}
}

//cat > a | << $USER
//ls > a | cat
//ls > a | whoami
//""
//echo > a | ls
//cd execution > a | cat
// cd execution > a | ls | ls > a
//echo | ls > a
//ls > a | echo > b
//ls > a | echo
//echo hello | ls > /dev/stdin
//echo > a
//env ls
//< Makefile
//<< a
//cat < Makefile
//echo < Makefile
//< Makefile cat
//cat | cat | ls > a | echo < Makefile
//echo "jfhgkjhg" > file | cat << a
//ls  | cat > a
//cat > a
//cat > a | ls
//> a
//>> a
