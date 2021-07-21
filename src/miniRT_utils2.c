#include "miniRT.h"

void	create_plane(t_vars *vars, int x, int y)
{
	t_coordinates	vector_point;
	t_coordinates	result;

	result = rotate_vector_v1(coordinates(0, 1, 0), vars);
	vector_point = norm_vector_obj(x, y, vars);
	ft_lstadd_back(&vars->obj, new_plane(vars->obj, (t_param_obj){
			coordinates_point(vars->current_camera->xyz, vector_point,
				calc_length_to_canva(vars->current_camera->size1, vars->canva.x)
				* 5), coordinates(0, 0, 0), coordinates(0, 0, 0),
			result, 0, 0, vars->canva.obj_color}, vars));
}

void	create_light(t_vars *vars, int x, int y)
{
	t_coordinates	vector_point;

	vector_point = norm_vector_obj(x, y, vars);
	ft_lstadd_back(&vars->obj, new_light(vars->obj, (t_param_obj){
			coordinates_point(vars->current_camera->xyz, vector_point,
				calc_length_to_canva(vars->current_camera->size1, vars->canva.x)
				* 2), coordinates(0, 0, 0), coordinates(0, 0, 0),
			coordinates(0, 0, 0), 0.5, 0, vars->canva.obj_color}, vars));
}

void	free_vars(t_vars *vars)
{
	if (vars->need_free)
	{
		ft_lstclear(&vars->obj, free);
		vars->need_free = 0;
	}
	if (vars->need_free_win)
	{
		mlx_destroy_image(vars->mlx, vars->img);
		if (!vars->bmp)
			mlx_destroy_window(vars->mlx, vars->win);
		vars->need_free_win = 0;
	}
}

int	read_param(char *arg, const char *param)
{
	if (ft_strncmp(arg, param, ft_strlen(param) + 1) == 0)
		return (1);
	return (0);
}
