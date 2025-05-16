#ifndef MINITALK_H
# define MINITALK_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "libft/libft.h"

char	byte_to_char(char *byte);
char	*char_to_byte(char c);
void	send_char(int server_pid, char c);
void	send_message(int pid, char *msg);

#endif
