/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 03:58:14 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/01 09:00:21 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_list *command, t_env **envir)
{
	t_env *temp;
	t_env *prev;
	t_env *to_free;

	command = command->next;
	while (command)
	{
		temp = *envir;
		prev = NULL;
		while (temp)
		{
			if (!ft_strcmp(command->content, temp->key))
			{
				if (!prev)
				{
					*envir = temp->next;
					to_free = temp;
				}
				else
				{
					to_free = temp;
					prev->next = temp->next;
				}
				free(to_free->value);
				free(to_free->key);
				free(to_free);
				break;
			}
			prev = temp;
			temp = temp->next;
		}
		command = command->next;
	}
}

