/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:03:41 by isrkik            #+#    #+#             */
/*   Updated: 2024/07/19 10:20:08 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*now;
	t_list	*next;

	if (lst == NULL || del == NULL)
		return ;
	now = *lst;
	while (now != NULL)
	{
		next = now->next;
		ft_lstdelone(now, del);
		now = next;
	}
	*lst = NULL;
}
