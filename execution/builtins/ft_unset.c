/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 03:58:14 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/28 14:36:02 by isrkik           ###   ########.fr       */
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
	int	i;

	i = 0;
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

	to_ret = envir->next;
	free(envir->value);
	free(envir->key);
	free(envir);
	return (to_ret);
}

void	ft_unset_vars(t_list *command, t_env **envir)
{
	t_env	*prev;
	char	**splitd;
	int		i;
	t_env	*temp;

	i = 0;
	splitd = ft_split_space(command->content);
	while (splitd && splitd[i])
	{
		temp = *envir;
		while (temp)
		{
			if (!ft_strcmp(splitd[i], temp->key))
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
		i++;
	}
	ft_free_2d_array(splitd);// zdtha ana 
}

void	ft_unset(t_list *command, t_env **envir, t_vars *vars)
{
	command = command->next;
	vars->exit_status = 0;
	if (vars->numofpipes)
		return ;
	while (command)
	{
		if (!((command->type == COMM)
				&& ft_unset_invalid_char(command->content, vars)))
		{
			ft_unset_vars(command, envir);
		}
		command = command->next;
	}
}
