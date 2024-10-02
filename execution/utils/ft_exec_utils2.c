/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 05:38:21 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/30 10:34:26 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_split_2(const char *str, const char *sep, char **k, char **v)
{
	char	*found_at;
	int		key_size;
	int		value_size;

	found_at = ft_strchr_2(str, sep);
	if (!found_at)
		return (-1);
	key_size = (found_at - str);
	value_size = ft_strlen(found_at + 1);
	*k = malloc(sizeof(char) * key_size + 1);
	*v = malloc(sizeof(char) * value_size + 1);
	ft_strlcpy(*k, str, key_size + 1);
	ft_strlcpy(*v, found_at + ft_strlen((char *)sep), value_size + 1);
	return (0);
}

void	ft_free_2d_array(char ***array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array && *array && (*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}

int	ft_pipe_num(t_list *comm)
{
	int	n;

	n = 0;
	while (comm)
	{
		if (comm->type == PIP)
			n++;
		comm = comm->next;
	}
	return (n);
}

void	add_back(char **splitd, int *i, t_list **new_comm)
{
	while (splitd && splitd[*i])
	{
		ft_lstadd_back(new_comm, ft_lstnew(ft_strdup(splitd[*i]), 0));
		(*i)++;
	}
}

t_list	*ft_dup_comm(t_list *comm)
{
	t_list	*new_comm;
	t_list	*tmp;
	int		i;
	char	**splitd;

	new_comm = NULL;
	tmp = comm;
	while (tmp)
	{
		i = 0;
		if (tmp->type != SPLITED)
			ft_lstadd_back(&new_comm,
				ft_lstnew(ft_strdup(tmp->content), tmp->type));
		else
		{
			splitd = ft_split_space(tmp->content);
			add_back(splitd, &i, &new_comm);
			ft_free_2d_array(&splitd);
			splitd = NULL;
		}
		tmp = tmp->next;
	}
	ft_lstfree(&comm);
	return (new_comm);
}
