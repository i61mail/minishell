/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:27:36 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/09 06:19:20 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_sort_env(char **envir)
{
	int		i;
	int		j;
	char	*temp;
	int		l;

	i = 0;
	while (envir && envir[i])
		i++;
	l = i - 1;
	i = -1;
	while (++i < l)
	{
		j = -1;
		while (++j < l)
		{
			temp = NULL;
			if (ft_strcmp_(envir[j], envir[j + 1], '=') > 0)
			{
				temp = envir[j + 1];
				envir[j + 1] = envir[j];
				envir[j] = temp;
			}
		}
	}
	return (envir);
}

char	**ft_2envkeys(t_env *envir)
{
	char	**_2denv;
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	_2denv = malloc(sizeof(char *) * (ft_env_length(envir) + 1));
	if (!_2denv)
		return (NULL);
	while (envir)
	{
		temp = ft_strdup(envir->key);
		_2denv[i] = temp;
		envir = envir->next;
		i++;
	}
	_2denv[i] = NULL;
	return (_2denv);
}

void	ft_print_env(t_env *envir, t_vars *vars)
{
	ft_putstr_fd("declare -x ", vars->pfd[1]);
	ft_putstr_fd(envir->key, vars->pfd[1]);
	if (envir->value)
	{
		ft_putstr_fd("=\"", vars->pfd[1]);
		ft_putstr_fd(envir->value, vars->pfd[1]);
		ft_putstr_fd("\"", vars->pfd[1]);
	}
	ft_putstr_fd("\n", vars->pfd[1]);
}

int	ft_export(t_env *envir, t_vars *vars, t_list *command)
{
	t_list	*temp;

	temp = command->next;
	if (!ft_strncmp(command->content, "export\0", 7)
		&& (!command->next || *(command->next->content) == '\0'))
		ft_dump_env(envir, vars);
	if (vars->numofpipes)
		return (0);
	else
	{
		while (temp)
		{
			if (temp->type == SPLITED)
				ft_handle_split(temp, &envir, vars);
			else if (ft_invalid_char(temp->content, vars) == 1)
				ft_handle_default(temp, &envir);
			temp = temp->next;
		}
	}
	return (0);
}
