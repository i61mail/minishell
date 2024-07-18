CC = cc

CFLAGS = -Wall -Werror -Wextra

TARGET = minishell

SRC_MAN = mandatory/main.c

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
