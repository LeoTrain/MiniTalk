CC = cc
FLAGS = -Wall -Wextra -Werror
SRV_SRC = server.c
CLI_SRC = client.c
SRV_BIN = server
CLI_BIN = client
LIBFT=libft/libft.a

all: $(LIBFT) $(SRV_BIN) $(CLI_BIN)

$(LIBFT):
	@make -C libft

$(SRV_BIN): $(SRV_SRC) $(LIBFT) minitalk.h
	$(CC) $(FLAGS) $(SRV_SRC) minitalk_utils.c -Llibft -lft -o $(SRV_BIN)

$(CLI_BIN): $(CLI_SRC) $(LIBFT) minitalk.h
	$(CC) $(FLAGS) $(CLI_SRC) minitalk_utils.c -Llibft -lft -o $(CLI_BIN)

clean:
	rm -f $(SRV_BIN) $(CLI_BIN)
	@make -C libft clean

fclean: clean
	@make -C libft fclean

re: fclean all

rs: $(SRV_BIN)
	@clear
	./$(SRV_BIN)

t: $(CLI_BIN)
	@clear
	./$(CLI_BIN) $(PID) $(MSG)
