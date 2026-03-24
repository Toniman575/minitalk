NAME_SERVER =		server
SRCS_SERVER =		server.c
OBJS_SERVER =		$(SRCS_SERVER:.c=.o)
DEPS_SERVER =		$(OBJS_SERVER:.o=.d)

NAME_CLIENT =		client
SRCS_CLIENT =		client.c
OBJS_CLIENT =		$(SRCS_CLIENT:.c=.o)
DEPS_CLIENT =		$(OBJS_CLIENT:.o=.d)

LIBFT_DIR =	./libft
LIBFT =		$(LIBFT_DIR)/libft.a
CC =		cc
CFLAGS =	-Wall -Wextra -Werror -MMD -MP -I$(LIBFT_DIR)
LDFLAGS =	-L$(LIBFT_DIR) -lft

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(LIBFT) $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LDFLAGS) -o $(NAME_SERVER)

$(NAME_CLIENT): $(LIBFT) $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LDFLAGS) -o $(NAME_CLIENT)

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

FORCE:

clean:
	rm -f $(OBJS_SERVER) $(DEPS_SERVER) $(OBJS_CLIENT) $(DEPS_CLIENT)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

debug: fclean
	$(MAKE) -C $(LIBFT_DIR) debug
	$(MAKE) all CFLAGS="$(CFLAGS) -g"

.PHONY: all clean fclean re debug FORCE

-include $(DEPS)