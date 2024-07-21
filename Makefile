CC = cc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

TARGET = minishell

SRC_MAN = mandatory/main.c utils/ft_lstadd_back_bonus.c utils/ft_lstclear_bonus.c utils/ft_lstiter_bonus.c \
	utils/ft_lstsize_bonus.c utils/ft_lstadd_front_bonus.c utils/ft_lstdelone_bonus.c \
	utils/ft_lstlast_bonus.c utils/ft_lstnew_bonus.c utils/ft_strlen.c utils/ft_isdigit.c \
	utils/ft_isalpha.c utils/ft_substr.c utils/ft_strdup.c utils/ft_isspace.c utils/ft_issep.c \
	utils/ft_lstfree.c utils/ft_isquotes.c utils/ft_issingle.c utils/ft_isdouble.c utils/ft_even_odd.c \
	utils/ft_redircmp.c

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
