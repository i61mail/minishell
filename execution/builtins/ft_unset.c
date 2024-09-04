/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 03:58:14 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/04 01:07:38 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_list *command, t_env **envir,t_vars *vars)
{
	t_env *temp;
	t_env *prev;
	//t_env *to_free;

	command = command->next;
	prev = NULL;
	while (command)
	{
		if (ft_invalid_char(command->content, vars, 0)) 
		{
			command = command->next;
			continue;
		}
		temp = *envir;
		while (temp)
		{
			if (!ft_strcmp(command->content ,temp->key))
			{
				if(!prev)
				{
					printf("aa %s\n",temp->next->key);
					*envir = temp->next;
					//for (t_env *temp = *envir; temp->next ; temp = temp->next)
					//	printf("aa %s\n",temp->key);
				}
				else
				{
						//to_free = prev->next;
					prev->next = temp->next;
					//free(to_free->value);
					//free(to_free->key);
					//free(to_free);
				}
			}
			prev = temp;
			temp = temp->next;
		}
		command = command->next;
	}
}
