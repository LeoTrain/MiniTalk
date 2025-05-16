#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	*char_to_byte(char c)
{
	char	*byte;
	int		a;
	int		i;

	byte = (char *)calloc(9, sizeof(char));
	if (!byte)
		return (NULL);
	a = c;
	i = 0
	while (a > 0)
	{
		byte[i++] = a % 2;
		a /= 2;
	}
	return (byte);
}

void send_char(pid_t server_pid, char c)
{
	char	*byte;

	byte = char_to_byte(c);
	if (!byte)
		return ;
	while (*byte)
	{
		if (*byte == '0')
			kill(server_pid, SIGUSR1);
		if (*byte == '1')
			kill(server_pid, SIGUSR2);
		byte++;
	}
}

int main(int argc, char **argv) {
	char	*msg;
	pid_t server_pid;

    if (argc != 3)
	{
        write(2, "Usage: ./client <server_pid> <message>\n", 40);
        return 1;
    }

    server_pid = (pid_t)atoi(argv[1]);
    msg = argv[2];

    while (*msg)
	{
        send_char(server_pid, *msg++);
		sleep(1);

	}
    send_char(server_pid, '\0');

    return 0;
}

