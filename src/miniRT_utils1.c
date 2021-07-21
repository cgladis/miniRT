#include "miniRT.h"

void	create_sphere(t_vars *vars, int x, int y)
{
	t_coordinates	vector_point;

	printf("create_sphere\n");
	vector_point = norm_vector_obj(x, y, vars);
	ft_lstadd_back(&vars->obj, new_sphere(vars->obj,
			(t_param_obj){coordinates_point(vars->current_camera->xyz,
				vector_point, calc_length_to_canva(vars->current_camera->size1,
					vars->canva.x) * 2), coordinates(0, 0, 0),
			coordinates(0, 0, 0), coordinates(0, 0, 0),
			calc_length_to_canva(vars->current_camera->size1, vars->canva.x)
			/ 2, 0, vars->canva.obj_color}, vars));
}

void	create_square(t_vars *vars, int x, int y)
{
	t_coordinates	vector_point;

	printf("create_square\n");
	vector_point = norm_vector_obj(x, y, vars);
	ft_lstadd_back(&vars->obj, new_square(vars->obj, (t_param_obj){
			coordinates_point(vars->current_camera->xyz, vector_point,
				calc_length_to_canva(vars->current_camera->size1, vars->canva.x)
				* 2), coordinates(0, 0, 0), coordinates(0, 0, 0),
			vector_point, calc_length_to_canva(vars->current_camera->size1,
				vars->canva.x) / 2, 0, vars->canva.obj_color}, vars));
}

void	create_triangle(t_vars *vars, int x, int y)
{
	t_coordinates	vector_point_1;
	t_coordinates	vector_point_2;
	t_coordinates	vector_point_3;

	printf("create_triangle\n");
	vector_point_1 = norm_vector_obj(x, y - vars->canva.y / 10, vars);
	vector_point_2 = norm_vector_obj(x - vars->canva.x / 10,
			y + vars->canva.y / 10, vars);
	vector_point_3 = norm_vector_obj(x + vars->canva.x / 10,
			y + vars->canva.y / 10, vars);
	ft_lstadd_back(&vars->obj, new_triangle(vars->obj, (t_param_obj){
			coordinates_point(vars->current_camera->xyz, vector_point_1,
				calc_length_to_canva(vars->current_camera->size1, vars->canva.x)
				* 2), coordinates_point(vars->current_camera->xyz,
				vector_point_2, calc_length_to_canva(vars->current_camera
					->size1, vars->canva.x) * 2), coordinates_point(vars
				->current_camera->xyz, vector_point_3, calc_length_to_canva(
					vars->current_camera->size1, vars->canva.x) * 2),
			coordinates(0, 0, 0), 0, 0,
			vars->canva.obj_color}, vars));
}

void	create_cylinder(t_vars *vars, int x, int y)
{
	t_coordinates	vector_point;
	t_coordinates	vector_3d;

	printf("create_cylinder\n");
	vector_point = norm_vector_obj(x, y, vars);
	vector_3d = rotate_vector_v1(coordinates(0, 1, 0), vars);
	ft_lstadd_back(&vars->obj, new_cylinder(vars->obj,
			(t_param_obj){coordinates_point(vars->current_camera->xyz,
				vector_point, calc_length_to_canva(vars->current_camera->size1,
					vars->canva.x) * 2), coordinates(0, 0, 0),
			coordinates(0, 0, 0), vector_3d,
			calc_length_to_canva(vars->current_camera->size1,
				vars->canva.x) / 2, calc_length_to_canva(vars
				->current_camera->size1, vars->canva.x) * 1.5,
			vars->canva.obj_color}, vars));
}

void	create_camera(t_vars *vars)
{
	ft_lstadd_back(&vars->obj, new_camera(vars->obj, (t_param_obj){
			vars->current_camera->xyz, coordinates(0, 0, 0),
			coordinates(0, 0, 0), vars->current_camera->vector_3d,
			vars->current_camera->size1, 0, new_color(0, 0, 0)}, vars));
	vars->current_camera = last_obj(vars->obj);
	printf("create_camera\n");
}
