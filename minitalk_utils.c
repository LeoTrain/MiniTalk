#include "minitalk.h"

char	byte_to_char(char *byte)
{
	int		i;
	int		pow;
	char	result;

	result = 0;
	pow = 1;
	i = 7;
	while (i >= 0)
	{
		if (byte[i] == '1')
			result += pow;
		pow *= 2;
		i--;
	}
	return ((char)result);
}

char	*char_to_byte(char c)
{
	char			*byte;
	unsigned char	a;
	int				i;
	int				pow;

	byte = (char *)ft_calloc(9, sizeof(char));
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

void send_char(int server_pid, char c)
{
	char	*byte;
	char	*tmp;
	int		signal;

	byte = char_to_byte(c);
	if (!byte)
		return ;
	tmp = byte;
	while (*tmp)
	{
		if (*tmp == '0')
			signal = SIGUSR1;
		else if (*tmp == '1')
			signal = SIGUSR2;
		if (kill(server_pid, signal) == -1)
		{
			free(byte);
			exit(EXIT_FAILURE);
		}
		tmp++;
		usleep(100);
	}
	free(byte);
}

void	send_message(int pid, char *msg)
{
	while (*msg)
		send_char(pid, *msg++);
	send_char(pid, '\0');
}

