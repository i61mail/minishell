/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:09:34 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/07 17:44:43 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_token(t_vars *vars, int i, t_list **comm, int type)
{
	char	*token;
	t_list	*current;

	token = ft_substr(vars->read, vars->catsh, i - vars->catsh);
	if (!token)
		return (-1);
	current = ft_lstnew(token, type);
	if (!current)
		return (free(token), free(current), -1);
	ft_lstadd_back(comm, current);
	if (!*comm)
		return (free(token), free(current), -1);
	return (0);
}

int	quotes(t_vars *vars, int *i, t_list **comm)
{
	if (ft_isquotes(vars->read[*i]))
	{
		if (even_odd(vars->read) == 0)
		{
			ft_error(comm);
			return (-1);
		}
		ft_arequotes(vars, i, comm);
	}
	return (0);
}

int	ft_pars_comm(t_vars *vars, t_list **comm)
{
	int	i;

	i = 0;
	while (vars->read[i] != '\0')
	{
		if (!ft_issep(vars->read[i])
			&& !ft_isspace(vars->read[i]) && !ft_isquotes(vars->read[i]))
			ft_arealpha(vars, &i, comm);
		else if (ft_isspace(vars->read[i]))
			ft_arespace(vars->read, &i);
		else if (ft_issep(vars->read[i]))
		{
			if (ft_aresep(vars, &i, comm) == -1)
				return (-1);
		}
		if (quotes(vars, &i, comm) == -1)
			return (-1);
	}
	while (*comm)
	{
		printf("%s      &&    %d\n", (*comm)->content, (*comm)->type);
		*comm = (*comm)->next;
	}
	return (0);
}

int	strcpy_env(t_env **envir, char **env)
{
	int		i;
	int		k;
	int		j;
	t_env	*new_node;
	char	*key;
	char	*value;

	i = 0;
	while (env[i])
	{
		k = 0;
		while (env[i][k] && env[i][k] != '=')
			k++;
		j = k;
		key = malloc(sizeof(char) * (k + 1));
		if (!key)
			return (-1);
		ft_strncpy(key, env[i], k);
		while (env[i][k])
			k++;
		k -= j;
		value = malloc(sizeof(char) * (k + 1));
		if (!value)
			return (free(key), -1);
		ft_strncpy(value, env[i] + j + 1, k);
		new_node = ft_lstenv(key, value);
		if (!new_node)
			return (free(key), free(value), -1);
		ft_lstenvadd_back(envir, new_node);
		i++;
	}
	while (*envir)
	{
		// printf("key == %s\n", (*envir)->key);
		printf("%s", (*envir)->key);
		printf("=%s\n",(*envir)->value);
		*envir = (*envir)->next;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_list	*comm;
	t_vars	vars;
	t_env	*envir;

	(void)av;
	envir = NULL;
	strcpy_env(&envir, env);
	while (1)
	{
		comm = NULL;
		if (ac == 1)
		{
			vars.read = readline("minishell> ");
			if (!vars.read)
				break ;
			add_history(vars.read);
			ft_pars_comm(&vars, &comm);
		}
		else
			break ;
	}
	return (0);
}
