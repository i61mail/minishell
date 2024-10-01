/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:15:40 by mait-lah          #+#    #+#             */
/*   Updated: 2024/10/01 14:52:29 by isrkik           ###   ########.fr       */
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
		vars->exit_status = 127;
		return (1);
	}
	if (ft_file_err(binary, vars))
		return (1);
	return (0);
}

void	ft_fd(t_vars *vars)
{
	dup_and_close(vars->pfd[1], 1);
	dup_and_close(vars->old_fd, 0);
	if (vars->pfd[0] != 0 && vars->pfd[0] != 1)
		close(vars->pfd[0]);
}

void	ft_child(t_vars *vars, t_list *comm, t_env *envir)
{
	char	*binary;
	char	**_2denv;
	char	**_2dcomm;

	ft_fd(vars);
	while (comm && comm->type == AMBIGUOUS)
		comm = comm->next;
	if (!comm)
		exit(0);
	binary = ft_locate_bin(comm->content, my_getenv("PATH", envir));
	if (!ft_invalid_bin(binary, comm, vars))
	{
		comm->content = binary;
		_2denv = ft_2denv(envir);
		_2dcomm = ft_2dcomm(comm);
		execve(binary, _2dcomm, (char *const *)_2denv);
		perror(comm->content);
		vars->exit_status = errno;
	}
	else
		close(vars->old_fd);
	free(binary);
	exit(vars->exit_status);
}

void	ft_run(t_vars *vars, t_list *comm, t_env **envir)
{
	int		id;
	t_list	*new_comm;

	new_comm = NULL;
	id = 0;
	while (comm)
	{
		comm = ft_setup(comm, &new_comm, vars);
		if (comm)
		{
			if (!ft_is_builtin(comm->content))
				id = ft_non_builtin(comm, envir, vars);
			else
				ft_builtin(comm, envir, vars);
		}
		if (vars->old_fd)
			close(vars->old_fd);
		vars->old_fd = vars->pfd[0];
		if (vars->pfd[1] != 1)
			close(vars->pfd[1]);
		ft_lstfree(&comm);
		comm = new_comm;
		vars->cmd_num++;
	}
	ft_wait(id, vars);
}

t_list	*ft_execute(t_vars *vars, t_list *comm, t_env **envir)
{
	vars->numofpipes = ft_pipe_num(comm);
	vars->builtin = 0;
	vars->old_fd = 0;
	vars->pfd[1] = 1;
	vars->atoifail = 0;
	vars->cmd_num = 0;
	if (!comm)
		return (NULL);
	if (vars->exit_status == 130 && vars->is_signal == 1)
	{
		vars->exit_status = 1;
		close(vars->heredoc_fd);
		ft_lstfree(&comm);
		return (NULL);
	}
	if (vars->numofpipes == 0)
		old_search(vars, comm);
	comm = ft_dup_comm(comm);
	ft_run(vars, comm, envir);
	return (comm);
}
