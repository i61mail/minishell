/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 05:38:21 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/28 10:19:36 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_put_error(char *before, char *sep, char *after)
{
	ft_putstr_fd(before, 2);
	ft_putstr_fd(sep, 2);
	ft_putstr_fd(after, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

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

void	ft_free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
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

t_list	*ft_dup_comm(t_list *comm)
{
	t_list	*new_comm;
	int		i;
	char	**splitd;

	new_comm = NULL;
	while (comm)
	{
		i = 0;
		if (comm->type != SPLITED)
			ft_lstadd_back(&new_comm,
				ft_lstnew(ft_strdup(comm->content), comm->type));
		else
		{
			splitd = ft_split_space(comm->content);
			while (splitd && splitd[i])
			{
				ft_lstadd_back(&new_comm, ft_lstnew(ft_strdup(splitd[i]), 0));
				i++;
			}
			ft_free_2d_array(splitd);
		}
		comm = comm->next;
	}
	ft_lstfree(&comm);
	return (new_comm);
}
