/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:27:36 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/06 08:28:39 by isrkik           ###   ########.fr       */
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
	if(s2 && s2[i] == '=')
		return (1);
	return (s1[i] - s2[i]);
}

char**	ft_sort_env(char **envir)
{
	int	i = 0;
	char *temp;
	int l;

	while(envir && envir[i])
		i++;
	l = i - 1;
	i = 0;
	while(i < l)
	{
		int j = 0;
		while(j < l)
		{
			temp = NULL;
			if(ft_strcmp_(envir[j], envir[j+1], '=') > 0)
			{
				temp = envir[j+1];
				envir[j+1] = envir[j];
				envir[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (envir);
}

char	**ft_2envkeys(t_env *envir)
{
	char	**_2denv;
	char	*temp  = NULL;
	int		i;

	i = 0;
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

void	ft_free_2d_array(void **array)
{
	int i;
	
	i = 0;
	while(array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
void	ft_print_env(t_env *envir,t_vars *vars)
{
	ft_putstr_fd("declare -x ", vars->pfd[1]);
	ft_putstr_fd(envir->key, vars->pfd[1]);
	if (envir->value)
	{
		ft_putstr_fd("=\"", vars->pfd[1]);
		ft_putstr_fd(envir->value,vars->pfd[1]);
		ft_putstr_fd("\"", vars->pfd[1]);
	}
	ft_putstr_fd("\n",vars->pfd[1]);
}
void	ft_dump_env(t_env *envir, t_vars *vars)
{	
	t_env *temp;
	char **sorted;
	int i;

	sorted = ft_sort_env(ft_2envkeys(envir));
	i = 0;

	while(sorted && sorted[i])
	{
		temp = envir;
		while(temp)
		{
			if (!ft_strcmp(temp->key,sorted[i]) && ft_strcmp(temp->key,"_\0") && ft_strcmp(temp->key, "2PWD\0"))
				ft_print_env(temp, vars);
			temp = temp->next;
		}
		i++;
	}
	ft_free_2d_array((void **)sorted);
}
void	ft_add_env(char *key, char *value, t_env **envir, int type)
{
	t_env *new;
	t_env *temp;

	temp = *envir;
	while(temp)
	{
		if(!ft_strcmp(temp->key , key))
		{
			if(type == 1)
				temp->value = ft_strjoin(ft_strdup(temp->value), value);
			else
				temp->value = value;
			return;
		}
		temp = temp->next;
	}

	new = malloc(sizeof(t_env));
	new->key = ft_strdup(key);
	new->value = value;
	if(type == 3)
		new->value = ft_strdup("");
	new->next = NULL;
	ft_lstenvadd_back(envir, new);
}

int	ft_put_error(char *before, char *sep, char *after)
{
	ft_putstr_fd(before, 2);
	ft_putstr_fd(sep, 2);
	ft_putstr_fd(after, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
int	not_valid(char *err, t_vars *vars)
{
	ft_put_error("minishell: export: `", err, "': not a valid identifier");
	vars->exit_status = 1;
	return (1);
}
int	ft_invalid_char(char *kandv, t_vars *vars, int is_export)
{
	//char c;
	int i;
	(void)is_export;

	i = 0;
	
	if(!kandv || !kandv[i])
		return(not_valid(kandv, vars));
	if ((kandv && kandv[i] && !(ft_isalpha(kandv[i]) || kandv[i] == '_')) || i++)
		return (not_valid(kandv, vars));
	while(kandv && kandv[i] && (ft_isdigit(kandv[i]) || ft_isalpha(kandv[i]) || kandv[i] == '_' ))
		i++;
	if (kandv && (!kandv[i] || kandv[i] == '='))
		return (vars->exit_status = 0);
	else if(kandv && kandv[i] == ' ')
	{
		vars->exit_status = 0;
		return(2);
	}
	else if (kandv && kandv[i] == '+' && is_export)
	{
		if (kandv && kandv[i + 1] != '=')
			return (not_valid(kandv, vars));
	}
	else
		return (not_valid(kandv, vars));
	return (0);
}

int	ft_var_type(char *var)
{
	while(var && *var)
	{
		if(*var == '=' && *(var + 1))
			return(0);
		else if (*var == '=' && *(var + 1) == '\0')
			return(3); // empty but with equal a=
		if(*var == '+' && *(var + 1) == '=')
			return (1); // append a+=b z
		var++;
	}
	return (4); //no value var export a
}

int	ft_export(t_env *envir,t_vars *vars, t_list *command)
{
	t_list *temp;
	char *key;
	char *value;
	int type;
	char **splited;
	int 	i;

	i = 0;
	if(vars->numofpipes)
		return(0);
	temp = command->next;
	if(!ft_strncmp(command->content,"export\0",7) && (!command->next || *(command->next->content) == '\0'))
		ft_dump_env(envir, vars);
	else
	{
		while(temp)
		{   
			key = NULL;
			value = NULL;
			ft_putstr_fd(temp->content , 2 );
			ft_putchar_fd('\n',2);
			if (ft_invalid_char(temp->content, vars, 1) == 1)
			{
				temp = temp->next;
				continue;
			}
			else if (ft_invalid_char(temp->content, vars, 1) == 2)
			{
				splited = ft_split(temp->content, ' ');
				while(splited && splited[i])
				{
					ft_add_env(splited[i], NULL, &envir , 4);
					i++;
				}
				temp = temp->next;
				continue;
			}
			type = ft_var_type(temp->content);
			if (type == 0 || type == 3)
				ft_split_2(temp->content, "=", &key , &value);
			if (type == 1)
				ft_split_2(temp->content, "+=", &key , &value);
			if (type == 4)
				key = temp->content;
			ft_add_env(key, value, &envir , type);
			temp = temp->next;
		}
	}
	return (0);
}
