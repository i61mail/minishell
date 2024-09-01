/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 03:58:14 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/01 01:13:42 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_list *command, t_env **envir)
{
	t_env *temp;
	t_env *prev;
	t_env *to_free;

	command = command->next;
	prev = NULL;
	while (command)
	{
		temp = *envir;
		while (temp)
		{
			if (!ft_strcmp(command->content ,temp->key))
			{
				//if(!prev)
				//{
				//	puts("here");
				//	*envir = temp->next;
				//}
				to_free = prev->next;
				prev->next = temp->next;
				free(to_free->value);
				free(to_free->key);
				free(to_free);
			}
			prev = temp;
			temp = temp->next;
		}
		command = command->next;
	}
}
