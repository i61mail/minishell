/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:55:00 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/27 10:20:19 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	last_be_first(char **str, int *b, char **s, t_vars *vars)
{
	char	*string;
	char	*temp;

	temp = NULL;
	string = NULL;
	string = ft_strstr(*str, s[*b], b);
	vars->befor_sing = vars->catsh + *b;
	temp = ft_strjoin(temp, string);
	(*b)++;
	free(*str);
	*str = ft_strdup("");
	*str = ft_strjoin(*str, temp);
}

void	copie_to_node(char **str, t_list **comm, t_vars *vars)
{
	int		b;
	char	*token;
	char	**s;
	int		i;

	token = NULL;
	b = 0;
	s = ft_split_space(*str);
	i = double_pointer(s);
	while (i - 1 > 0 && s[b])
	{
		token = ft_strdup(s[b]);
		ft_lstadd_back(comm, ft_lstnew(token, COMM));
		b++;
		i--;
	}
	last_be_first(str, &b, s, vars);
}

void	add_to_temp(char **str_temp, int *i, t_vars *vars)
{
	char	temp[2];

	vars->bef_dollar = 1;
	temp[1] = '\0';
	temp[0] = vars->read[*i];
	*str_temp = ft_strjoin(*str_temp, temp);
	(*i)++;
}

void	check_splited(t_vars *vars, int *i, int *type)
{
	if (*i > 0 && (ft_isalpha(vars->read[*i - 1]) || vars->read[*i - 1] == '_'
			|| ft_isspace(vars->read[*i - 1])))
		*type = SPLITED;
	else if (*i == 0 && vars->read[*i] == '$')
		*type = SPLITED;
}

void	split_before_quotes(t_vars *vars, char **str_temp,
		t_list **comm, int *i)
{
	if (check_space(*str_temp) == 1)
	{
		vars->befo_qu = *i;
		copie_to_node(str_temp, comm, vars);
		vars->befor = ft_strdup(*str_temp);
	}
}
