/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:56:18 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/28 11:55:54 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_is_builtin(char *command)
{
	if (!ft_strcmp(command, "cd\0") || !ft_strcmp(command, "echo\0")
		|| !ft_strcmp(command, "env\0")
		|| !ft_strcmp(command, "exit\0") || !ft_strcmp(command, "export\0")
		|| !ft_strcmp(command, "pwd\0") || !ft_strcmp(command, "unset\0"))
		return (1);
	return (0);
}

char	*my_getenv(char *str, t_env *envir)
{
	t_env	*temp;

	temp = envir;
	while (temp)
	{
		if (ft_strcmp(temp->key, str) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

void	ft_builtin(t_list *comm, t_env **envir, t_vars *vars)
{
	if (comm && !ft_strncmp(comm->content, "cd\0", 5))
		ft_cd(vars, comm, envir);
	else if (comm && !ft_strncmp(comm->content, "echo\0", 7))
		ft_echo(comm, vars);
	else if (comm && !ft_strncmp(comm->content, "env\0", 7))
		ft_env(*envir, vars);
	else if (comm && !ft_strncmp(comm->content, "exit\0", 7))
		ft_exit(comm, vars);
	else if (comm && !ft_strncmp(comm->content, "export\0", 7))
		ft_export(*envir, vars, comm);
	else if (comm && !ft_strncmp(comm->content, "pwd\0", 7))
		ft_pwd(vars, envir);
	else if (comm && !ft_strncmp(comm->content, "unset\0", 7))
		ft_unset(comm, envir, vars);
}

int	ft_isred(int t)
{
	if (t == RED_IN || t == RED_OUT || t == RED_APPEND || t == HEREDOC)
		return (1);
	return (0);
}

t_list	*ft_check4red(t_list *comm, t_vars *vars)
{
	t_list	*temp;
	t_list	*new_comm;

	temp = comm;
	new_comm = NULL;
	while (temp)
	{
		if (ft_isred(temp->type))
		{
			if (ft_handle_redir(temp, temp->next, vars) == -1)
				return (NULL);// need to free new comm at exit
			temp = temp->next;
			if (temp)
				temp = temp->next;
		}
		else
		{
			// ft_lstadd_back(&new_comm, ft_lstnew(temp->content, temp->type));
			temp = temp->next;
		}
	}
	return (comm);//returning new_comm
}
