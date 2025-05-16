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

void	send_message(int pid, char *msg)
{
	while (*msg)
		send_char(pid, *msg++);
	send_char(pid, '\0');
}

void	get_user_answer(void)
{
	int		pid;
	char	*msg;

	printf("Enter a PID: ");
	scanf("%d", &pid);
	while (1)
	{
		msg = (char *)malloc(1024 * sizeof(char));
		if (!msg)
			return ;
		printf("Enter a message: ");
		scanf(" %[^\n]", msg);
		send_message(pid, msg);
	}
}

int main(int argc, char **argv)
{
	char	*msg;
	int		server_pid;

	if (argc != 3)
	{
		get_user_answer();
		return (0);
	}
	server_pid = atoi(argv[1]);
	msg = argv[2];
	send_message(server_pid, msg);
	return 0;
}

