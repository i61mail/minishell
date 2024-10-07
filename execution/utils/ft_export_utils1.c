/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 06:12:31 by mait-lah          #+#    #+#             */
/*   Updated: 2024/10/01 21:30:31 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_handle_default(t_list *comm, t_env **envir, t_vars *vars)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	vars->exprt_type = ft_var_type(comm->content, *envir);
	if (vars->exprt_type == 0 || vars->exprt_type == 3)
		ft_split_2(comm->content, "=", &key, &value);
	if (vars->exprt_type == 1)
		ft_split_2(comm->content, "+=", &key, &value);
	if (vars->exprt_type == 4)
		key = comm->content;
	ft_add_env(key, value, envir, vars);
	if (vars->exprt_type != 4)
		free(key);
}

void	add_value_util(t_env **temp, char **tmp, char *value)
{
	if ((*temp)->value && (*temp)->value[0] != '\0')
	{
		*tmp = (*temp)->value;
		free(*tmp);
	}
	else
	{
		free((*temp)->value);
		(*temp)->value = value;
		return ;
	}
	(*temp)->value = value;
}

void	add_value(t_env **temp, char *value, t_vars *vars)
{
	char	*tmp;

	if (!ft_strcmp("PATH", (*temp)->key))
		vars->env_i = 0;
	if (temp)
	{
		if (vars->exprt_type == 1)
		{
			tmp = (*temp)->value;
			free(tmp);
			(*temp)->value = ft_strjoin(ft_strdup((*temp)->value), value);
			free(value);
			tmp = NULL;
		}
		else
		{
			if (!value)
				return ;
			add_value_util(temp, &tmp, value);
		}
		return ;
	}
}

void	ft_add_env(char *key, char *value, t_env **envir, t_vars *vars)
{
	t_env	*new;
	t_env	*temp;

	temp = *envir;
	while (temp)
	{
		if (ft_strncmp(key, "_\0", 2) == 0)
			return (free(value));
		if (!ft_strcmp(temp->key, key))
			return (add_value(&temp, value, vars));
		temp = temp->next;
	}
	new = malloc(sizeof(t_env));
	new->key = ft_strdup(key);
	new->value = value;
	if (vars->exprt_type == 3)
	{
		free(new->value);
		new->value = ft_strdup("");
	}
	new->next = NULL;
	ft_lstenvadd_back(envir, new);
}

void	ft_dump_env(t_env *envir, t_vars *vars)
{
	t_env	*temp;
	char	**sorted;
	int		i;

	sorted = ft_sort_env(ft_2envkeys(envir));
	i = 0;
	while (sorted && sorted[i])
	{
		temp = envir;
		while (temp)
		{
			if (temp->value
				&& ft_strncmp(temp->key, "PATH\0", 5) == 0 && vars->env_i == 1)
				temp = temp->next;
			if (!ft_strcmp(temp->key, sorted[i]) && ft_strcmp(temp->key, "_\0")
				&& ft_strcmp(temp->key, "2PWD\0"))
				ft_print_env(temp, vars);
			temp = temp->next;
		}
		i++;
	}
	ft_free_2d_array(&sorted);
}
