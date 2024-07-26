CC = cc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

TARGET = minishell

SRC_MAN = mandatory/main.c utils/list_utils.c utils/ft_substr.c utils/ft_strdup.c utils/ft_strlen.c \
	utils/ft_even_odd.c utils/ft_redircmp.c utils/token.c utils/ft_iswhat.c utils/ft_arewhat.c \
	utils/ft_separator.c

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
