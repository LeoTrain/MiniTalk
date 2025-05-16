#include "libft/libft.h"
#include "minitalk.h"

static int byte_read = 0;

void	signal_handler(int sig)
{
	static char	byte[9];
	char		c;

	if (byte_read < 8)
	{
		if (sig == SIGUSR1)
			byte[byte_read] = '0';
		else if (sig == SIGUSR2)
			byte[byte_read] = '1';
		byte_read++;
	}
	if (byte_read == 8)
	{
		c = byte_to_char(byte);
		if (c != '\0')
			write(1, &c, 1);
		else
			write(1, "\n", 1);
		byte_read = 0;
		ft_bzero((void *)byte, sizeof(byte));
	}
}

int main()
{
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	printf("MY PID: %d\n", getpid());
	while (1);
		// pause();
	return (0);
}
