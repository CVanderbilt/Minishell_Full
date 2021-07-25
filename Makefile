NAME=minishell

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

LDFLAGS=-ltermcap

GLFLAGS=-lreadline

LDLIBS=-lft

HDDIRS=-I includes/ 

SRC= checker.c cmd1.c cmd2.c arg_counter.c \
	cd.c exec.c functions1.c functions2.c \
	minishell.c parser.c init_shell.c\
	redirections1.c redirections2.c reset.c redirects.c \
	utils1.c utils2.c minierrors.c get_var.c quotes.c \
	piped_exec.c env_set1.c env_set2.c env_set3.c simple_checks.c

GNL= kt_functions.c line_edition1.c line_edition2.c main_simple.c \
	utils.c sig_handler.c motion.c ask_cursor_pos.c motion2.c\
	kt_history.c kt_eol.c kt_del.c kt_print.c kt_move_unrec.c

LIB= ultra_str0.c ultra_str1.c ultra_str2.c ultra_io0.c\
	get_next_line.c frees.c log.c checks.c

SRCS= $(SRC) $(GNL) $(LIB)

SRCSC= $(addprefix src/, $(SRC)) \
	$(addprefix extras/noncanon_gnl/, $(GNL)) \
	$(addprefix extras/ultimate_libft/, $(LIB))

OBJ=$(SRCS:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(LDFLAGS) $(GLFLAGS) $(OBJ)

$(OBJ):
	$(CC) -c $(HDDIRS) $(SRCSC)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all bonus