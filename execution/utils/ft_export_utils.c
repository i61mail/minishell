/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 05:27:29 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/29 12:50:54 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strcmp_(char *s1, char *s2, char end)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] != end && s2[i] != end && s1[i] == s2[i])
		i++;
	if (s1 && s1[i] == '=')
		return (-1);
	if (s2 && s2[i] == '=')
		return (1);
	return (s1[i] - s2[i]);
}

int	not_valid(char *err, t_vars *vars)
{
	ft_put_error("minishell: export: `", err, "': not a valid identifier");
	vars->exit_status = 1;
	return (1);
}

int	ft_invalid_char(char *kandv, t_vars *vars)
{
	int	i;

	i = 0;
	if (!kandv || !kandv[i])
		return (not_valid(kandv, vars));
	if ((kandv && kandv[i]
			&& !(ft_isalpha(kandv[i]) || kandv[i] == '_')) || i++)
		return (not_valid(kandv, vars));
	while (kandv && kandv[i]
		&& (ft_isdigit(kandv[i]) || ft_isalpha(kandv[i]) || kandv[i] == '_' ))
		i++;
	if (kandv && (!kandv[i] || kandv[i] == '='))
		return (0);
	else if (kandv && kandv[i] == '+')
	{
		if (kandv && kandv[i + 1] != '=')
			return (not_valid(kandv, vars));
	}
	else
		return (not_valid(kandv, vars));
	return (0);
}

int	ft_var_type(char *var, t_env *envir)
{
	while (var && *var)
	{
		if (*var == '=' && *(var + 1))
			return (0);
		else if (*var == '=' && *(var + 1) == '\0')
			return (3);
		if (*var == '+' && *(var + 1) == '=')
			return (1);
		var++;
	}
	if (my_getenv(var, envir))
		return (1);
	return (4);
}

void	ft_handle_split(t_list *comm, t_env **envir, t_vars *vars)
{
	int		i;
	char	**splited;

	i = 0;
	splited = ft_split_space(comm->content);
	while (splited && splited[i])
	{
		if (ft_invalid_char(splited[i], vars) == 0)
		{
			vars->exprt_type = 4;
			ft_add_env(splited[i], NULL, envir, vars);
		}
		i++;
	}
}
