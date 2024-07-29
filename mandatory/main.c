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
	int check;
	int	quote;

	quote = 0;
	i = 0;
	while (vars->read[i] != '\0')
	{
		if (!ft_issep(vars->read[i]) && !ft_isspace(vars->read[i]) && !ft_isquotes(vars->read[i]))
			quote = ft_arealpha(vars, &i, comm);
		else if (ft_isspace(vars->read[i]))
			ft_arespace(vars->read, &i);
		else if (ft_issep(vars->read[i]))
		{
			quote = ft_aresep(vars, &i, comm);
			if (quote == -1)
				return (-1);
		}
		else if (ft_isquotes(vars->read[i]))
		{
				check = even_odd(vars->read);
				if (check == 0)
				{
					ft_error(comm);
					return (-1);
				}
				if (quote != 2)
				{
					vars->catsh = i;
					ft_arequotes(vars, &i, comm, QUOT);
				}
				else
				{
					i = vars->catsh;
					ft_arequotes(vars, &i, comm, QUOT);
				}
		}
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
