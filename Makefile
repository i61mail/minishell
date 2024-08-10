CC = cc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

TARGET = minishell

SRC_MAN = parsing/main.c utils/list_utils.c utils/lib_func.c utils/lib_func2.c utils/lib_func3.c \
	utils/ft_even_odd.c utils/ft_redircmp.c utils/token.c utils/ft_iswhat.c utils/ft_arewhat.c \
	utils/ft_separator.c parsing/env.c utils/ft_arewhat2.c utils/env_utils.c utils/quote_utils.c \
	

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
