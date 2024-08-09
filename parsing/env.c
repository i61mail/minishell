/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:04:43 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/09 12:17:33 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	strcpy_env(t_env **envir, char **env)
{
	int		i;
	int		k;
	int		j;
	t_env	*new_node;
	char	*key;
	char	*value;

	i = 0;
	while (env[i])
	{
		k = 0;
		while (env[i][k] && env[i][k] != '=')
			k++;
		j = k;
		key = malloc(sizeof(char) * (k + 1));
		if (!key)
			return (-1);
		ft_strncpy(key, env[i], k);
		while (env[i][k])
			k++;
		k -= j;
		value = malloc(sizeof(char) * (k + 1));
		if (!value)
			return (free(key), -1);
		ft_strncpy(value, env[i] + j + 1, k);
		new_node = ft_lstenv(key, value);
		if (!new_node)
			return (free(key), free(value), -1);
		ft_lstenvadd_back(envir, new_node);
		i++;
	}
	// while (*envir)
	// {
	// 	printf("%s", (*envir)->key);
	// 	printf("=%s\n",(*envir)->value);
	// 	*envir = (*envir)->next;
	// }
	return (0);
}
