#include "../../inc/minshell.h"

void ft_exit(int status)
{
    rl_clear_history();
    exit(status);
}