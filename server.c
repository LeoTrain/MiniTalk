#include "libft/libft.h"
#include "minitalk.h"
#include <unistd.h>

static int byte_read = 0;

static void	apply_byte(int sig, char *byte)
{
	if (sig == SIGUSR1)
		byte[byte_read++] = '0';
	else if (sig == SIGUSR2)
		byte[byte_read++] = '1';
}

static void	write_and_reset_byte(char *byte)
{
	char	c;

	c = byte_to_char(byte);
	if (c != '\0')
		write(1, &c, 1);
	else
		write(1, "\n", 1);
	byte_read = 0;
	ft_bzero((void *)byte, sizeof(byte));
}

void	signal_handler(int sig)
{
	static char	byte[9];

	if (byte_read < 8)
		apply_byte(sig, byte);
	if (byte_read == 8)
		write_and_reset_byte(byte);
}

int main()
{
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	ft_putstr_fd("MY PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1);
	return (0);
}
