#include "../include/errors.h"
#include "../include/builtins.h"

int	error_allocation(void)
{
	ft_putendl_fd("minishell: Cannot allocate memory",2);
	return (-1);
}
// int	wrong_export_sintax(char *inpt)
// {
// 	ft_putstr_fd("minishell: export: `", 2);
// 	ft_putstr_fd(inpt, 2);
// 	ft_putstr_fd ("': not a valid identifier\n", 2);
// 	return (0);
// }