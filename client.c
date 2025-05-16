#include "minitalk.h"
#include <stdlib.h>


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
	server_pid = ft_atoi(argv[1]);
	msg = argv[2];
	send_message(server_pid, msg);
	return 0;
}

