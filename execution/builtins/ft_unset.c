/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 03:58:14 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/08 00:53:55 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	unset_not_valid(char *err, t_vars *vars)
{
	ft_put_error("minishell: unset: `", err, "': not a valid identifier");
	vars->exit_status = 1;
	return (1);
}

int	ft_unset_invalid_char(char *kandv, t_vars *vars)
{
	//char c;
	int i;

	i = 0;
	
	if (!kandv || !kandv[i])
		return(unset_not_valid(kandv, vars));
	if ((kandv && kandv[i] && !(ft_isalpha(kandv[i]) || kandv[i] == '_')) || i++)
		return (unset_not_valid(kandv, vars));
	while (kandv && kandv[i] && (ft_isdigit(kandv[i]) || ft_isalpha(kandv[i]) || kandv[i] == '_' ))
		i++;
	if (kandv && kandv[i])
		return (unset_not_valid(kandv, vars));
	return (0);
}
 
void	ft_unset(t_list *command, t_env **envir, t_vars *vars)
{
	t_env *temp;
	t_env *prev;
	//t_env *to_free;
	char **splitd;
	int i =  0;
	command = command->next;
	prev = NULL;
	if (vars->numofpipes)
		return ;
	while (command)
	{
		if ((command->type == COMM) && ft_unset_invalid_char(command->content, vars)) 
		{
			command = command->next;
			continue;
		}
		splitd = ft_split(command->content, ' ');
		while (splitd && splitd[i])
		{
			temp = *envir;
			while (temp)
			{
				if (!ft_strcmp(splitd[i], temp->key))
				{
					if (!prev)
					{
						printf("aa %s\n", temp->next->key);
						*envir = temp->next;
						//for (t_env *temp = *envir;temp->next ;temp = temp->next)
						//	printf("aa %s\n", temp->key);
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
			i++;
		}
		command = command->next;
	}
}

