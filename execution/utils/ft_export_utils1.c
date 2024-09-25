/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 06:12:31 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/25 12:27:12 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_handle_split(t_list *comm, t_env **envir, t_vars *vars)
{
	int		i;
	char	**splited;

	i = 0;
	splited = ft_split_space(comm->content);
	while (splited && splited[i])
	{
		if (ft_invalid_char(splited[i], vars) == 0)
			ft_add_env(splited[i], NULL, envir, 4);
		i++;
	}
}

void	ft_handle_default(t_list *comm, t_env **envir)
{
	char	*key;
	char	*value;
	int		type;

	key = NULL;
	value = NULL;
	type = ft_var_type(comm->content);
	if (type == 0 || type == 3)
		ft_split_2(comm->content, "=", &key, &value);
	if (type == 1)
		ft_split_2(comm->content, "+=", &key, &value);
	if (type == 4)
		key = comm->content;
	ft_add_env(key, value, envir, type);
}

void	ft_add_env(char *key, char *value, t_env **envir, int type)
{
	t_env	*new;
	t_env	*temp;

	temp = *envir;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key))
		{
			if (type == 1)
				temp->value = ft_strjoin(ft_strdup(temp->value), value);
			else
				temp->value = value;
			return ;
		}
		temp = temp->next;
	}
	new = malloc(sizeof(t_env));
	new->key = ft_strdup(key);
	new->value = value;
	if (type == 3)
		new->value = ft_strdup("");
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
	ft_free_2d_array(sorted);
}
