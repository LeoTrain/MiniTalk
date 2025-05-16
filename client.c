#include "libft/libft.h"
#include "minitalk.h"

int	check_pid(char *arg)
{
	int	server_pid;

	server_pid = ft_atoi(arg);
	if (server_pid <= 0)
	{
		write(2, "Error: invalid PID.\n", 21);
		return (1);
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (argc != 3)
	{
		write(2, "Error: format->./client <PID> <MSG>\n", 36);
		return (1);
	}
	if (check_pid(argv[1]))
		return (1);
	return (0);
}

int main(int argc, char **argv)
{
	char	*msg;
	int		server_pid;

	if (check_args(argc, argv))
		return (1);
	server_pid = ft_atoi(argv[1]);
	msg = argv[2];
	send_message(server_pid, msg);
	return 0;
}

