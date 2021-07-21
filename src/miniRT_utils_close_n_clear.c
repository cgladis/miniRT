#include "miniRT.h"

int	close_w(t_vars *vars)
{
	free_vars(vars);
	exit(0);
}

void	clear_ray_tracing_data(t_ray_tracing *data)
{
	if (data->lights)
		ft_lstclear(&data->lights, free);
}
