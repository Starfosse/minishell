NAME = minishell

SRC = main.c get_next_line.c get_next_line_utils.c exec_commands.c builts_in.c check_args.c built_in_pwd.c built_in_echo.c built_in_cd.c built_in_env.c build_in_unset.c build_in_export.c build_in_exit.c pipes.c redir.c signals.c env.c prompt.c utils.c choose_fd.c single_cmd.c multiple_cmd.c parsing.c parsing2.c custom_split.c check_syntax.c

OBJ = main.o get_next_line.o get_next_line_utils.o exec_commands.o builts_in.o check_args.o built_in_pwd.o built_in_echo.o built_in_cd.o built_in_env.o build_in_unset.o build_in_export.o build_in_exit.o pipes.o redir.o signals.o env.o prompt.o utils.o choose_fd.o single_cmd.o multiple_cmd.o parsing.o parsing2.o custom_split.o check_syntax.o
	
CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME) :
		make -C libft/
		make bonus -C libft/
		$(CC) $(CFLAGS) -c $(SRC)
		gcc -o $(NAME) $(OBJ) -lreadline libft/libft.a
clean:
		$(RM) $(OBJ) 
		$(RM) $(BONUS_OBJ) 
		make -C libft/ clean

fclean: clean
		$(RM) $(NAME)
		make -C libft/ fclean

re: fclean all
		make -C libft/ re