CC = cc

CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address

TARGET = minishell

EXEC_MAN =	./execution/ft_execute.c ./execution/builtins/ft_echo.c ./execution/builtins/ft_cd.c \
	./execution/builtins/ft_pwd.c ./execution/builtins/ft_exit.c

SRC_MAN =  $(EXEC_MAN)  main.c utils/list_utils.c utils/lib_func.c utils/lib_func2.c utils/lib_func3.c \
	utils/ft_even_odd.c utils/ft_redircmp.c utils/token.c utils/ft_iswhat.c utils/arewhat.c \
	utils/ft_separator.c parsing/env.c utils/quotes.c utils/env_utils.c utils/quote_utils.c \
	utils/lib_func4.c utils/ft_strchr.c utils/expanding.c utils/dollar.c utils/temp.c \
	utils/temp2.c

OBJ_MAN = ${SRC_MAN:.c=.o}

%.o : %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@  

all : $(TARGET)

$(TARGET) : $(OBJ_MAN)
	$(CC) $(CFLAGS) -lreadline $(OBJ_MAN) -o $(TARGET)

clean :
	rm -f $(OBJ_MAN)

fclean : clean
	rm -f $(TARGET)

re : fclean $(TARGET)
