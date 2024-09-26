/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:11:35 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/26 10:28:39 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_heredoc
{
	char	*value;
	char	*expand;
	char	*here_line;
	char	*file_name;
	pid_t	return_fork;
	int		child_status;
	int		parrent_status;
	int		len;
	int		start;
	int		fd;
	int		passed_fd;
}		t_heredoc;

typedef struct s_vars
{
	char			*read;
	int				catsh;
	int				befor_sing;
	int				quoted;
	int				exit_status;
	int				del_type;
	char			*token;
	int				pfd[2];
	int				old_fd;
	int				pipe;
	int				numofpipes;
	int				bef_spac;
	int				len;
	int				start;
	int				heredoc_fd;
	int				flag_splite;
	int				builtin;
	int				cmd_num;
	int				cd;
	struct termios	reset;
	int				atoifail;
	char			*befor;
	int				befo_qu;
	int				check_ambiguous;
	int				inside;
	int				env_i;
	int				is_signal;
}		t_vars;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				catsh;
	struct s_env	*next;
}		t_env;

typedef struct s_list
{
	char			*content;
	int				type;
	struct s_list	*next;
}		t_list;

typedef struct s_args
{
	t_vars	*vars;
	int		*i;
	char	**str_temp;
}			t_args;

typedef enum s_token
{
	COMM,
	RED_IN,
	RED_OUT,
	RED_APPEND,
	HEREDOC,
	PIP,
	HEREDOC_DEL_Q,
	HEREDOC_DEL_U,
	AMBIGUOUS,
	SPLITED
}		t_token;

/*              utils  linked list       */

t_list		*ft_lstnew(void *content, int type);
void		ft_lstadd_front(t_list **lst, t_list *new);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstfree(t_list **comm);
void		free_all(char *read, t_list **comm, t_env **envir);

/*       is what  */

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			single_quo(t_vars *vars, int *i, char **str_temp);
int			ft_arequotes(t_vars *vars, int *i, t_list **comm, t_env **envir);
int			ft_aresep(t_vars *vars, int *i, t_list **comm, t_env **envir);
int			ft_isquotes(int c);
int			ft_isspace(int c);
int			ft_arespace(t_vars *vars, int *i);
int			ft_arealpha(t_vars *vars, int *i, t_list **comm, t_env **envir);
int			ft_issep(int c);
int			quotes(t_vars *vars, int *i, t_list **comm, t_env **envir);
int			count_dollar(char *str, int *i);
int			double_quo(t_vars *vars, int *i, char **str_temp, t_env **envir);
int			dollar(t_vars *vars, int *i, char **str_temp, t_env **envir);
void		replace_expand(char *str_temp, t_list **comm, int type);
int			expanding(t_vars *vars, int *i, char **str_temp, t_env **envir);
int			dollar_quotes(t_vars *vars, int *i, char **str_temp, t_env **envir);
int			just_alpha(t_vars *vars, int *i, char **str_temp, t_env **envir);
int			before_quotes(t_vars *vars, int *i, char **str_temp, t_env **envir);
void		skip_digit(t_vars *vars, int *i, int *check);
int			ft_dollar(t_vars *vars, int *i, char **str_temp, t_env **envir);
int			append_dollar2(t_vars *vars, int *i, char **temp, t_env **envir);
int			join_afterdollar(t_vars *vars, int *i, char **str_temp);
int			address_quote(t_vars *vars, int *i, char **str_temp, t_env **envir);
int			append_dollar(t_vars *vars, int *i, char **temp, t_env **envir);
int			ft_aresep3(t_vars *vars, int *i, int type, t_list **comm);
int			ft_aresep2(t_vars *vars, int *i, int type, t_list **comm);
int			process_heredoc(t_vars *vars, t_env **envir);
int			heredoc_delimiter(t_vars *vars, int *i, t_list **comm);
int			ft_isprint(int c);
int			add_to_node(char *key, char *value, t_env **envir);
char		*ft_strstr(char *str, char *to_find, int *b);
int			sspace(char *str_temp);

/*        utils       */

int			ft_strlen(char *str);
char		*ft_substr(char *s, int start, int len);
char		*ft_strdup(char *s1);
char		*ft_strnjoin(char *s1, char *s2, size_t n);
char		*ft_strjoin(char *s1, char *s2);
void		*ft_memset(void *b, int c, size_t len);
char		*ft_strncpy(char *dst, char *src, int n);
char		**ft_split_space(char *s);
char		**ft_split_char(char *s, char c);
void		ft_putstr_fd(char *str, int fd);
void		ft_putchar_fd(char c, int fd);
int			ft_strcmp(char *s1, char *s2);
long long	ft_atoi(char *str);
long long	ft_atoi_2(char *str, t_vars *vars);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strchr(const char *str, int c);
char		*ft_itoa(int nbr);
void		ft_putnbr_fd(int n, int fd);
void		handle_ctrlc(int sig);
int			ft_catch(int type, int value);
void		add_to_temp(char **str_temp, int *i, char *read);
int			handle_dollar(t_args *args, t_env **envir, t_list **comm);
int			returning(t_vars *vars, int *i, t_list **comm);
void		init_v(int *check, char **temp);
int			double_pointer(char **str);
int			check_space(char *str);
void		check_splited(t_vars *vars, int *i, int *type);
void		split_before_quotes(t_vars *vars, char **str_temp,
				t_list **comm, int *i);

/*    utils check*/

int			even_odd(char *read);
int			ft_redircmp(char *s1, char *s2, int *i);
void		ft_error(t_list **comm, t_vars *vars);
int			ft_check_type(char *read, int *i, int *type);
int			ft_pipe(t_vars *vars, int *i, t_list **comm);
int			ft_append(t_vars *vars, int *i, t_list **comm);
int			ft_heredoc(t_vars *vars, int *i, t_list **comm);
int			ft_redirec(t_vars *vars, int *i, t_list **comm, char c);
int			ft_token(t_vars *vars, int i, t_list **comm, int type);
int			after_skip(char *str, int i, char c);

/*        env        */
int			strcpy_env(t_env **envir, char **env);
t_env		*ft_lstenv(char *key, char *value);
void		ft_lstenvadd_back(t_env **lst, t_env *new);
t_env		*ft_lstenvlast(t_env *lst);
void		ft_env_free(t_env **env);
int			extra_vars(char *key, char *value, t_env **envir);
int			add_to_node(char *key, char *value, t_env **envir);

/*       execution      */
void		ft_execute(t_vars *vars, t_list *comm, t_env **envir);

/*        builtins        */
int			ft_echo(t_list *command, t_vars *vars);
int			ft_cd(t_vars *vars, t_list *comm, t_env **envir);
int			ft_pwd(t_vars *vars, t_env **envir);
int			ft_exit(t_list *comm, t_vars *vars);
int			ft_export(t_env *envir, t_vars *vars, t_list *command);
void		ft_env(t_env *envir, t_vars *vars);
void		ft_unset(t_list *command, t_env **envir, t_vars *vars);

/* 		  exec utils	*/
int			ft_env_length(t_env *envir);
int			ft_comm_length(t_list *comm);
int			ft_pipe_num(t_list *comm);
void		dup_and_close(int oldfd, int newfd);
char		*ft_locate_bin(char *command, char *path);
char		**ft_2denv(t_env *envir);
char		**ft_2dcomm(t_list *comm);
t_list		*ft_split_pipe(t_list **new_comm, t_vars *vars);
int			ft_split_2(const char *str, const char *sep, char **k, char **v);
int			ft_isred(int t);
int			ft_put_error(char *before, char *sep, char *after);
char		*ft_strchr_2(const char *str, const char *sep);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		ft_free_2d_array(char **array);
t_list		*ft_dup_comm(t_list *comm);
int			ft_is_builtin(char *command);
char		*my_getenv(char *str, t_env *envir);
void		ft_builtin(t_list *comm, t_env **envir, t_vars *vars);
t_list		*ft_check4red(t_list *comm, t_vars *vars);
int			ft_handle_redir(t_list *node, t_list *next_node, t_vars *vars);
int			ft_file_err(char *binary, t_vars *vars);

/*		export utils 	*/
int			ft_strcmp_(char *s1, char *s2, char end);
int			ft_invalid_char(char *kandv, t_vars *vars);
int			ft_var_type(char *var);
void		ft_handle_split(t_list *comm, t_env **envir, t_vars *vars);
void		ft_handle_default(t_list *comm, t_env **envir);
void		ft_add_env(char *key, char *value, t_env **envir, int type);
void		ft_dump_env(t_env *envir, t_vars *vars);
char		**ft_sort_env(char **envir);
void		ft_print_env(t_env *envir, t_vars *vars);
char		**ft_2envkeys(t_env *envir);

#endif