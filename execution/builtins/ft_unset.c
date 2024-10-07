/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 03:58:14 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/30 10:33:21 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset_invalid_char(char *kandv, t_vars *vars)
{
	int	i;

	i = 0;
	vars->exit_status = 0;
	if (!kandv || !kandv[i])
		return (unset_not_valid(kandv, vars));
	if ((kandv && kandv[i]
			&& !(ft_isalpha(kandv[i]) || kandv[i] == '_')) || i++)
		return (unset_not_valid(kandv, vars));
	while (kandv && kandv[i]
		&& (ft_isdigit(kandv[i]) || ft_isalpha(kandv[i]) || kandv[i] == '_' ))
		i++;
	if (kandv && kandv[i])
		return (unset_not_valid(kandv, vars));
	return (0);
}

t_env	*ft_free_node(t_env *envir)
{
	t_env	*to_ret;

	to_ret = NULL;
	if (envir)
	{
		to_ret = envir->next;
		free(envir->value);
		free(envir->key);
	}
	free(envir);
	return (to_ret);
}

static void	init_vars(int *i, t_env **prev)
{
	*i = -1;
	*prev = NULL;
}

void	ft_unset_vars(t_list *command, t_env **envir)
{
	t_env	*prev;
	char	**splitd;
	int		i;
	t_env	*temp;

	init_vars(&i, &prev);
	splitd = ft_split_space(command->content);
	while (splitd && splitd[++i])
	{
		temp = *envir;
		while (temp)
		{
			if (!ft_strcmp(splitd[i], temp->key) && ft_strcmp(splitd[i], "_"))
			{
				if (!prev)
					*envir = ft_free_node(temp);
				else
					prev->next = ft_free_node(temp);
				break ;
			}
			prev = temp;
			temp = temp->next;
		}
	}
	ft_free_2d_array(&splitd);
}

void	ft_unset(t_list *command, t_env **envir, t_vars *vars)
{
	command = command->next;
	vars->exit_status = 0;
	while (command)
	{
		if (!((command->type == COMM)
				&& ft_unset_invalid_char(command->content, vars)
				&& !vars->numofpipes))
		{
			ft_unset_vars(command, envir);
		}
		command = command->next;
	}
}
