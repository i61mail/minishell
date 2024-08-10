/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:54:35 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/10 09:10:54 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(t_list **comm)
{
	ft_putstr("minishell: syntax error\n", 2);
	ft_lstfree(comm);
	return ;
}

int	ft_check_type(char *read, int *i, int *type)
{
	int	c;

	c = *i;
	if (read[c] == '|')
		*type = PIP;
	else if (ft_redircmp(read, ">>", i) == 1)
		*type = RED_APPEND;
	else if (ft_redircmp(read, "<<", i) == 1)
		*type = HEREDOC;
	else if (read[c] == '<')
		*type = RED_IN;
	else if (read[c] == '>')
		*type = RED_OUT;
	else
		return (-1);
	return (0);
}

int	skip_space(char *str, char c, int red)
{
	int	i;

	i = 0;
	(void)red;
	(void)c;
	while (ft_isspace(str[i]))
		i++;
	return (0);
}

int	after_skip(char *str, int i, int red)
{
	(void)red;
	while (ft_isspace(str[i]))
	{
		i++;
	}
	if (str[i] == '\0')
		return (-1);
	if (ft_issep(str[i]) && str[i] != '<')
	{
		i++;
		after_skip(str, i, red);
	}
	return (0);
}
