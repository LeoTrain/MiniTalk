CC = cc
FLAGS = -Wall -Wextra -Werror
SRV_SRC = server.c
CLI_SRC = client.c
SRV_BIN = server
CLI_BIN = client

all: $(SRV_BIN) $(CLI_BIN)

$(SRV_BIN): $(SRV_SRC)
	$(CC) $(FLAGS) $(SRV_SRC) -o $(SRV_BIN)

$(CLI_BIN): $(CLI_SRC)
	$(CC) $(FLAGS) $(CLI_SRC) -o $(CLI_BIN)

clean:
	rm -f $(SRV_BIN) $(CLI_BIN)

fclean: clean

re: fclean all

rs: $(SRV_BIN)
	@clear
	./$(SRV_BIN)

t: $(CLI_BIN)
	@clear
	./$(CLI_BIN) $(PID) $(MSG)
