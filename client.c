#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	*char_to_byte(char c)
{
	unsigned char	a;
	char			*byte;
	int				i;
	int				pow;


	byte = (char *)calloc(9, sizeof(char));
	if (!byte)
		return (NULL);
	a = (unsigned char)c;
	i = 0;
	pow = 128;
	while (i < 8)
	{
		if (a >= pow)
		{
			byte[i] = '1';
			a -= pow;
		}
		else
			byte[i] = '0';
		pow /= 2;
		i++;
	}
	byte[8] = '\0';
	printf("BYTE: %s\n", byte);
	return (byte);
}

void send_char(pid_t server_pid, char c)
{
	char	*byte;
	char	*tmp;

	byte = char_to_byte(c);
	if (!byte)
		return ;
	tmp = byte;
	while (*tmp)
	{
		if (*tmp == '0')
			kill(server_pid, SIGUSR1);
		if (*tmp == '1')
			kill(server_pid, SIGUSR2);
		tmp++;
		usleep(1);
	}
	free(byte);
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

	printf("MESSAGE TO SEND: %s\n", msg);
	while (*msg)
	{
		send_char(server_pid, *msg++);
	}
    send_char(server_pid, '\0');
    return 0;
}

