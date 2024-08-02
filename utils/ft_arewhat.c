#include "../minishell.h"

int    ft_arealpha(t_vars *vars, int *i, t_list **comm)
{
	vars->catsh = *i;
	while (vars->read[*i])
	{
		if (!ft_issep(vars->read[*i]) && !ft_isspace(vars->read[*i]) && !ft_isquotes(vars->read[*i]))
			(*i)++;
		else
			break ;
	}
	if (ft_isquotes(vars->read[*i]))
		return (2);
	if (ft_token(vars, *i, comm, COMM) == -1)
		return (-1);
	return (0);
}

int ft_arespace(char *read, int *i)
{
	while (read[*i])
	{
		if (ft_isspace(read[*i]))
			(*i)++;
		else
			break ;
	}
	return (0);
}

static int	ft_aresep2(t_vars *vars, int *i, int type, t_list **comm)
{
	int	check;

	check = 0;
	if (type == 4) // heredoc <<
	{
		vars->catsh = *i;
		check = ft_heredoc(vars, i, comm);
		if (check == 2)
			return (2);
		else if (check == -1)
			return (-1);
	}
	else if (type == 1 || type == 2) //redirection '<' && '>'
	{
		vars->catsh = *i;
		if (type == 1)
		{
			check = ft_redirec(vars, i, '<', comm);
			if (check == 2)
				return (2);
			else if (check == -1)
				return (-1);
		}
		else
		{
			check = ft_redirec(vars, i, '>', comm);
			if (check == 2)
				return (2);
			else if (check == -1)
				return (-1);
		}
	}
	return (0);
}

int ft_aresep(t_vars *vars, int *i, t_list **comm)
{
	int	type;
	int	check;

	type = 0;
	if (ft_check_type(vars->read, i, &type) == -1)
	{
		ft_error(comm);
		return (-1);
	}
	if (type == 5) //pipe
	{
		vars->catsh = *i;
		check = ft_pipe(vars, i, comm);
		if (check == 2)
			return (2);
		else if (check == -1)
			return (-1);
	}
	else if (type == 3) //append >>
	{
		vars->catsh = *i;
		check = ft_append(vars, i, comm);
		if (check == 2)
			return (2);
		else if (check == -1)
			return (-1);
	}
	if (ft_aresep2(vars, i, type, comm) == -1)
		return (-1);
	if (ft_token(vars, *i, comm, type) == -1)
		return (-1);
	return (0);
}

int	ft_count_dollar(char *str, int *i)
{
	int	k;

	k = 0;
	while (str[*i] == '$')
	{
		(*i)++;
		k++;
	}
	if (k % 2 == 0)
		return (k);
	else
		return (k - 1);
	return (0);
}

int	ft_arequotes(t_vars *vars, int *i, t_list **comm, int type)
{
	// t_vars	temp;
	char	*str_tmp;
	(void)comm;
	(void)type;
	char temp[2];
	int	d = 0;
	int a = 0;
	char *temp2 = NULL;
	// char *expand = NULL;
	int	check;
	// int	sing = 0;

	check = 0;
	temp[1] = '\0';
	str_tmp = malloc(sizeof(char) * (ft_strlen(vars->read) - *i));
	if (!str_tmp)
		return (-1);
	str_tmp[0] = '\0';
	// str_tmp = ft_substr(vars->read, *i, ft_strlen(vars->read) - *i);
	// printf("%s\n", str_tmp);
	// int	check;
	
	// check = 0;
	// while (vars->read[*i])
	// {
	// 	(*i)++;
	// 	if (ft_isquotes(vars->read[*i]) || vars->read[*i] == '\0' || ft_isspace(vars->read[*i]) || ft_issep(vars->read[*i]))
	// 	{
	// 		if (ft_isquotes(vars->read[*i]))
	// 			check = 1;
	// 		if (ft_issep(vars->read[*i]) && check == 1)
	// 		{
	// 			ft_token(vars, *i - 1, comm, type);
	// 			return (0);
	// 		}
	// 		if (vars->read[*i] == '\0' || (ft_isspace(vars->read[*i]) && check == 1) || (ft_isspace(vars->read[*i + 1]) && check == 1)
	// 			|| vars->read[*i + 1] == '\0')
	// 		{
	// 			check = 0;//"a">a
	// 			if (ft_token(vars, *i, comm, type) == -1)
	// 			{
	// 				printf("asd\n");
	// 				ft_error(comm);
	// 				return (-1);
	// 			}
	// 			if (vars->read[*i] != '\0')
	// 				(*i)++;
	// 			break ;
	// 		 }
	// 	}
	// }
	// while (vars->read[*i])
	// {
		while (vars->read[*i])
		{
			if (vars->read[*i] != '$' && ft_isquotes(vars->read[*i]) == 0)
			{
				temp[0] = vars->read[*i];
				str_tmp = ft_strjoin(str_tmp, temp);
				// (*i)++;
			}
			else if (vars->read[*i] == '$')
			{
				a = (*i)++;
				if (ft_isdigit(vars->read[*i]) || vars->read[*i] == 34)
					(*i)++;
				if (vars->read[*i] == '$')
				{
					int temp = *i - 1;
					d = ft_count_dollar(vars->read, &temp);
					(*i) = temp - 1;
					temp2 = ft_substr(vars->read, a, d);
					str_tmp = ft_strjoin(str_tmp, temp2);
					(*i)++;
				}
				if (vars->read[*i] == '_' || (ft_isalpha(vars->read[*i]) && !ft_isquotes(vars->read[*i - 1])) || (ft_isdigit(vars->read[*i]) && !ft_isquotes(vars->read[*i - 1])))
				{
					d = (*i);
					while (vars->read[*i] == '_' || ft_isalpha(vars->read[*i]) || ft_isdigit(vars->read[*i]))
						(*i)++;
					// ft_expanding();
					printf("expand");
				}

			}
			// else if (vars->read[*i] == 39)
			// {
			// 	(*i)++;
			// 	while (vars->read[*i] != 39)
			// 	{
			// 		temp[0] = vars->read[*i];
			// 		str_tmp = ft_strjoin(str_tmp, temp);
			// 	}
			// }
			// else if (vars->read[*i] == 34)
			// {
			// 	(*i)++;
			// 	if (ft_isalpha(vars->read[*i]))
			// 	{
			// 		while (ft_isalpha(vars->read[*i]))
			// 		{
			// 			temp[0] = vars->read[*i];
			// 			str_tmp = ft_strjoin(str_tmp, temp);
			// 			(*i)++;
			// 		}
			// 	}
			// }
			(*i)++;
		}
		printf("%s\n", str_tmp);
		return (0);
}
