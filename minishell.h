#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}   t_list;

typedef enum s_token
{
	TK_COMMAND,
	TK_SPACE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_REDIR_APPEND,
	TK_REDIR_FILE,
	TK_PIPE
}	t_token;

/*              utils  linked list       */

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));


/*             utils  main         */

int		ft_strlen(char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	*ft_substr(char *s, int start, int	len);
char	*ft_strdup(char *s1);
int		ft_isspace(int c);
int		ft_issep(int c);
void	ft_lstfree(t_list **comm);
int		ft_isquotes(int c);
int		ft_isdouble(char *read, int *i);
int		ft_issingle(char *read, int *i);
int		even_odd(char *read, bool what);

#endif