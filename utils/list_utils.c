/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:55:38 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/02 16:56:47 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(void *content, int type)
{
	t_list	*temp;

	temp = (t_list *)malloc(sizeof(t_list));
	if (!temp)
		return (NULL);
	temp->content = content;
	temp->type = type;
	temp->next = NULL;
	return (temp);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstfree(t_list **comm)
{
	t_list	*curr;
	t_list	*temp;

	if (!comm)
		return ;
	curr = *comm;
	while (curr)
	{
		temp = curr->next;
		free(curr);
		curr = temp;
	}
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	*ft_strnjoin(char *s1, char *s2, size_t n)
{
	char	*s;
	size_t	i;
	size_t	len;

	i = 0;
	if (!s1)
		return (ft_strdup(s2));
	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (free(s1), NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	len = ft_strlen(s);
	i = 0;
	while (s2[i] && i < n)
	{
		s[len++] = s2[i];
		i++;
	}
	s[len] = '\0';
	return (free(s1), s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len;
	int		i;

	i = 0;
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (free(s1), NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	i = 0;
	len = ft_strlen(str);
	while (s2[i])
		str[len++] = s2[i++];
	str[len] = '\0';
	return (free(s1), str);
}

void	*ft_memset(void *b, int c, size_t len)
{
	char	*s;

	s = (char *)b;
	while (len > 0)
	{
		*s = (unsigned char)c;
		s++;
		len--;
	}
	return (b);
}
