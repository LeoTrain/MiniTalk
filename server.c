#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
		printf("0");
	if (sig == SIGUSR2)
		printf("1");
	printf("\n");
}

int main()
{
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	printf("MY PID: %d\n", getpid());

	while (1);
}
