NAME = philo
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
INCLUDE = includes/
OBJ_DIR = obj/

SRC = src/memory_manage/allocator.c src/memory_manage/init.c src/memory_manage/terminate.c \
      src/parser/parser.c src/parser/parser_utils.c \
      src/philo/monitoring.c src/philo/philo.c src/philo/routine.c \
      src/threads/threads.c \
      src/utils/time.c src/utils/utils.c

OBJ = $(SRC:src/%.c=$(OBJ_DIR)%.o)

$(OBJ_DIR)%.o: src/%.c Makefile includes/philo.h
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -I $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
