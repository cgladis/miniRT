#include "miniRT.h"

void	trace_ray(int i, int j, t_ray_tracing *data)
{
	t_color			color;

	data->lights = NULL;
	data->ray = norm_vector_obj(i, j, data->vars);
	data->closest_obj = closest_intersection(data->vars->current_camera->xyz,
			data->ray, data, (t_t_minmax){1, INFINITY});
	if (data->closest_obj.obj == NULL)
	{
		my_mlx_pixel_put(data->vars, i, j,
			data->vars->canva.background_color.color);
		return ;
	}
	color = get_color(data->closest_obj.closest_t, data->ray,
			data->closest_obj.obj, data);
	my_mlx_pixel_put(data->vars, i, j, color.color);
}

void	*pthread_trace(void *input_data)
{
	int						i;
	int						j;
	t_ray_tracing			*data;

	data = input_data;
	i = data->k;
	while (i < data->vars->canva.y)
	{
		j = 0;
		while (j < data->vars->canva.x)
		{
			data->x = j;
			data->y = i;
			trace_ray(j, i, data);
			clear_ray_tracing_data(data);
			j++;
		}
		i += NUM_PTHREAD;
	}
	return (NULL);
}

void	draw_obj(t_vars *vars)
{
	int						i;
	t_ray_tracing			data[NUM_PTHREAD];
	pthread_t				tid[NUM_PTHREAD];

	i = 0;
	while (i < NUM_PTHREAD)
	{
		data[i].k = i;
		data[i].vars = vars;
		pthread_create(&tid[i], NULL, pthread_trace, (void *)&data[i]);
		i++;
	}
	while (i--)
		pthread_join(tid[i], NULL);
	if (!vars->bmp)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

void	draw_obj_light(t_vars *vars)
{
	int				i;
	int				j;
	t_ray_tracing	data;

	i = 0;
	data.vars = vars;
	while (i < vars->canva.x)
	{
		j = 0;
		while (j < vars->canva.y)
		{
			data.x = i;
			data.y = j;
			trace_ray(i, j, &data);
			clear_ray_tracing_data(&data);
			j++;
		}
		i++;
	}
	if (!vars->bmp)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

t_color	get_color(double t, t_coordinates vector_point,
					 t_obj *obj, t_ray_tracing *data)
{
	t_color			color;

	data->p = coordinates_point(data->vars->current_camera->xyz,
			vector_point, t);
	if (obj->identifier == 1)
		data->normal = norm_vector(minus_vector(data->p, obj->xyz));
	if (obj->identifier == 2)
		data->normal = norm_vector(light_plane(data->vars, obj, data->p));
	if (obj->identifier == 3)
		data->normal = norm_vector(light_triangle(data->vars, obj, data->p));
	if (obj->identifier == 4)
		data->normal = norm_vector(light_square(data->vars, obj, data->p));
	if (obj->identifier == 5)
		data->normal = norm_vector(light_cylinder(data->vars, obj, data->p));
	if (obj->identifier == 25)
		data->normal = norm_vector(light_plane(data->vars, obj, data->p));
	color = compute_lighting(data, obj);
	return (color);
}
