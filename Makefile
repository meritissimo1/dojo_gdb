NAME = jujubs

SRCS = lab_dojo3.c

OBJS = $(SRCS:%.c=%.o)

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	clang $(OBJS) src/rand3.o $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

$(OBJS): $(SRCS)
	clang -g3 -c src/rand3.c $< -o $@

clean:
	@make -C libft clean
	@rm -rf $(OBJS)

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME)

re: fclean all
