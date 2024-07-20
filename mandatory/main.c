#include "../minishell.h"

int	ft_tocken(char *read, int i, int catsh, t_list **comm)
{
	char *tocken;
	t_list *current;

	tocken = ft_substr(read, catsh, i - catsh);
	  if (!tocken)
		return (-1);
	current = ft_lstnew(tocken);
	ft_lstadd_back(comm, current);
	if (!*comm)
	{
		free(tocken);
		return (-1);
	}
	return (0);
}

int    ft_arealpha(char *read, int *i, t_list **comm)
{
	int		catsh;

	catsh = *i;
	while (read[*i])
	{
		if (!ft_issep(read[*i]) && !ft_isspace(read[*i]) && !ft_isquotes(read[*i]))
			(*i)++;
		else
			break ;
	}
	if (ft_tocken(read, *i, catsh, comm) == -1)
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


int ft_aresep(char *read, int *i, t_list **comm)
{
	int catsh;

	catsh = *i;
	if (read[*i] == '|' && *i == 0)
	{
		printf("ismail: syntax error near unexpected token `|'\n");
		return (-1);
	}
	while (read[*i])
	{
		if (ft_issep(read[*i]))
			(*i)++;
		else
			break ;
	}
	if (read[*i] == '\0' || ft_issep(read[*i + 1]))
	{
		printf("ismail : syntax error near unexpected token `|'\n");
		ft_lstfree(comm);
		return (-1);
	}
	if (ft_tocken(read, *i, catsh, comm) == -1)
		return (-1);
	return (0);
}

int    ft_pars_comm(char *read, t_list **comm)
{
	int i;
	// int check;

	i = 0;
	while (read[i] != '\0')
	{
		if (!ft_issep(read[i]) && !ft_isspace(read[i]) && !ft_isquotes(read[i]))
			ft_arealpha(read, &i, comm);
		else if (ft_isspace(read[i]))
			ft_arespace(read, &i);
		else if (ft_issep(read[i]))
		{
			if (ft_aresep(read, &i, comm) == -1)
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
		printf("%s\n", (*comm)->content);
		*comm = (*comm)->next;
	}
	return (0);
}

int main(int ac, char **av)
{
	char *read;
	t_list  *comm;
	(void)av;

	while (1)
	{
		comm = NULL;
		if (ac == 1)
		{
			read = readline("minishell> ");
			if (!read)
				break ;
			add_history(read);
			ft_pars_comm(read, &comm);
		}
		else
			break ;
	}
	return (0);
}   
