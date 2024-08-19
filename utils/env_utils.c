/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 09:00:08 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/18 11:16:05 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstenv(char *key, char *value)
{
	t_env	*temp;

	temp = (t_env *)malloc(sizeof(t_env));
	if (!temp)
		return (NULL);
	temp->key = key;
	temp->value = value;
	temp->next = NULL;
	return (temp);
}

void	ft_lstenvadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstenvlast(*lst);
	last->next = new;
}

t_env	*ft_lstenvlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_env_free(t_env **env)
{
	t_env	*curr;
	t_env	*temp;

	if (!env)
		return ;
	curr = *env;
	while (curr)
	{
		temp = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = temp;
	}
}
