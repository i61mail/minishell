/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:04:43 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/05 15:52:45 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*add_to_key(char *env, int j)
{
	char	*key;

	key = malloc(sizeof(char) * (j + 1));
	if (!key)
		return (NULL);
	ft_strncpy(key, env, j);
	return (key);
}

static char	*add_to_value(char *env, int len, int j)
{
	char	*value;

	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	ft_strncpy(value, env + j + 1, len);
	return (value);
}

int	add_to_node(char *key, char *value, t_env **envir)
{
	t_env	*new_node;

	new_node = ft_lstenv(key, value);
	if (!new_node)
		return (free(key), free(value), -1);
	ft_lstenvadd_back(envir, new_node);
	return (0);
}

int	strcpy_env(t_env **envir, char **env)
{
	int		i;
	int		j;
	int		len;
	char	*key;
	char	*value;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		key = add_to_key(env[i], j);
		if (!key)
			return (-1);
		len = ft_strlen(env[i]);
		len -= j;
		value = add_to_value(env[i], len, j);
		if (!value)
			return (free(key), -1);
		if (ft_strncmp(key, "PWD\0", 7) == 0)
		{
			add_to_node(ft_strdup("_PWD"), ft_strdup(value), envir);
		}
		if (ft_strncmp(key, "OLDPWD\0", 7) == 0)
			value = NULL;
		if (add_to_node(key, value, envir) == -1)
			return (-1);
		i++;
	}
	return (0);
}
