#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>

static int byte_read = 0;

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

void	signal_handler(int sig)
{
	static char	*byte = NULL;

	if (!byte)
	{
		byte = (char *)calloc(9, sizeof(char));
		if (!byte)
			return ;
	}
	if (byte_read < 8)
	{
		if (sig == SIGUSR1)
		{
			byte[byte_read] = '0';
		}
		else if (sig == SIGUSR2)
		{
			byte[byte_read] = '1';
		}
		byte_read++;
	}
	if (byte_read == 8)
	{
		char ch = byte_to_char(byte);
		if (ch != '\0')
			write(1, &ch, 1);
		else
			write(1, "\n", 1);
		byte_read = 0;
		free(byte);
		byte = NULL;
	}
}

int main()
{
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	printf("MY PID: %d\n", getpid());
	while (1);
}
