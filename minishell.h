#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_vars
{
	char *read;
	int	catsh;
}	t_vars;

typedef struct s_list
{
	void			*content;
	int				type;
	struct s_list	*next;
}   t_list;

typedef enum s_token
{
	COMM,
	SPACE,
	RED_IN,
	RED_OUT,
	RED_APPEND,
	HEREDOC,
	PIP
}	t_token;

/*              utils  linked list       */

t_list	*ft_lstnew(void *content, int type);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);


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
int		ft_redircmp(char *s1, char *s2, int *i);
void	ft_error(void);
void	ft_check_type(char *read, int *i, int *type);
int		ft_pipe(t_vars *vars, int *i);
int		ft_append(t_vars *vars, int *i, bool what);

#endif