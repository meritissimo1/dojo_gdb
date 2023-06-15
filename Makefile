NAME = debug

SRCS = lab_dojo4.c

OBJS = lab_dojo2.o

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	clang $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

$(OBJS): $(SRCS)
	clang -g3 -c $< -o $@

clean:
	@make -C libft clean
	@rm -rf $(OBJS)

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME)

re: fclean all
