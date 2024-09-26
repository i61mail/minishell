/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:15:40 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/26 09:59:01 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_invalid_bin(char *binary, t_list *comm, t_vars *vars)
{
	if (!binary)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(comm->content, 2);
		ft_putstr_fd(": command not found\n", 2);
		free(comm->content);
		free(comm);
		vars->exit_status = 127;
		return (1);
	}
	if (ft_file_err(binary, vars))
		return (1);
	return (0);
}

void	ft_child(t_vars *vars, t_list *comm, t_env *envir)
{
	char	*binary;
	char	**_2denv;

	dup_and_close(vars->pfd[1], 1);
	dup_and_close(vars->old_fd, 0);
	if (vars->pfd[0] != 0 && vars->pfd[0] != 1)
		close(vars->pfd[0]);
	while (comm && comm->type == AMBIGUOUS)
		comm = comm->next;
	if (!comm)
		exit(0);
	binary = ft_locate_bin(comm->content, my_getenv("PATH", envir));
	if (!ft_invalid_bin(binary, comm, vars))
	{
		comm->content = binary;
		_2denv = ft_2denv(envir);
		execve(binary, ft_2dcomm(comm), (char *const *)_2denv);
		perror(comm->content);
		vars->exit_status = errno;
	}
	else
		close(vars->old_fd);
	exit(vars->exit_status);
}

int	ft_handle_redir(t_list *node, t_list *next_node, t_vars *vars)
{
	int	fd;

	fd = -1;
	if (!node || !next_node)
	{
		printf("i should'nt get here\n");
		return (-1);
	}
	if (next_node->type == AMBIGUOUS)
	{
		ft_putstr_fd("minishell: ", 2);// fix for test (echo a | ls > /dev/stdin )
		ft_putstr_fd(next_node->content, 2);
		ft_putstr_fd(" ambiguous redirect\n", 2);
		vars->exit_status = 1;
		return (-1);
	}
	if (node->type != PIP && node->type != RED_IN)
		vars->pipe = 0;
	if (node->type == RED_OUT)
	{
		fd = open(next_node->content, O_CREAT | O_WRONLY | O_TRUNC, 0622);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(next_node->content);
			vars->exit_status = 1;
			return (-1);
		}
		if (vars->pfd[1] != 1)
			close(vars->pfd[1]);
		vars->pfd[1] = fd;
	}
	if (node->type == RED_APPEND)
	{
		fd = open(next_node->content, O_WRONLY | O_CREAT | O_APPEND, 0622);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(next_node->content);
			vars->exit_status = 1;
			return (-1);
		}
		if (vars->pfd[1] != 1)
			close(vars->pfd[1]);
		vars->pfd[1] = fd;
	}
	if (node->type == RED_IN)
	{
		fd = open(next_node->content, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(next_node->content);
			vars->exit_status = 1;
			return (-1);
		}
		vars->old_fd = fd;
	}
	if (node->type == HEREDOC)
	{
		if (vars->heredoc_fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(next_node->content);
			vars->exit_status = errno;
			return (-1);
		}
		vars->old_fd = vars->heredoc_fd;
		// close(vars->heredoc_fd);
		return (vars->heredoc_fd);
	}
	return (fd);
}

void	ft_run(t_vars *vars, t_list *comm, t_env **envir)
{
	int		id;
	t_list	*new_comm;
	int		pid;

	new_comm = NULL;
	id = 0;
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
				ft_catch(0, 2);
				if (id == -1)
				{
					perror("minishell: fork:");
					return ;
				}
				if (!id)
				{
					signal(SIGQUIT, SIG_DFL);
					ft_child(vars, comm, *envir);
				}
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
	}
	if (waitpid(id, &pid, 0) > 0)
	{
		if (vars->exit_status == 130 && vars->is_signal == 1)
		{
			vars->exit_status = 1;
			return ;
		}
    	if (WIFEXITED(pid))
        	vars->exit_status = WEXITSTATUS(pid);
		else if (WIFSIGNALED(pid))
			vars->exit_status = 128 + WTERMSIG(pid);
		if (vars->exit_status == 131)
			printf("Quit: 3\n");
	}
	while (wait(NULL) > 0)
		;
	ft_catch(0, -1);
}

void	ft_execute(t_vars *vars, t_list *comm, t_env **envir)
{
	vars->numofpipes = ft_pipe_num(comm);
	vars->builtin = 0;
	vars->old_fd = 0;
	vars->pfd[1] = 1;
	vars->atoifail = 0;
	if (!comm)
		return ;
	comm = ft_dup_comm(comm);
	ft_run(vars, comm, envir);
	if (vars->exit_status == 130 && vars->is_signal == 1)
		vars->exit_status = 1;
}
