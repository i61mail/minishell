#include "../minishell.h"

int	ft_tocken(t_vars *vars, int i, t_list **comm, int type)
{
	char *tocken;
	t_list *current;

	tocken = ft_substr(vars->read, vars->catsh, i - vars->catsh);
	  if (!tocken)
		return (-1);
	current = ft_lstnew(tocken, type);
	ft_lstadd_back(comm, current);
	// printf("%s    &&     %d\n", current->content, current->type);
	if (!*comm)
	{
		free(tocken);
		return (-1);
	}
	return (0);
}

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
	if (ft_tocken(vars, *i, comm, COMM) == -1)
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

// int ft_aresep(t_vars *vars, int *i, t_list **comm)
// {
// 	int	type;
// 	int	check;

// 	check = 0;
// 	vars->catsh = *i;
// 	if ((vars->read[*i] == '|' && *i == 0) || (vars->read[*i] == '|' && ft_issep(vars->read[*i + 1]))
// 	|| (ft_issep(vars->read[*i]) && ((vars->read[*i + 1] == '\0' && vars->read[*i] != '|'))))
// 	{
// 		while (ft_isspace(vars->read[*i + 1]))
// 			(*i)++;
// 		if (!ft_isalpha(vars->read[*i + 1]))
// 		{
// 			printf("ismail: 1syntax error near unexpected token `|'\n");
// 			return (-1);
// 		}
// 	}
// 	//ft_issep(vars->read[*i]) && ft_issep(vars->read[*i + 2])
// 	while (vars->read[*i])
// 	{
// 		if (ft_issep(vars->read[*i]))
// 		{
// 			check += 1;
// 			(*i)++;
// 		}
// 		if (check >= 2 && ft_issep(vars->read[*i]))
// 		{
// 			printf("ismail: 2syntax error near unexpected token `|'\n");
// 			return (-1);
// 		}
// 		else
// 			break ;
// 	}
// 		printf("--%d\n", *i);
// 	ft_check_type(vars->read, i, &type);
// 		printf("++%d\n", *i);
// 	if (type == 5 || type == 4)
// 	{
// 		printf("**%d\n", *i);
// 		while (ft_isspace(vars->read[*i + 1]))
// 			(*i)++;
// 		if (ft_issep(vars->read[*i + 1]))
// 		{
// 			printf("ismail: 3syntax error near unexpected token `|'\n");
// 			return (-1);
// 		}
// 		else if (!ft_issep(vars->read[*i + 1]) && )
// 	}
// 	printf("//%d\n", *i);
// 	// if (vars->read[*i] == '\0')
// 	// {
// 	// 	printf("ismail : 3syntax error near unexpected token `|'\n");
// 	// 	ft_lstfree(comm);
// 	// 	return (comm = NULL, -1);
// 	// }
// 	if (ft_tocken(vars, *i, comm, type) == -1)
// 		return (-1);
// 	return (0);
// }


int ft_aresep(t_vars *vars, int *i, t_list **comm)
{
	int	type;

	type = 0;
	(void)comm;
	ft_check_type(vars->read, i, &type);
	// printf("type == %d\n", type);
	if (type == 6) //pipe
	{
		vars->catsh = *i;
		if (ft_pipe(vars, i) == -1)
			return (-1);
	}
	else if (type == 4) //append >>
	{
		printf("----%d\n", *i);
		vars->catsh = *i;
		if (ft_append(vars, i, true) == -1)
			return (-1);
	}
	// else if (type == 4) // heredoc <<
	// {

	// }
	// else if (type == 2 || type == 1) //redirection '<' && '>'
	// {

	// }
	printf("++++%d\n", *i);
	ft_tocken(vars, *i, comm, type);
	return (0);
}

int    ft_pars_comm(t_vars *vars, t_list **comm)
{
	int i;
	// int check;

	i = 0;
	while (vars->read[i] != '\0')
	{
		if (!ft_issep(vars->read[i]) && !ft_isspace(vars->read[i]) && !ft_isquotes(vars->read[i]))
			ft_arealpha(vars, &i, comm);
		else if (ft_isspace(vars->read[i]))
			ft_arespace(vars->read, &i);
		else if (ft_issep(vars->read[i]))
		{
			if (ft_aresep(vars, &i, comm) == -1)
				return (-1);
		}
		// else if (ft_isquotes(read[i]))
		// {
		// 	// printf("is quotes\n");
		// 	if (read[i] == 34)
		// 	{
		// 		check = even_odd(read, true);
		// 		if (check == 0)
		// 		{
		// 			printf("error\n");
		// 			return (-1);
		// 		}
		// 		ft_isdouble(read, &i);
		// 		check = 0;
		// 	}
		// 	check = even_odd(read, false);
		// 	if (check == 0)
		// 	{
		// 		printf("error\n");
		// 		return (-1);
		// 	}
		// 	ft_issingle(read, &i);
		// }
		// else
		// {
		// 	printf("error\n");
		// 	return (-1);
		// }
	}
	while (*comm)
	{
		printf("%s      &&    %d\n", (*comm)->content, (*comm)->type);
		// printf("%d\n", (*comm)->type);
		*comm = (*comm)->next;
	}
	return (0);
}

int main(int ac, char **av)
{
	// char *read;
	t_list  *comm;
	t_vars	vars;
	(void)av;

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
