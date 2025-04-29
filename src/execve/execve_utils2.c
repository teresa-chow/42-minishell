

#include "../../include/builtins.h"
#include "../../include/execve.h"
#include "../../include/errors.h"

void	free_failed_child(t_exec_data *inf, t_data *data)
{
	free_arrays(inf, data, 0);
	free_env_list(data, 0, &data->env);
	free_ast(&data->ast_root);
}