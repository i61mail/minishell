/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 03:58:14 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/31 18:36:40 by mait-lah         ###   ########.fr       */
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
