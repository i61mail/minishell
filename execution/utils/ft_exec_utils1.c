/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:23:32 by mait-lah          #+#    #+#             */
/*   Updated: 2024/10/01 14:57:38 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_2denv(t_env *envir, t_vars *vars)
{
	char	**_2denv;
	char	*temp;
	char	*temp1;
	int		i;

	i = 0;
	_2denv = malloc(sizeof(char *) * (ft_env_length(envir) + 1));
	if (!_2denv)
		return (NULL);
	while (envir)
	{
		if (ft_condition(envir, vars))
		{
			envir = envir->next;
			continue ;
		}
		temp = ft_strjoin(ft_strdup(envir->key), "=");
		temp1 = ft_strjoin(temp, envir->value);
		_2denv[i] = temp1;
		envir = envir->next;
		i++;
	}
	_2denv[i] = NULL;
	return (_2denv);
}

char	**ft_2dcomm(t_list *comm)
{
	char	**_2dcomm;
	int		i;

	i = 0;
	_2dcomm = malloc(sizeof(char *) * (ft_comm_length(comm) + 1));
	if (!_2dcomm)
		return (NULL);
	while (comm && !ft_isred(comm->type) && comm->type != AMBIGUOUS)
	{
		_2dcomm[i] = comm->content;
		comm = comm->next;
		i++;
	}
	_2dcomm[i] = NULL;
	return (_2dcomm);
}

t_list	*ft_free_lst_node(t_list *comm)
{
	t_list	*to_ret;

	to_ret = NULL;
	if (comm)
	{
		to_ret = comm->next;
		free(comm->content);
	}
	free(comm);
	return (to_ret);
}

t_list	*ft_split_pipe(t_list **new_comm, t_vars *vars)
{
	t_list		*temp;
	t_list		*prev;

	temp = (*new_comm);
	prev = NULL;
	while (temp && temp->type != PIP)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp)
	{
		vars->pipe = 1;
		if (prev)
			prev->next = NULL;
		return (ft_free_lst_node(temp));
	}
	else
	{
		vars->pipe = 0;
		return (NULL);
	}
}

char	*ft_strchr_2(const char *str, const char *sep)
{
	int	i;
	int	j;
	int	t;

	i = 0;
	if (!str || !sep)
		return (NULL);
	while (str[i])
	{
		t = i;
		j = 0;
		while (str[t++] == sep[j++])
		{
			if (j == ft_strlen((char *)sep))
				return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
