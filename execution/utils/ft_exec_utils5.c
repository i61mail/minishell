/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:42:26 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/26 13:42:54 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list	*ft_setup(t_list *comm, t_list **new_comm, t_vars *vars)
{
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

	if (waitpid(id, &pid, 0) > 0)
	{
		if (WIFEXITED(pid))
			vars->exit_status = WEXITSTATUS(pid);
		else if (WIFSIGNALED(pid))
			vars->exit_status = 128 + WTERMSIG(pid);
		if (vars->exit_status == 131)
			printf("Quit: 3\n");
		ft_catch(0, -1);
	}
	while (wait(NULL) > 0)
		;
}
