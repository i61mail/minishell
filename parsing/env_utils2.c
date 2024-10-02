/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:40:03 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/28 12:38:42 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_to_node(char *key, char *value, t_env **envir)
{
	t_env	*new_node;

	new_node = ft_lstenv(key, value);
	if (!new_node)
		return (free(key), free(value), -1);
	ft_lstenvadd_back(envir, new_node);
	return (0);
}

int	extra_vars(char *key, char *value, t_env **envir)
{
	if (ft_strncmp(key, "PWD\0", 7) == 0)
	{
		if (add_to_node(ft_strdup("2PWD"), ft_strdup(value), envir) == -1)
			return (-1);
	}
	if (ft_strncmp(key, "OLDPWD\0", 7) == 0)
	{
		free(value);
		value = NULL;
	}
	if (ft_strncmp(key, "_\0", 2) == 0)
	{
		free(value);
		value = ft_strdup("/usr/bin/env");
	}
	if (add_to_node(key, value, envir) == -1)
		return (-1);
	return (0);
}
