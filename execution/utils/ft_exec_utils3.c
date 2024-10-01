/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: i61mail <i61mail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:56:18 by mait-lah          #+#    #+#             */
/*   Updated: 2024/10/01 21:23:27 by i61mail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	ft_check4red_util(t_list **temp, t_vars *vars)
{
	if (temp && *temp)
		*temp = (*temp)->next;
	if (temp && *temp)
	{
		if ((*temp)->type != HEREDOC)
		{
			free(vars->last_arg);
			vars->last_arg = ft_strdup((*temp)->content);
		}
		else
		{
			free(vars->last_arg);
			vars->last_arg = NULL;
		}
	}
}

void	free_failure_red(t_list **new_comm, t_list *comm, t_list *temp, t_vars *vars)
{
	(void)comm;
	if (new_comm)
	{
		free(temp->content);
		free(temp);
	}
	if (vars->type != AMBIGUOUS && !ft_isred(comm->type))
	{
		free(comm->content);
		free(comm);
	}
	ft_lstfree(new_comm);
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
				return (free_failure_red(&new_comm, comm, temp, vars), NULL);
			temp = temp->next;
			ft_check4red_util(&temp, vars);
		}
		else
		{
			ft_lstadd_back(&new_comm,
				ft_lstnew(ft_strdup(temp->content), temp->type));
			temp = temp->next;
		}
	}
	ft_lstfree(&comm);
	return (new_comm);
}
