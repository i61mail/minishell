/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 05:38:21 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/10 07:04:34 by mait-lah         ###   ########.fr       */
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

void	ft_free_2d_array(void **array)
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

//t_list *dup_comm(t_list *comm)
//{
//	t_list *new_comm;
//	int i ;

	
//	while(comm)
//	{
//		i = 0;
//		if(comm->type != SPLITED)
//			ft_lstadd_back(&comm, new_comm);
//		else
//		{
					
//		}
//		comm = comm->next;
//	}
//	return (new_comm);
//}
