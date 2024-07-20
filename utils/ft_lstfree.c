#include "../minishell.h"

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
