CC = cc
RDLPATH=$(shell brew --prefix readline)
CFLAGS = -Wall -Werror -Wextra -g  -I $(RDLPATH)/include

TARGET = minishell

EXEC_MAN =	./execution/ft_execute.c ./execution/ft_execute2.c ./execution/builtins/ft_echo.c ./execution/builtins/ft_cd.c  \
	./execution/builtins/ft_pwd.c ./execution/builtins/ft_exit.c ./execution/utils/ft_exec_utils.c \
	./execution/builtins/ft_export.c ./execution/builtins/ft_env.c ./execution/builtins/ft_unset.c \
	./execution/utils/ft_exec_utils1.c ./execution/utils/ft_exec_utils2.c ./execution/utils/ft_export_utils.c \
	./execution/utils/ft_export_utils1.c ./execution/utils/ft_exec_utils3.c ./execution/utils/ft_exec_utils4.c \
	./execution/utils/ft_cd_utils.c ./execution/utils/ft_red_utils.c ./execution/utils/ft_exec_utils5.c \
	./execution/utils/ft_cd_utils1.c ./execution/utils/ft_cd_utils2.c ./execution/utils/ft_cd_utils3.c

SRC_MAN =  $(EXEC_MAN)  main.c utils/list_utils.c utils/libft/func.c utils/libft/func1.c utils/libft/func2.c\
	utils/libft/func3.c utils/libft/func4.c utils/libft/func5.c main2.c utils/init_vars.c \
	utils/token.c utils/ft_iswhat.c utils/alpha.c utils/libft/func6.c utils/shell_level.c \
	utils/sep_syntax.c parsing/env.c utils/quotes.c parsing/env_utils.c utils/quote_utils.c \
	utils/expanding.c utils/dollar.c utils/quote_utils2.c utils/alpha2.c utils/alpha3.c\
	utils/separator.c utils/quote_utils3.c parsing/env_utils2.c \
	utils/heredoc/heredoc.c utils/heredoc/heredoc_filename.c utils/heredoc/heredoc_delimiter.c \
	utils/heredoc/heredoc_expansion.c utils/heredoc/heredoc_expansion2.c utils/heredoc/heredoc_expansion3.c \

OBJ_MAN = ${SRC_MAN:.c=.o}

%.o : %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@ 

all : $(TARGET)

$(TARGET) : $(OBJ_MAN) 
	$(CC) $(CFLAGS) $(OBJ_MAN) -o $(TARGET) -lreadline -L  $(RDLPATH)/lib

clean :
	rm -f $(OBJ_MAN)

fclean : clean
	rm -f $(TARGET)

re : fclean $(TARGET)


