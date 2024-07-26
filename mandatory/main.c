#include "../minishell.h"

int	ft_token(t_vars *vars, int i, t_list **comm, int type)
{
	char *token;
	t_list *current;

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
		printf("%s      &&    %d\n", (char *)(*comm)->content, (*comm)->type);
		*comm = (*comm)->next;
	}
	return (0);
}

int main(int ac, char **av)
{
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
