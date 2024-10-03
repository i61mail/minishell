/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:42:26 by mait-lah          #+#    #+#             */
/*   Updated: 2024/10/01 11:52:18 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list	*ft_setup(t_list *comm, t_list **new_comm, t_vars *vars)
{
	vars->override_es = 0;
	vars->pfd[0] = vars->old_fd;
	vars->pfd[1] = 1;
	*new_comm = ft_split_pipe(&comm, vars);
	if (vars->pipe)
		pipe(vars->pfd);
	comm = ft_check4red(comm, vars);
	return (comm);
}

int	ft_non_builtin(t_list *comm, t_env **envir, t_vars *vars)
{
	int	id;

	id = fork();
	if (ft_strncmp(comm->content, "./minishell\0", 12) == 0)
		ft_catch(4, 5);
	else
		ft_catch(0, 2);
	if (id == -1)
	{
		perror("minishell: fork:");
		return (-1);
	}
	if (!id)
	{
		signal(SIGQUIT, SIG_DFL);
		ft_child(vars, comm, *envir);
	}
	return (id);
}

void	ft_wait(int id, t_vars *vars)
{
	int		pid;

	if (waitpid(id, &pid, 0) > 0 && !vars->override_es)
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

int	unset_not_valid(char *err, t_vars *vars)
{
	ft_put_error("minishell: unset: `", err, "': not a valid identifier");
	vars->exit_status = 1;
	return (1);
}
